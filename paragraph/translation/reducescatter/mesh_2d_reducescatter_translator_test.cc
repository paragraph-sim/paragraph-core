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

#include "google/protobuf/text_format.h"
#include "google/protobuf/util/message_differencer.h"
#include "gtest/gtest.h"
#include "paragraph/shim/test_macros.h"
#include "paragraph/translation/translation_map.h"

paragraph::InstructionProto Mesh2dReduceScatter_no_barrier_test_proto() {
  paragraph::InstructionProto proto;
  std::string test_str =
      R"proto(
name: "reduce-scatter"
opcode: "reduce-scatter"
instruction_id: 2
bytes_out: 80
communication_groups {
  group_ids: 0
  group_ids: 1
  group_ids: 2
  group_ids: 3
  group_ids: 4
  group_ids: 5
  group_ids: 6
  group_ids: 7
}
inner_subroutines {
  name: "reduce-scatter_mesh-2d"
  subroutine_root_id: 59
  execution_probability: 1
  execution_count: 1
  instructions {
    name: "reduce-scatter_stream-0_stage-0"
    opcode: "reduce-scatter"
    instruction_id: 7
    bytes_out: 40
    communication_groups {
      group_ids: 0
      group_ids: 1
      group_ids: 2
      group_ids: 3
    }
    inner_subroutines {
      name: "reduce-scatter_stream-0_stage-0_mesh-1d"
      subroutine_root_id: 26
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 8
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 9
        operand_ids: 8
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 12
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 10
            bytes_out: 10
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 11
            bytes_out: 10
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 12
            ops: 20
            operand_ids: 10
            operand_ids: 11
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 13
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 2
          group_ids: 2
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 14
        operand_ids: 13
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 17
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 15
            bytes_out: 10
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 16
            bytes_out: 10
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 17
            ops: 20
            operand_ids: 15
            operand_ids: 16
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_root_0"
        opcode: "null"
        instruction_id: 18
        operand_ids: 14
        operand_ids: 9
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_send_1"
        opcode: "send"
        instruction_id: 19
        bytes_out: 10
        communication_groups {
          group_ids: 0
        }
        operand_ids: 18
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_cw_sendrecv_1"
        opcode: "sendrecv"
        instruction_id: 20
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 2
          group_ids: 2
        }
        operand_ids: 18
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_cw_reduction_1"
        opcode: "call"
        instruction_id: 21
        operand_ids: 20
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_1"
          subroutine_root_id: 24
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_1"
            opcode: "delay"
            instruction_id: 22
            bytes_out: 10
          }
          instructions {
            name: "op2_cw_phase_1"
            opcode: "delay"
            instruction_id: 23
            bytes_out: 10
          }
          instructions {
            name: "sum_cw_phase_1"
            opcode: "delay"
            instruction_id: 24
            ops: 20
            operand_ids: 22
            operand_ids: 23
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_root_1"
        opcode: "null"
        instruction_id: 25
        operand_ids: 21
        operand_ids: 19
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_send_2"
        opcode: "send"
        instruction_id: 26
        bytes_out: 10
        communication_groups {
          group_ids: 0
        }
        operand_ids: 25
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-0_stage-1"
    opcode: "reduce-scatter"
    instruction_id: 27
    bytes_out: 10
    communication_groups {
      group_ids: 1
      group_ids: 5
    }
    operand_ids: 7
    inner_subroutines {
      name: "reduce-scatter_stream-0_stage-1_mesh-1d"
      subroutine_root_id: 29
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 28
        bytes_in: 5
        bytes_out: 5
        communication_groups {
          group_ids: 5
          group_ids: 5
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 29
        operand_ids: 28
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 32
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 30
            bytes_out: 5
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 31
            bytes_out: 5
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 32
            ops: 10
            operand_ids: 30
            operand_ids: 31
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-1_stage-0"
    opcode: "reduce-scatter"
    instruction_id: 33
    bytes_out: 40
    communication_groups {
      group_ids: 0
      group_ids: 1
      group_ids: 4
      group_ids: 5
    }
    inner_subroutines {
      name: "reduce-scatter_stream-1_stage-0_mesh-1d"
      subroutine_root_id: 52
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 34
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 35
        operand_ids: 34
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 38
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 36
            bytes_out: 10
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 37
            bytes_out: 10
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 38
            ops: 20
            operand_ids: 36
            operand_ids: 37
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 39
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 4
          group_ids: 4
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 40
        operand_ids: 39
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 43
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 41
            bytes_out: 10
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 42
            bytes_out: 10
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 43
            ops: 20
            operand_ids: 41
            operand_ids: 42
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_root_0"
        opcode: "null"
        instruction_id: 44
        operand_ids: 40
        operand_ids: 35
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_send_1"
        opcode: "send"
        instruction_id: 45
        bytes_out: 10
        communication_groups {
          group_ids: 0
        }
        operand_ids: 44
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_sendrecv_1"
        opcode: "sendrecv"
        instruction_id: 46
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 4
          group_ids: 4
        }
        operand_ids: 44
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_reduction_1"
        opcode: "call"
        instruction_id: 47
        operand_ids: 46
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_1"
          subroutine_root_id: 50
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_1"
            opcode: "delay"
            instruction_id: 48
            bytes_out: 10
          }
          instructions {
            name: "op2_cw_phase_1"
            opcode: "delay"
            instruction_id: 49
            bytes_out: 10
          }
          instructions {
            name: "sum_cw_phase_1"
            opcode: "delay"
            instruction_id: 50
            ops: 20
            operand_ids: 48
            operand_ids: 49
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_root_1"
        opcode: "null"
        instruction_id: 51
        operand_ids: 47
        operand_ids: 45
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_send_2"
        opcode: "send"
        instruction_id: 52
        bytes_out: 10
        communication_groups {
          group_ids: 0
        }
        operand_ids: 51
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-1_stage-1"
    opcode: "reduce-scatter"
    instruction_id: 53
    bytes_out: 10
    communication_groups {
      group_ids: 1
      group_ids: 3
    }
    operand_ids: 33
    inner_subroutines {
      name: "reduce-scatter_stream-1_stage-1_mesh-1d"
      subroutine_root_id: 55
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-1_stage-1_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 54
        bytes_in: 5
        bytes_out: 5
        communication_groups {
          group_ids: 3
          group_ids: 3
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-1_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 55
        operand_ids: 54
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 58
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 56
            bytes_out: 5
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 57
            bytes_out: 5
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 58
            ops: 10
            operand_ids: 56
            operand_ids: 57
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_root"
    opcode: "null"
    instruction_id: 59
    operand_ids: 27
    operand_ids: 53
  }
}
      )proto";
  google::protobuf::TextFormat::ParseFromString(test_str,
                                                &proto);
  return proto;
}  // NOLINT

// Tests expanding 2D-Mesh reduce-scatter
TEST(Mesh2dReduceScatter, NoBarrier) {
  auto graph = absl::make_unique<paragraph::Graph>("test_graph", 1);
  auto sub = absl::make_unique<paragraph::Subroutine>(
      "test_subroutine", graph.get());
  auto sub_ptr = sub.get();
  graph->SetEntrySubroutine(std::move(sub));

  ASSERT_OK_AND_ASSIGN(auto instr_1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "first_instruction", sub_ptr));
  instr_1->SetOps(4);

  ASSERT_OK_AND_ASSIGN(auto reducescatter,
                       paragraph::Instruction::Create(
      paragraph::Opcode::kReduceScatter, "reduce-scatter", sub_ptr));
  reducescatter->SetBytesOut(80);
  paragraph::CommunicationGroup reducescatter_group = {0, 1, 2, 3, 4, 5, 6, 7};
  reducescatter->AppendCommunicationGroup(reducescatter_group);

  auto reduction_sub = absl::make_unique<paragraph::Subroutine>(
      "reduction_subroutine", graph.get());
  auto reduction_ptr = reduction_sub.get();
  ASSERT_OK_AND_ASSIGN(auto op1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op1", reduction_ptr));
  op1->SetBytesOut(80);
  ASSERT_OK_AND_ASSIGN(auto op2, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op2", reduction_ptr));
  op2->SetBytesOut(80);
  ASSERT_OK_AND_ASSIGN(auto sum_op, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "sum", reduction_ptr, true));
  sum_op->SetOps(160);
  sum_op->AddOperand(op1);
  sum_op->AddOperand(op2);
  reducescatter->AppendInnerSubroutine(std::move(reduction_sub));

  ASSERT_OK_AND_ASSIGN(auto instr_3, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "last_instruction", sub_ptr, true));
  instr_3->SetOps(4);

  nlohmann::json config = R"(
    {
      "reduce-scatter": {
        "algorithm": "mesh-2d",
        "concentration": 2,
        "dimension_widths": [2, 2],
        "integrated_local_exchange": true
      }
    }
  )"_json;

  ASSERT_OK_AND_ASSIGN(auto translators, paragraph::CreateTranslators(
     paragraph::TranslatorType::kCollective, config));
  EXPECT_OK(translators["reduce-scatter"]->Translate(reducescatter));

  paragraph::InstructionProto reducescatter_proto =
      Mesh2dReduceScatter_no_barrier_test_proto();
  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(
      reducescatter->ToProto().value(), reducescatter_proto));
}

