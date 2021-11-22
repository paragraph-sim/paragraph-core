/* Copyright 2021 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *  https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "paragraph/translation/reducescatter/mesh_2d_reducescatter_translator.h"

#include <memory>
#include <string>
#include <utility>
#include <unordered_set>
#include <vector>

#include "factory/ObjectFactory.h"
#include "paragraph/translation/utils.h"

namespace paragraph {

Mesh2dReduceScatterTranslator::Mesh2dReduceScatterTranslator(
    nlohmann::json config) {
  CHECK_NE(config.find("dimension_widths"), config.end()) <<
      "2D Mesh should have field 'dimension_widths' as an array of size 2.";
  CHECK(config["dimension_widths"].is_array()) <<
      "2D Mesh config field 'dimension_widths' should be an array.";
  CHECK_EQ(config["dimension_widths"].size(), 2) <<
      "2D Mesh config field 'dimension_widths' should should have size 2.";
  for (size_t i = 0; i < config["dimension_widths"].size(); i++) {
    uint64_t width = config["dimension_widths"][i].get<uint64_t>();
    CHECK_GT(width, 1) << "Mesh width should be more than 1.";
    dimension_sizes_.push_back(width);
  }
  // Extract concentration (number of processors per mesh node) from config
  // By default equals 1
  concentration_ = 1;
  if (config.find("concentration") != config.end()) {
    concentration_ = config["concentration"].get<uint64_t>();
  }
  // conentrated ports
  integrated_local_exchange_ = false;
  if (config.find("integrated_local_exchange") != config.end()) {
    integrated_local_exchange_ =
        config["integrated_local_exchange"].get<bool>();
  }

  // Create json config for internal 1D Mesh reduce-scatter
  nlohmann::json implicit_config = R"(
    { "algorithm": "mesh-1d" }
  )"_json;
  // If we have a barrier in 2D Mesh, we need to instantiate a barrier before
  // reduce-scatter in each dimension. Synchronizing processors only in the
  // dimension that is communicating is enough (as opposed to i.e. sync current
  // and previous dimension) because the synchronized processor by the end of
  // the barrier would receive and send all the data from the previous stage,
  // even if not all other processors from the previous stage have finished.
  if (config.find("barrier") != config.end()) {
    implicit_config["barrier"] = config["barrier"];
  }
  auto maybe_reducescatter_translator = ReduceScatterTranslator::Create(
      implicit_config);
  CHECK_OK(maybe_reducescatter_translator.status());
  reducescatter_translator_ = std::move(maybe_reducescatter_translator.value());
}

shim::StatusOr<std::unique_ptr<Subroutine>>
    Mesh2dReduceScatterTranslator::GetSubroutine(
        Subroutine* reduction_subroutine,
        const std::string& name_prefix,
        Instruction* calling_instruction,
        int64_t processor_id,
        int64_t processor_index,
        const CommunicationGroup& comm_group,
        double comm_size) const {
  auto graph = calling_instruction->GetGraph();
  auto reducescatter_subroutine = absl::make_unique<Subroutine>(
      absl::StrCat(name_prefix, "_mesh-2d"), graph);
  auto reducescatter_sub_ptr = reducescatter_subroutine.get();
  RETURN_IF_FALSE(comm_group.at(processor_index) == processor_id,
                  absl::InvalidArgumentError) <<
      "Processor index points to the wrong Processor ID.";
  size_t num_dimensions = dimension_sizes_.size();
  // Vector of previous instruction for every concurrent stream
  std::vector<Instruction*> previous_instructions(
      num_dimensions, nullptr);
  // We initialize communication sizes for each stage and each dimension as
  // dimension and/or communication groups could be uneven
  std::vector<double> stage_comm_sizes;
  for (size_t par_stream = 0; par_stream < num_dimensions; par_stream++) {
    if ((comm_size == 0) || (comm_group.empty())) {
      stage_comm_sizes.push_back(0);
    } else {
      stage_comm_sizes.push_back(
          comm_size / comm_group.size() / num_dimensions);
    }
  }
  bool conc_step = (concentration_ > 1) && !integrated_local_exchange_;
  // We have as many stages as dimensions in the Mesh
  // At every stage, we span as many concurrent single-dimensional
  // reduce-scatter as number of dimensions N we have in mesh. For every
  // concurrent stream,  we start with the partial exchange over dimension
  // (i + 0) % N, then dimension (i + 1) % N, and to the last dimension (in
  // generic case). Before starting partial exchange over each dimension, we
  // need to synchronize the processors that participate in the exchange step
  // and the processors that participated in the previous step.
  // If `integrated_local_exchange_` set, we add communicators to the last stage
  // exchange to minimize traffic. Otherwise, we run local communicators
  // exchange as the last step.
  for (size_t par_stream = 0; par_stream < num_dimensions; par_stream++) {
    for (size_t stage = 0; stage < num_dimensions; stage++) {
      size_t dim = (par_stream + stage) % num_dimensions;
      bool integrated_local_exchange = integrated_local_exchange_
        && ((stage + 1) == num_dimensions);
      std::unordered_set<size_t> comm_dimensions;
      CHECK(comm_dimensions.insert(dim + 1).second);
      // We only need to communicate data between concentrators once. If we
      // don't have a separate stage for that in the end, we do it in the last
      // stage.
      if (integrated_local_exchange) {
        CHECK(comm_dimensions.insert(0).second);
      }
      auto new_comm_group = CommunicationGroupProjectionOnDimensions(
          comm_dimensions, processor_id, comm_group,
          dimension_sizes_, concentration_);
      // Every new stage we should increase communication size
      // On the first stage we only exchange data laying in the 1st dimension
      // On the second stage we exchange data from both 1st and 2nd dimensions
      stage_comm_sizes.at(par_stream) *= new_comm_group.size();
      // If we don't have any communication in original comm_group within the
      // current dimension, just leave it
      if (new_comm_group.size() > 1) {
        ASSIGN_OR_RETURN(auto reducescatter_stage, Instruction::Create(
            Opcode::kReduceScatter,
            absl::StrCat(name_prefix, "_stream-", par_stream, "_stage-", stage),
            reducescatter_sub_ptr));
        reducescatter_stage->AppendCommunicationGroup(new_comm_group);
        reducescatter_stage->SetBytesOut(stage_comm_sizes.at(par_stream));
        if (previous_instructions.at(par_stream) != nullptr) {
          reducescatter_stage->AddOperand(previous_instructions.at(par_stream));
        }
        ASSIGN_OR_RETURN(auto reduction_subroutine_stage,
                         reduction_subroutine->Clone("", /*reset_ids*/ false));
        if ((comm_size != 0) && (stage_comm_sizes.at(par_stream) != 0)) {
          reduction_subroutine_stage->ScalePerformance(
              1.0 * stage_comm_sizes.at(par_stream) / comm_size);
        }
        reducescatter_stage->AppendInnerSubroutine(std::move(
            reduction_subroutine_stage));
        RETURN_IF_ERROR(reducescatter_translator_->Translate(
            reducescatter_stage));
        previous_instructions.at(par_stream) = reducescatter_stage;
      }
    }
  }
  // Check if we have non-trivial concentration and need to perform
  // explicit local exchange step
  if (conc_step) {
    auto local_comm_group = CommunicationGroupProjectionOnDimensions(
        {0}, processor_id, comm_group,
        dimension_sizes_, concentration_);
    if (local_comm_group.size() > 1) {
      ASSIGN_OR_RETURN(auto reducescatter_conc, Instruction::Create(
          Opcode::kReduceScatter,
          absl::StrCat(name_prefix, "_conc"),
          reducescatter_sub_ptr,
          true));
      reducescatter_conc->AppendCommunicationGroup(local_comm_group);
      reducescatter_conc->SetBytesOut(comm_size);
      for (auto& instr : previous_instructions) {
        if (instr != nullptr) {
          reducescatter_conc->AddOperand(instr);
        }
      }
      ASSIGN_OR_RETURN(auto reduction_subroutine_conc,
                       reduction_subroutine->Clone("", /*reset_ids*/ false));
      reducescatter_conc->AppendInnerSubroutine(std::move(
          reduction_subroutine_conc));
      RETURN_IF_ERROR(reducescatter_translator_->Translate(
          reducescatter_conc));
    }
  } else {
    ASSIGN_OR_RETURN(auto reducescatter_root, Instruction::Create(
        Opcode::kNull,
        absl::StrCat(name_prefix, "_root"),
        reducescatter_sub_ptr,
        true));
    for (auto& instr : previous_instructions) {
      if (instr != nullptr) {
        reducescatter_root->AddOperand(instr);
      }
    }
  }
  return reducescatter_subroutine;
}

registerWithObjectFactory(
    "mesh-2d",
    ReduceScatterTranslator,
    Mesh2dReduceScatterTranslator,
    nlohmann::json);

}  // namespace paragraph
