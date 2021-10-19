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
#include <filesystem>
#include <memory>
#include <string>
#include <utility>

#include "absl/flags/flag.h"
#include "absl/flags/parse.h"
#include "paragraph/graph/graph.h"
#include "paragraph/shim/macros.h"

ABSL_FLAG(int64_t, num_replicas, 1,
          "The number of data parallel replicas in the new graph.");
ABSL_FLAG(std::string, input_graph, "",
          "Input graph file.");
ABSL_FLAG(std::string, output_graph, "",
          "Output graph file.");

int32_t main(int32_t argc, char** argv) {
  // Parsing flags
  absl::ParseCommandLine(argc, argv);
  std::filesystem::path input_graph_file = absl::GetFlag(FLAGS_input_graph);
  CHECK_NE(input_graph_file, "");
  std::filesystem::path output_graph_file = absl::GetFlag(FLAGS_output_graph);
  CHECK_NE(output_graph_file, "");
  int64_t num_replicas = absl::GetFlag(FLAGS_num_replicas);

  // Reading input graph
  auto graph_statusor = paragraph::Graph::ReadFromFile(input_graph_file);
  CHECK_OK(graph_statusor.status());
  std::unique_ptr<paragraph::Graph> input_graph =
      std::move(graph_statusor.value());
  CHECK_OK(input_graph->ValidateComposite());

  // Adding extra processors to communication sets of AllReduce instructions
  CHECK_OK(input_graph->ExtendCommunicationSize(num_replicas));
  CHECK_OK(input_graph->ValidateComposite());

  // Writing output graph
  CHECK_OK(input_graph->WriteToFile(output_graph_file));
  return 0;
}