paragraph::InstructionProto
Mesh2dReduceScatter_with_barrier_test_proto() {
  paragraph::InstructionProto proto;
  std::string test_str =
      R"proto(
name: "reduce-scatter"
opcode: "reduce-scatter"
instruction_id: 2
bytes_out: 80
communication_groups {
  group_ids: 0
  group_ids: 1
  group_ids: 2
  group_ids: 3
  group_ids: 4
  group_ids: 5
  group_ids: 6
  group_ids: 7
}
inner_subroutines {
  name: "reduce-scatter_mesh-2d"
  subroutine_root_id: 55
  execution_probability: 1
  execution_count: 1
  instructions {
    name: "reduce-scatter_conc"
    opcode: "reduce-scatter"
    instruction_id: 7
    bytes_out: 80
    communication_groups {
      group_ids: 2
      group_ids: 3
    }
    inner_subroutines {
      name: "reduce-scatter_conc_mesh-1d"
      subroutine_root_id: 13
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_conc_unidir-ring_barrier"
        opcode: "barrier"
        instruction_id: 8
        communication_groups {
          group_ids: 2
          group_ids: 3
        }
        inner_subroutines {
          name: "reduce-scatter_conc_unidir-ring_barrier_centralized"
          subroutine_root_id: 11
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "reduce-scatter_conc_unidir-ring_barrier_centralized_coordinator_recv_from_3"
            opcode: "recv"
            instruction_id: 9
            communication_groups {
              group_ids: 3
            }
          }
          instructions {
            name: "reduce-scatter_conc_unidir-ring_barrier_centralized_coordinator_send_to_3"
            opcode: "send"
            instruction_id: 10
            communication_groups {
              group_ids: 3
            }
            operand_ids: 9
          }
          instructions {
            name: "reduce-scatter_conc_unidir-ring_barrier_centralized_root_2"
            opcode: "null"
            instruction_id: 11
            operand_ids: 10
          }
        }
      }
      instructions {
        name: "reduce-scatter_conc_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 12
        bytes_in: 40
        bytes_out: 40
        communication_groups {
          group_ids: 3
          group_ids: 3
        }
        operand_ids: 8
      }
      instructions {
        name: "reduce-scatter_conc_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 13
        operand_ids: 12
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 16
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 14
            bytes_out: 40
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 15
            bytes_out: 40
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 16
            ops: 80
            operand_ids: 14
            operand_ids: 15
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-0_stage-0"
    opcode: "reduce-scatter"
    instruction_id: 17
    bytes_out: 20
    communication_groups {
      group_ids: 0
      group_ids: 2
    }
    operand_ids: 7
    inner_subroutines {
      name: "reduce-scatter_stream-0_stage-0_mesh-1d"
      subroutine_root_id: 22
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-0_stage-0_unidir-ring_barrier"
        opcode: "barrier"
        instruction_id: 18
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        inner_subroutines {
          name: "reduce-scatter_stream-0_stage-0_unidir-ring_barrier_centralized"
          subroutine_root_id: 20
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "reduce-scatter_stream-0_stage-0_unidir-ring_barrier_centralized_send_to_0"
            opcode: "send"
            instruction_id: 19
            communication_groups {
              group_ids: 0
            }
          }
          instructions {
            name: "reduce-scatter_stream-0_stage-0_unidir-ring_barrier_centralized_recv_from_0"
            opcode: "recv"
            instruction_id: 20
            communication_groups {
              group_ids: 0
            }
            operand_ids: 19
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 21
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
        operand_ids: 18
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-0_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 22
        operand_ids: 21
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 25
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 23
            bytes_out: 10
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 24
            bytes_out: 10
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 25
            ops: 20
            operand_ids: 23
            operand_ids: 24
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-0_stage-1"
    opcode: "reduce-scatter"
    instruction_id: 26
    bytes_out: 10
    communication_groups {
      group_ids: 2
      group_ids: 6
    }
    operand_ids: 17
    inner_subroutines {
      name: "reduce-scatter_stream-0_stage-1_mesh-1d"
      subroutine_root_id: 32
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-0_stage-1_unidir-ring_barrier"
        opcode: "barrier"
        instruction_id: 27
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        inner_subroutines {
          name: "reduce-scatter_stream-0_stage-1_unidir-ring_barrier_centralized"
          subroutine_root_id: 30
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "reduce-scatter_stream-0_stage-1_unidir-ring_barrier_centralized_coordinator_recv_from_6"
            opcode: "recv"
            instruction_id: 28
            communication_groups {
              group_ids: 6
            }
          }
          instructions {
            name: "reduce-scatter_stream-0_stage-1_unidir-ring_barrier_centralized_coordinator_send_to_6"
            opcode: "send"
            instruction_id: 29
            communication_groups {
              group_ids: 6
            }
            operand_ids: 28
          }
          instructions {
            name: "reduce-scatter_stream-0_stage-1_unidir-ring_barrier_centralized_root_2"
            opcode: "null"
            instruction_id: 30
            operand_ids: 29
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 31
        bytes_in: 5
        bytes_out: 5
        communication_groups {
          group_ids: 6
          group_ids: 6
        }
        operand_ids: 27
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 32
        operand_ids: 31
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 35
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 33
            bytes_out: 5
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 34
            bytes_out: 5
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 35
            ops: 10
            operand_ids: 33
            operand_ids: 34
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-1_stage-0"
    opcode: "reduce-scatter"
    instruction_id: 36
    bytes_out: 20
    communication_groups {
      group_ids: 2
      group_ids: 6
    }
    operand_ids: 7
    inner_subroutines {
      name: "reduce-scatter_stream-1_stage-0_mesh-1d"
      subroutine_root_id: 42
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-1_stage-0_unidir-ring_barrier"
        opcode: "barrier"
        instruction_id: 37
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        inner_subroutines {
          name: "reduce-scatter_stream-1_stage-0_unidir-ring_barrier_centralized"
          subroutine_root_id: 40
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "reduce-scatter_stream-1_stage-0_unidir-ring_barrier_centralized_coordinator_recv_from_6"
            opcode: "recv"
            instruction_id: 38
            communication_groups {
              group_ids: 6
            }
          }
          instructions {
            name: "reduce-scatter_stream-1_stage-0_unidir-ring_barrier_centralized_coordinator_send_to_6"
            opcode: "send"
            instruction_id: 39
            communication_groups {
              group_ids: 6
            }
            operand_ids: 38
          }
          instructions {
            name: "reduce-scatter_stream-1_stage-0_unidir-ring_barrier_centralized_root_2"
            opcode: "null"
            instruction_id: 40
            operand_ids: 39
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 41
        bytes_in: 10
        bytes_out: 10
        communication_groups {
          group_ids: 6
          group_ids: 6
        }
        operand_ids: 37
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 42
        operand_ids: 41
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 45
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 43
            bytes_out: 10
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 44
            bytes_out: 10
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 45
            ops: 20
            operand_ids: 43
            operand_ids: 44
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-1_stage-1"
    opcode: "reduce-scatter"
    instruction_id: 46
    bytes_out: 10
    communication_groups {
      group_ids: 0
      group_ids: 2
    }
    operand_ids: 36
    inner_subroutines {
      name: "reduce-scatter_stream-1_stage-1_mesh-1d"
      subroutine_root_id: 51
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-1_stage-1_unidir-ring_barrier"
        opcode: "barrier"
        instruction_id: 47
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        inner_subroutines {
          name: "reduce-scatter_stream-1_stage-1_unidir-ring_barrier_centralized"
          subroutine_root_id: 49
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "reduce-scatter_stream-1_stage-1_unidir-ring_barrier_centralized_send_to_0"
            opcode: "send"
            instruction_id: 48
            communication_groups {
              group_ids: 0
            }
          }
          instructions {
            name: "reduce-scatter_stream-1_stage-1_unidir-ring_barrier_centralized_recv_from_0"
            opcode: "recv"
            instruction_id: 49
            communication_groups {
              group_ids: 0
            }
            operand_ids: 48
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-1_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 50
        bytes_in: 5
        bytes_out: 5
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
        operand_ids: 47
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-1_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 51
        operand_ids: 50
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 54
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 52
            bytes_out: 5
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 53
            bytes_out: 5
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 54
            ops: 10
            operand_ids: 52
            operand_ids: 53
          }
        }
      }
    }
  }
  instructions {
    name: "reduce-scatter_root"
    opcode: "null"
    instruction_id: 55
    operand_ids: 26
    operand_ids: 46
  }
}
      )proto";
  google::protobuf::TextFormat::ParseFromString(test_str,
                                                &proto);
  return proto;
}  // NOLINT

// Tests expanding 1D-Mesh reduce-scatter with barrier
TEST(Mesh2dReduceScatter, WithBarrier) {
  auto graph = absl::make_unique<paragraph::Graph>("test_graph", 2);
  auto sub = absl::make_unique<paragraph::Subroutine>(
      "test_subroutine", graph.get());
  auto sub_ptr = sub.get();
  sub_ptr->SetId(3);
  graph->SetEntrySubroutine(std::move(sub));

  ASSERT_OK_AND_ASSIGN(auto instr_1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "first_instruction", sub_ptr));
  instr_1->SetOps(4);

  ASSERT_OK_AND_ASSIGN(auto reducescatter,
                       paragraph::Instruction::Create(
      paragraph::Opcode::kReduceScatter, "reduce-scatter", sub_ptr));
  reducescatter->SetBytesOut(80);
  paragraph::CommunicationGroup reducescatter_group = {0, 1, 2, 3, 4, 5, 6, 7};
  reducescatter->AppendCommunicationGroup(reducescatter_group);

  auto reduction_sub = absl::make_unique<paragraph::Subroutine>(
      "reduction_subroutine", graph.get());
  auto reduction_ptr = reduction_sub.get();
  ASSERT_OK_AND_ASSIGN(auto op1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op1", reduction_ptr));
  op1->SetBytesOut(80);
  ASSERT_OK_AND_ASSIGN(auto op2, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op2", reduction_ptr));
  op2->SetBytesOut(80);
  ASSERT_OK_AND_ASSIGN(auto sum_op, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "sum", reduction_ptr, true));
  sum_op->SetOps(160);
  sum_op->AddOperand(op1);
  sum_op->AddOperand(op2);
  reducescatter->AppendInnerSubroutine(std::move(reduction_sub));

  ASSERT_OK_AND_ASSIGN(auto instr_3, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "last_instruction", sub_ptr, true));
  instr_3->SetOps(4);

  nlohmann::json config = R"(
    {
      "reduce-scatter": {
        "algorithm": "mesh-2d",
        "concentration": 2,
        "dimension_widths": [2, 2],
        "barrier": {
          "algorithm": "centralized"
        }
      }
    }
  )"_json;

  ASSERT_OK_AND_ASSIGN(auto translators, paragraph::CreateTranslators(
     paragraph::TranslatorType::kCollective, config));
  EXPECT_OK(translators["reduce-scatter"]->Translate(reducescatter));

  paragraph::InstructionProto reducescatter_proto =
      Mesh2dReduceScatter_with_barrier_test_proto();
  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(
      reducescatter->ToProto().value(), reducescatter_proto));
}

