/* Copyright 2021 NVIDIA CORPORATION
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
#include "paragraph/translation/allreduce/null_allreduce_translator.h"

#include <memory>
#include <string>
#include <utility>

#include "factory/ObjectFactory.h"

namespace paragraph {

NullAllReduceTranslator::NullAllReduceTranslator(
    nlohmann::json config) {}

shim::StatusOr<std::unique_ptr<Subroutine>>
    NullAllReduceTranslator::GetSubroutine(
        Subroutine* reduction_subroutine,
        const std::string& name_prefix,
        Instruction* calling_instruction,
        int64_t processor_id,
        int64_t processor_index,
        const CommunicationGroup& comm_group,
        double comm_size) const {
  auto graph = calling_instruction->GetGraph();
  auto allreduce_subroutine = absl::make_unique<Subroutine>(
      absl::StrCat(name_prefix, "_null"), graph);
  return allreduce_subroutine;
}

registerWithObjectFactory(
    "null",
    AllReduceTranslator,
    NullAllReduceTranslator,
    nlohmann::json);

}  // namespace paragraph
