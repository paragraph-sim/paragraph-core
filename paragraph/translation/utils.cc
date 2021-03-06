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
#include "paragraph/translation/utils.h"

#include <algorithm>
#include <vector>
#include <unordered_set>

namespace paragraph {

std::vector<uint64_t> ConsecutiveProcessorIdToGridCoordinates(
    int64_t processor_id,
    const std::vector<uint64_t>& dimension_sizes,
    uint64_t concentration) {
  std::vector<uint64_t> coordinates;
  coordinates.push_back(processor_id % concentration);
  processor_id /= concentration;
  for (auto dimension_width : dimension_sizes) {
    coordinates.push_back(processor_id % dimension_width);
    processor_id /= dimension_width;
  }
  return coordinates;
}

uint64_t GridCoordinatesToConsecutiveProcessorId(
    const std::vector<uint64_t>& coordinates,
    const std::vector<uint64_t>& dimension_sizes,
    uint64_t concentration) {
  uint64_t processor_id = coordinates.at(0);
  uint64_t step = concentration;
  for (size_t index = 1; index < coordinates.size(); index++) {
    processor_id += step * coordinates.at(index);
    step *= dimension_sizes.at(index - 1);
  }
  return processor_id;
}

CommunicationGroup CommunicationGroupProjectionOnDimensions(
    const std::unordered_set<size_t>& dimensions,
    int64_t processor_id,
    const CommunicationGroup& comm_group,
    const std::vector<uint64_t>& dimension_sizes,
    uint64_t concentration) {
  std::vector<uint64_t> processor_coordinates =
      ConsecutiveProcessorIdToGridCoordinates(processor_id,
                                              dimension_sizes,
                                              concentration);
  std::vector<size_t> rigid_dimensions;
  for (size_t dim = 0; dim <= dimension_sizes.size(); dim++) {
    if (dimensions.find(dim) == dimensions.end()) {
      rigid_dimensions.push_back(dim);
    }
  }
  CommunicationGroup new_comm_group;
  for (const auto& peer_id : comm_group) {
    bool in_projection = true;
    auto peer_coordinates = ConsecutiveProcessorIdToGridCoordinates(
        peer_id, dimension_sizes, concentration);
    for (auto& dim : rigid_dimensions) {
      if (peer_coordinates.at(dim) != processor_coordinates.at(dim)) {
        in_projection = false;
      }
    }
    if (in_projection) {
      new_comm_group.push_back(peer_id);
    }
  }
  return new_comm_group;
}

CommunicationGroup Swizzling2dGridToRing(
    const std::vector<uint64_t>& dimension_sizes,
    uint64_t concentration) {
  CHECK_EQ(dimension_sizes.size(), 2) << "Algorithm expects 2D Mesh or Torus.";
  CHECK_EQ(dimension_sizes.at(0) % 2, 0) << "First dimension should be even "
                                         << "for successful swizzling.";
  // We start at processor with ID = 0 sitting in top left corner with
  // coordinates {0, 0} and all concentrations;
  CommunicationGroup swizzled_ring;
  for (uint64_t conc = 0; conc < concentration; conc++) {
    swizzled_ring.push_back(
        GridCoordinatesToConsecutiveProcessorId({conc, 0, 0},
                                                dimension_sizes,
                                                concentration));
  }
  // Iterate over all columns; and all rows from the 1st to the last
  for (uint64_t col = 0; col < dimension_sizes.at(0); col++) {
    for (uint64_t row_iter = 1; row_iter < dimension_sizes.at(1); row_iter++) {
      // Change swizzling direction depending on column parity
      // For column 0 and even columns, go down;
      // For the last column and odd columns, go up.
      uint64_t row = (col % 2) ? dimension_sizes.at(1) - row_iter : row_iter;
      // Add all concentrators
      for (uint64_t conc = 0; conc < concentration; conc++) {
        swizzled_ring.push_back(
            GridCoordinatesToConsecutiveProcessorId({conc, col, row},
                                                    dimension_sizes,
                                                    concentration));
      }
    }
  }
  // Add row 0 in the reverse order as a home run, except for
  // processor {0, 0}, as it is already there.
  for (uint64_t col = dimension_sizes.at(0) - 1; col > 0; col--) {
    for (uint64_t conc = 0; conc < concentration; conc++) {
      swizzled_ring.push_back(
          GridCoordinatesToConsecutiveProcessorId({conc, col, 0},
                                                  dimension_sizes,
                                                  concentration));
    }
  }
  return swizzled_ring;
}

}  // namespace paragraph