paragraph::InstructionProto
Mesh2dReduceScatter_inconsecutive_proc_test_proto() {
  paragraph::InstructionProto proto;
  std::string test_str =
      R"proto(
name: "reduce-scatter"
opcode: "reduce-scatter"
instruction_id: 2
bytes_out: 48
communication_groups {
  group_ids: 0
  group_ids: 2
  group_ids: 4
}
inner_subroutines {
  name: "reduce-scatter_mesh-2d"
  subroutine_root_id: 37
  execution_probability: 1
  execution_count: 1
  instructions {
    name: "reduce-scatter_stream-0_stage-1"
    opcode: "reduce-scatter"
    instruction_id: 7
    bytes_out: 24
    communication_groups {
      group_ids: 0
      group_ids: 2
      group_ids: 4
    }
    inner_subroutines {
      name: "reduce-scatter_stream-0_stage-1_mesh-1d"
      subroutine_root_id: 21
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 8
        bytes_in: 8
        bytes_out: 8
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 9
        operand_ids: 8
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 12
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 10
            bytes_out: 8
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 11
            bytes_out: 8
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 12
            ops: 16
            operand_ids: 10
            operand_ids: 11
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 13
        bytes_in: 8
        bytes_out: 8
        communication_groups {
          group_ids: 4
          group_ids: 4
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 14
        operand_ids: 13
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 17
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 15
            bytes_out: 8
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 16
            bytes_out: 8
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 17
            ops: 16
            operand_ids: 15
            operand_ids: 16
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_root_0"
        opcode: "null"
        instruction_id: 18
        operand_ids: 14
        operand_ids: 9
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_ccw_send_1"
        opcode: "send"
        instruction_id: 19
        bytes_out: 8
        communication_groups {
          group_ids: 0
        }
        operand_ids: 18
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_cw_send_1"
        opcode: "send"
        instruction_id: 20
        bytes_out: 8
        communication_groups {
          group_ids: 4
        }
        operand_ids: 18
      }
      instructions {
        name: "reduce-scatter_stream-0_stage-1_mesh-1d_root_1"
        opcode: "null"
        instruction_id: 21
        operand_ids: 20
        operand_ids: 19
      }
    }
  }
  instructions {
    name: "reduce-scatter_stream-1_stage-0"
    opcode: "reduce-scatter"
    instruction_id: 22
    bytes_out: 24
    communication_groups {
      group_ids: 0
      group_ids: 2
      group_ids: 4
    }
    inner_subroutines {
      name: "reduce-scatter_stream-1_stage-0_mesh-1d"
      subroutine_root_id: 36
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 23
        bytes_in: 8
        bytes_out: 8
        communication_groups {
          group_ids: 0
          group_ids: 0
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_reduction_0"
        opcode: "call"
        instruction_id: 24
        operand_ids: 23
        inner_subroutines {
          name: "reduction_subroutine_ccw_phase_0"
          subroutine_root_id: 27
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_ccw_phase_0"
            opcode: "delay"
            instruction_id: 25
            bytes_out: 8
          }
          instructions {
            name: "op2_ccw_phase_0"
            opcode: "delay"
            instruction_id: 26
            bytes_out: 8
          }
          instructions {
            name: "sum_ccw_phase_0"
            opcode: "delay"
            instruction_id: 27
            ops: 16
            operand_ids: 25
            operand_ids: 26
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_sendrecv_0"
        opcode: "sendrecv"
        instruction_id: 28
        bytes_in: 8
        bytes_out: 8
        communication_groups {
          group_ids: 4
          group_ids: 4
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_reduction_0"
        opcode: "call"
        instruction_id: 29
        operand_ids: 28
        inner_subroutines {
          name: "reduction_subroutine_cw_phase_0"
          subroutine_root_id: 32
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "op1_cw_phase_0"
            opcode: "delay"
            instruction_id: 30
            bytes_out: 8
          }
          instructions {
            name: "op2_cw_phase_0"
            opcode: "delay"
            instruction_id: 31
            bytes_out: 8
          }
          instructions {
            name: "sum_cw_phase_0"
            opcode: "delay"
            instruction_id: 32
            ops: 16
            operand_ids: 30
            operand_ids: 31
          }
        }
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_root_0"
        opcode: "null"
        instruction_id: 33
        operand_ids: 29
        operand_ids: 24
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_ccw_send_1"
        opcode: "send"
        instruction_id: 34
        bytes_out: 8
        communication_groups {
          group_ids: 0
        }
        operand_ids: 33
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_cw_send_1"
        opcode: "send"
        instruction_id: 35
        bytes_out: 8
        communication_groups {
          group_ids: 4
        }
        operand_ids: 33
      }
      instructions {
        name: "reduce-scatter_stream-1_stage-0_mesh-1d_root_1"
        opcode: "null"
        instruction_id: 36
        operand_ids: 35
        operand_ids: 34
      }
    }
  }
  instructions {
    name: "reduce-scatter_root"
    opcode: "null"
    instruction_id: 37
    operand_ids: 7
    operand_ids: 22
  }
}
      )proto";
  google::protobuf::TextFormat::ParseFromString(test_str,
                                                &proto);
  return proto;
}  // NOLINT

// Tests expanding 1D-Mesh reduce-scatter
TEST(Mesh2dReduceScatter, InconsecutiveProcessors) {
  auto graph = absl::make_unique<paragraph::Graph>("test_graph", 2);
  auto sub = absl::make_unique<paragraph::Subroutine>(
      "test_subroutine", graph.get());
  auto sub_ptr = sub.get();
  graph->SetEntrySubroutine(std::move(sub));

  ASSERT_OK_AND_ASSIGN(auto instr_1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "first_instruction", sub_ptr));
  instr_1->SetOps(4);

  ASSERT_OK_AND_ASSIGN(auto reducescatter,
                       paragraph::Instruction::Create(
      paragraph::Opcode::kReduceScatter, "reduce-scatter", sub_ptr));
  reducescatter->SetBytesOut(48);
  paragraph::CommunicationGroup reducescatter_group = {0, 2, 4};
  reducescatter->AppendCommunicationGroup(reducescatter_group);

  auto reduction_sub = absl::make_unique<paragraph::Subroutine>(
      "reduction_subroutine", graph.get());
  auto reduction_ptr = reduction_sub.get();
  ASSERT_OK_AND_ASSIGN(auto op1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op1", reduction_ptr));
  op1->SetBytesOut(48);
  ASSERT_OK_AND_ASSIGN(auto op2, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "op2", reduction_ptr));
  op2->SetBytesOut(48);
  ASSERT_OK_AND_ASSIGN(auto sum_op, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "sum", reduction_ptr, true));
  sum_op->SetOps(96);
  sum_op->AddOperand(op1);
  sum_op->AddOperand(op2);
  reducescatter->AppendInnerSubroutine(std::move(reduction_sub));

  ASSERT_OK_AND_ASSIGN(auto instr_3, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "last_instruction", sub_ptr, true));
  instr_3->SetOps(4);

  nlohmann::json config = R"(
    {
      "reduce-scatter": {
        "algorithm": "mesh-2d",
        "dimension_widths": [2, 3]
      }
    }
  )"_json;

  ASSERT_OK_AND_ASSIGN(auto translators, paragraph::CreateTranslators(
     paragraph::TranslatorType::kCollective, config));
  EXPECT_OK(translators["reduce-scatter"]->Translate(reducescatter));

  paragraph::InstructionProto reducescatter_proto =
      Mesh2dReduceScatter_inconsecutive_proc_test_proto();
  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(
      reducescatter->ToProto().value(), reducescatter_proto));
}
