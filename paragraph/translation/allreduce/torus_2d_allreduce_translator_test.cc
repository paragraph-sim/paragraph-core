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
#include "paragraph/translation/allreduce/torus_2d_allreduce_translator.h"

#include <memory>
#include <string>
#include <utility>

#include "google/protobuf/text_format.h"
#include "google/protobuf/util/message_differencer.h"
#include "gtest/gtest.h"
#include "paragraph/shim/test_macros.h"
#include "paragraph/translation/translation_map.h"

paragraph::InstructionProto no_barrier_test_proto() {
  paragraph::InstructionProto proto;
  std::string test_str =
      R"proto(
name: "all-reduce"
opcode: "all-reduce"
instruction_id: 2
bytes_out: 48
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
  name: "all-reduce_torus-2d"
  subroutine_root_id: 79
  execution_probability: 1
  execution_count: 1
  instructions {
    name: "all-reduce_torus-2d_reduce-scatter"
    opcode: "reduce-scatter"
    instruction_id: 7
    bytes_out: 48
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
      name: "all-reduce_torus-2d_reduce-scatter_torus-2d"
      subroutine_root_id: 78
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_conc"
        opcode: "reduce-scatter"
        instruction_id: 8
        bytes_out: 48
        communication_groups {
          group_ids: 2
          group_ids: 3
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring"
          subroutine_root_id: 21
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 9
            bytes_out: 24
            communication_groups {
              group_ids: 2
              group_ids: 3
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 11
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 10
                bytes_in: 12
                bytes_out: 12
                communication_groups {
                  group_ids: 3
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 11
                operand_ids: 10
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 14
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 12
                    bytes_out: 12
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 13
                    bytes_out: 12
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 14
                    ops: 24
                    operand_ids: 12
                    operand_ids: 13
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 15
            bytes_out: 24
            communication_groups {
              group_ids: 3
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 17
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 16
                bytes_in: 12
                bytes_out: 12
                communication_groups {
                  group_ids: 3
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 17
                operand_ids: 16
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 20
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 18
                    bytes_out: 12
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 19
                    bytes_out: 12
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 20
                    ops: 24
                    operand_ids: 18
                    operand_ids: 19
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_conc_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 21
            operand_ids: 9
            operand_ids: 15
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0"
        opcode: "reduce-scatter"
        instruction_id: 22
        bytes_out: 12
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        operand_ids: 8
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring"
          subroutine_root_id: 35
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 23
            bytes_out: 6
            communication_groups {
              group_ids: 0
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 25
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 24
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 25
                operand_ids: 24
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 28
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 26
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 27
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 28
                    ops: 6
                    operand_ids: 26
                    operand_ids: 27
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 29
            bytes_out: 6
            communication_groups {
              group_ids: 2
              group_ids: 0
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 31
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 30
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 31
                operand_ids: 30
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 34
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 32
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 33
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 34
                    ops: 6
                    operand_ids: 32
                    operand_ids: 33
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 35
            operand_ids: 23
            operand_ids: 29
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1"
        opcode: "reduce-scatter"
        instruction_id: 36
        bytes_out: 6
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        operand_ids: 22
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring"
          subroutine_root_id: 49
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 37
            bytes_out: 3
            communication_groups {
              group_ids: 2
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 39
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 38
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 39
                operand_ids: 38
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 42
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 40
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 41
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 42
                    ops: 3
                    operand_ids: 40
                    operand_ids: 41
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 43
            bytes_out: 3
            communication_groups {
              group_ids: 6
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 45
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 44
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 45
                operand_ids: 44
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 48
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 46
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 47
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 48
                    ops: 3
                    operand_ids: 46
                    operand_ids: 47
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 49
            operand_ids: 37
            operand_ids: 43
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0"
        opcode: "reduce-scatter"
        instruction_id: 50
        bytes_out: 12
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        operand_ids: 8
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring"
          subroutine_root_id: 63
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 51
            bytes_out: 6
            communication_groups {
              group_ids: 2
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 53
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 52
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 53
                operand_ids: 52
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 56
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 54
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 55
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 56
                    ops: 6
                    operand_ids: 54
                    operand_ids: 55
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 57
            bytes_out: 6
            communication_groups {
              group_ids: 6
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 59
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 58
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 59
                operand_ids: 58
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 62
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 60
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 61
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 62
                    ops: 6
                    operand_ids: 60
                    operand_ids: 61
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 63
            operand_ids: 51
            operand_ids: 57
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1"
        opcode: "reduce-scatter"
        instruction_id: 64
        bytes_out: 6
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        operand_ids: 50
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring"
          subroutine_root_id: 77
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 65
            bytes_out: 3
            communication_groups {
              group_ids: 0
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 67
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 66
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 67
                operand_ids: 66
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 70
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 68
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 69
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 70
                    ops: 3
                    operand_ids: 68
                    operand_ids: 69
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 71
            bytes_out: 3
            communication_groups {
              group_ids: 2
              group_ids: 0
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 73
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 72
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 73
                operand_ids: 72
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 76
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 74
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 75
                    bytes_out: 1.5
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 76
                    ops: 3
                    operand_ids: 74
                    operand_ids: 75
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 77
            operand_ids: 65
            operand_ids: 71
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_root"
        opcode: "null"
        instruction_id: 78
        operand_ids: 36
        operand_ids: 64
      }
    }
  }
  instructions {
    name: "all-reduce_torus-2d_all-gather"
    opcode: "all-gather"
    instruction_id: 79
    bytes_out: 48
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
    operand_ids: 7
    inner_subroutines {
      name: "all-reduce_torus-2d_all-gather_torus-2d"
      subroutine_root_id: 104
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-0_stage-0"
        opcode: "all-gather"
        instruction_id: 80
        bytes_out: 6
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring"
          subroutine_root_id: 85
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 81
            bytes_out: 3
            communication_groups {
              group_ids: 0
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 82
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 82
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 83
            bytes_out: 3
            communication_groups {
              group_ids: 2
              group_ids: 0
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 84
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 84
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 85
            operand_ids: 81
            operand_ids: 83
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-0_stage-1"
        opcode: "all-gather"
        instruction_id: 86
        bytes_out: 12
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        operand_ids: 80
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring"
          subroutine_root_id: 91
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 87
            bytes_out: 6
            communication_groups {
              group_ids: 2
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 88
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 88
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 89
            bytes_out: 6
            communication_groups {
              group_ids: 6
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 90
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 90
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 91
            operand_ids: 87
            operand_ids: 89
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-1_stage-0"
        opcode: "all-gather"
        instruction_id: 92
        bytes_out: 6
        communication_groups {
          group_ids: 2
          group_ids: 6
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring"
          subroutine_root_id: 97
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 93
            bytes_out: 3
            communication_groups {
              group_ids: 2
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 94
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 94
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 95
            bytes_out: 3
            communication_groups {
              group_ids: 6
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 96
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 96
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 6
                  group_ids: 6
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 97
            operand_ids: 93
            operand_ids: 95
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-1_stage-1"
        opcode: "all-gather"
        instruction_id: 98
        bytes_out: 12
        communication_groups {
          group_ids: 0
          group_ids: 2
        }
        operand_ids: 92
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring"
          subroutine_root_id: 103
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 99
            bytes_out: 6
            communication_groups {
              group_ids: 0
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 100
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 100
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 101
            bytes_out: 6
            communication_groups {
              group_ids: 2
              group_ids: 0
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 102
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 102
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 0
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 103
            operand_ids: 99
            operand_ids: 101
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_conc"
        opcode: "all-gather"
        instruction_id: 104
        bytes_out: 48
        communication_groups {
          group_ids: 2
          group_ids: 3
        }
        operand_ids: 86
        operand_ids: 98
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_conc_bidir-ring"
          subroutine_root_id: 109
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 105
            bytes_out: 24
            communication_groups {
              group_ids: 2
              group_ids: 3
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 106
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 106
                bytes_in: 12
                bytes_out: 12
                communication_groups {
                  group_ids: 3
                  group_ids: 3
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 107
            bytes_out: 24
            communication_groups {
              group_ids: 3
              group_ids: 2
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 108
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 108
                bytes_in: 12
                bytes_out: 12
                communication_groups {
                  group_ids: 3
                  group_ids: 3
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_conc_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 109
            operand_ids: 105
            operand_ids: 107
          }
        }
      }
    }
  }
}
      )proto";
  google::protobuf::TextFormat::ParseFromString(test_str,
                                                &proto);
  return proto;
}  // NOLINT

// Tests expanding 2D-Torus all-reduce
TEST(Torus2dAllReduce, NoBarrier) {
  auto graph = absl::make_unique<paragraph::Graph>("test_graph", 2);
  auto sub = absl::make_unique<paragraph::Subroutine>(
      "test_subroutine", graph.get());
  auto sub_ptr = sub.get();
  sub_ptr->SetId(3);
  graph->SetEntrySubroutine(std::move(sub));

  ASSERT_OK_AND_ASSIGN(auto instr_1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "first_instruction", sub_ptr));
  instr_1->SetOps(4);

  ASSERT_OK_AND_ASSIGN(auto allreduce, paragraph::Instruction::Create(
      paragraph::Opcode::kAllReduce, "all-reduce", sub_ptr));
  allreduce->SetBytesOut(48);
  paragraph::CommunicationGroup allreduce_group = {0, 1, 2, 3, 4, 5, 6, 7};
  allreduce->AppendCommunicationGroup(allreduce_group);

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
  allreduce->AppendInnerSubroutine(std::move(reduction_sub));

  ASSERT_OK_AND_ASSIGN(auto instr_3, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "last_instruction", sub_ptr, true));
  instr_3->SetOps(4);

  nlohmann::json config = R"(
    {
      "all-reduce": {
        "algorithm": "torus-2d",
        "concentration": 2,
        "dimension_widths": [2, 2]
      }
    }
  )"_json;

  ASSERT_OK_AND_ASSIGN(auto translators, paragraph::CreateTranslators(
      paragraph::TranslatorType::kCollective, config));
  EXPECT_OK(translators["all-reduce"]->Translate(allreduce));

  paragraph::InstructionProto allreduce_proto = no_barrier_test_proto();
  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(
      allreduce->ToProto().value(), allreduce_proto));
}

paragraph::InstructionProto with_barrier_test_proto() {
  paragraph::InstructionProto proto;
  std::string test_str =
      R"proto(
name: "all-reduce"
opcode: "all-reduce"
instruction_id: 2
bytes_out: 48
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
  name: "all-reduce_torus-2d"
  subroutine_root_id: 167
  execution_probability: 1
  execution_count: 1
  instructions {
    name: "all-reduce_torus-2d_reduce-scatter"
    opcode: "reduce-scatter"
    instruction_id: 7
    bytes_out: 48
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
      name: "all-reduce_torus-2d_reduce-scatter_torus-2d"
      subroutine_root_id: 166
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0"
        opcode: "reduce-scatter"
        instruction_id: 8
        bytes_out: 24
        communication_groups {
          group_ids: 2
          group_ids: 3
          group_ids: 6
          group_ids: 7
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring"
          subroutine_root_id: 49
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 9
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized"
              subroutine_root_id: 16
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_3"
                opcode: "recv"
                instruction_id: 10
                communication_groups {
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_6"
                opcode: "recv"
                instruction_id: 11
                communication_groups {
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_7"
                opcode: "recv"
                instruction_id: 12
                communication_groups {
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_3"
                opcode: "send"
                instruction_id: 13
                communication_groups {
                  group_ids: 3
                }
                operand_ids: 10
                operand_ids: 11
                operand_ids: 12
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_6"
                opcode: "send"
                instruction_id: 14
                communication_groups {
                  group_ids: 6
                }
                operand_ids: 10
                operand_ids: 11
                operand_ids: 12
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_7"
                opcode: "send"
                instruction_id: 15
                communication_groups {
                  group_ids: 7
                }
                operand_ids: 10
                operand_ids: 11
                operand_ids: 12
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_barrier_centralized_root_2"
                opcode: "null"
                instruction_id: 16
                operand_ids: 13
                operand_ids: 14
                operand_ids: 15
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 17
            bytes_out: 12
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            operand_ids: 9
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 29
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 18
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 19
                operand_ids: 18
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 22
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 20
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 21
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 22
                    ops: 6
                    operand_ids: 20
                    operand_ids: 21
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 23
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 19
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 24
                operand_ids: 23
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 27
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 25
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 26
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 27
                    ops: 6
                    operand_ids: 25
                    operand_ids: 26
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 28
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 24
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_cw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 29
                operand_ids: 28
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 32
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 30
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 31
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 32
                    ops: 6
                    operand_ids: 30
                    operand_ids: 31
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 33
            bytes_out: 12
            communication_groups {
              group_ids: 7
              group_ids: 6
              group_ids: 3
              group_ids: 2
            }
            operand_ids: 9
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 45
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 34
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 35
                operand_ids: 34
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 38
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 36
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 37
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 38
                    ops: 6
                    operand_ids: 36
                    operand_ids: 37
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 39
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 35
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 40
                operand_ids: 39
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 43
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 41
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 42
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 43
                    ops: 6
                    operand_ids: 41
                    operand_ids: 42
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 44
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 40
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_ccw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 45
                operand_ids: 44
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 48
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 46
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 47
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 48
                    ops: 6
                    operand_ids: 46
                    operand_ids: 47
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 49
            operand_ids: 17
            operand_ids: 33
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1"
        opcode: "reduce-scatter"
        instruction_id: 50
        bytes_out: 6
        communication_groups {
          group_ids: 0
          group_ids: 2
          group_ids: 4
          group_ids: 6
        }
        operand_ids: 8
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring"
          subroutine_root_id: 86
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 51
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_barrier_centralized"
              subroutine_root_id: 53
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_barrier_centralized_send_to_0"
                opcode: "send"
                instruction_id: 52
                communication_groups {
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_barrier_centralized_recv_from_0"
                opcode: "recv"
                instruction_id: 53
                communication_groups {
                  group_ids: 0
                }
                operand_ids: 52
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 54
            bytes_out: 3
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            operand_ids: 51
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 66
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 55
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 56
                operand_ids: 55
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 59
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 57
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 58
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 59
                    ops: 1.5
                    operand_ids: 57
                    operand_ids: 58
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 60
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 56
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 61
                operand_ids: 60
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 64
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 62
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 63
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 64
                    ops: 1.5
                    operand_ids: 62
                    operand_ids: 63
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 65
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 61
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_cw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 66
                operand_ids: 65
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 69
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 67
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 68
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 69
                    ops: 1.5
                    operand_ids: 67
                    operand_ids: 68
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 70
            bytes_out: 3
            communication_groups {
              group_ids: 6
              group_ids: 4
              group_ids: 2
              group_ids: 0
            }
            operand_ids: 51
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 82
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 71
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 72
                operand_ids: 71
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 75
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 73
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 74
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 75
                    ops: 1.5
                    operand_ids: 73
                    operand_ids: 74
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 76
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 72
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 77
                operand_ids: 76
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 80
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 78
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 79
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 80
                    ops: 1.5
                    operand_ids: 78
                    operand_ids: 79
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 81
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 77
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_ccw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 82
                operand_ids: 81
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 85
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 83
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 84
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 85
                    ops: 1.5
                    operand_ids: 83
                    operand_ids: 84
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-0_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 86
            operand_ids: 54
            operand_ids: 70
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0"
        opcode: "reduce-scatter"
        instruction_id: 87
        bytes_out: 24
        communication_groups {
          group_ids: 0
          group_ids: 2
          group_ids: 4
          group_ids: 6
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring"
          subroutine_root_id: 123
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 88
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_barrier_centralized"
              subroutine_root_id: 90
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_barrier_centralized_send_to_0"
                opcode: "send"
                instruction_id: 89
                communication_groups {
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_barrier_centralized_recv_from_0"
                opcode: "recv"
                instruction_id: 90
                communication_groups {
                  group_ids: 0
                }
                operand_ids: 89
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 91
            bytes_out: 12
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            operand_ids: 88
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 103
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 92
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 93
                operand_ids: 92
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 96
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 94
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 95
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 96
                    ops: 6
                    operand_ids: 94
                    operand_ids: 95
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 97
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 93
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 98
                operand_ids: 97
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 101
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 99
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 100
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 101
                    ops: 6
                    operand_ids: 99
                    operand_ids: 100
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 102
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 98
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_cw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 103
                operand_ids: 102
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 106
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 104
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 105
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 106
                    ops: 6
                    operand_ids: 104
                    operand_ids: 105
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 107
            bytes_out: 12
            communication_groups {
              group_ids: 6
              group_ids: 4
              group_ids: 2
              group_ids: 0
            }
            operand_ids: 88
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 119
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 108
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 109
                operand_ids: 108
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 112
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 110
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 111
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 112
                    ops: 6
                    operand_ids: 110
                    operand_ids: 111
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 113
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 109
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 114
                operand_ids: 113
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 117
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 115
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 116
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 117
                    ops: 6
                    operand_ids: 115
                    operand_ids: 116
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 118
                bytes_in: 3
                bytes_out: 3
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 114
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_ccw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 119
                operand_ids: 118
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 122
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 120
                    bytes_out: 3
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 121
                    bytes_out: 3
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 122
                    ops: 6
                    operand_ids: 120
                    operand_ids: 121
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 123
            operand_ids: 91
            operand_ids: 107
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1"
        opcode: "reduce-scatter"
        instruction_id: 124
        bytes_out: 6
        communication_groups {
          group_ids: 2
          group_ids: 3
          group_ids: 6
          group_ids: 7
        }
        operand_ids: 87
        inner_subroutines {
          name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring"
          subroutine_root_id: 165
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 125
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized"
              subroutine_root_id: 132
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_3"
                opcode: "recv"
                instruction_id: 126
                communication_groups {
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_6"
                opcode: "recv"
                instruction_id: 127
                communication_groups {
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_7"
                opcode: "recv"
                instruction_id: 128
                communication_groups {
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_3"
                opcode: "send"
                instruction_id: 129
                communication_groups {
                  group_ids: 3
                }
                operand_ids: 126
                operand_ids: 127
                operand_ids: 128
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_6"
                opcode: "send"
                instruction_id: 130
                communication_groups {
                  group_ids: 6
                }
                operand_ids: 126
                operand_ids: 127
                operand_ids: 128
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_7"
                opcode: "send"
                instruction_id: 131
                communication_groups {
                  group_ids: 7
                }
                operand_ids: 126
                operand_ids: 127
                operand_ids: 128
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_barrier_centralized_root_2"
                opcode: "null"
                instruction_id: 132
                operand_ids: 129
                operand_ids: 130
                operand_ids: 131
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw"
            opcode: "reduce-scatter"
            instruction_id: 133
            bytes_out: 3
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            operand_ids: 125
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 145
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 134
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 135
                operand_ids: 134
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 138
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 136
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 137
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 138
                    ops: 1.5
                    operand_ids: 136
                    operand_ids: 137
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 139
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 135
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 140
                operand_ids: 139
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 143
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 141
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 142
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 143
                    ops: 1.5
                    operand_ids: 141
                    operand_ids: 142
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 144
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 140
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_cw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 145
                operand_ids: 144
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 148
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 146
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 147
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 148
                    ops: 1.5
                    operand_ids: 146
                    operand_ids: 147
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw"
            opcode: "reduce-scatter"
            instruction_id: 149
            bytes_out: 3
            communication_groups {
              group_ids: 7
              group_ids: 6
              group_ids: 3
              group_ids: 2
            }
            operand_ids: 125
            inner_subroutines {
              name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 161
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 150
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_reduction_1"
                opcode: "call"
                instruction_id: 151
                operand_ids: 150
                inner_subroutines {
                  name: "reduction_subroutine_phase_1"
                  subroutine_root_id: 154
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_1"
                    opcode: "delay"
                    instruction_id: 152
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_1"
                    opcode: "delay"
                    instruction_id: 153
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_1"
                    opcode: "delay"
                    instruction_id: 154
                    ops: 1.5
                    operand_ids: 152
                    operand_ids: 153
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 155
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 151
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_reduction_2"
                opcode: "call"
                instruction_id: 156
                operand_ids: 155
                inner_subroutines {
                  name: "reduction_subroutine_phase_2"
                  subroutine_root_id: 159
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_2"
                    opcode: "delay"
                    instruction_id: 157
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_2"
                    opcode: "delay"
                    instruction_id: 158
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_2"
                    opcode: "delay"
                    instruction_id: 159
                    ops: 1.5
                    operand_ids: 157
                    operand_ids: 158
                  }
                }
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 160
                bytes_in: 0.75
                bytes_out: 0.75
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 156
              }
              instructions {
                name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_ccw_unidir-ring_reduction_3"
                opcode: "call"
                instruction_id: 161
                operand_ids: 160
                inner_subroutines {
                  name: "reduction_subroutine_phase_3"
                  subroutine_root_id: 164
                  execution_probability: 1
                  execution_count: 1
                  instructions {
                    name: "op1_phase_3"
                    opcode: "delay"
                    instruction_id: 162
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "op2_phase_3"
                    opcode: "delay"
                    instruction_id: 163
                    bytes_out: 0.75
                  }
                  instructions {
                    name: "sum_phase_3"
                    opcode: "delay"
                    instruction_id: 164
                    ops: 1.5
                    operand_ids: 162
                    operand_ids: 163
                  }
                }
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_reduce-scatter_stream-1_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 165
            operand_ids: 133
            operand_ids: 149
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_reduce-scatter_root"
        opcode: "null"
        instruction_id: 166
        operand_ids: 50
        operand_ids: 124
      }
    }
  }
  instructions {
    name: "all-reduce_torus-2d_all-gather"
    opcode: "all-gather"
    instruction_id: 167
    bytes_out: 48
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
    operand_ids: 7
    inner_subroutines {
      name: "all-reduce_torus-2d_all-gather_torus-2d"
      subroutine_root_id: 230
      execution_probability: 1
      execution_count: 1
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-0_stage-0"
        opcode: "all-gather"
        instruction_id: 168
        bytes_out: 12
        communication_groups {
          group_ids: 2
          group_ids: 3
          group_ids: 6
          group_ids: 7
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring"
          subroutine_root_id: 185
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 169
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized"
              subroutine_root_id: 176
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_3"
                opcode: "recv"
                instruction_id: 170
                communication_groups {
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_6"
                opcode: "recv"
                instruction_id: 171
                communication_groups {
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_recv_from_7"
                opcode: "recv"
                instruction_id: 172
                communication_groups {
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_3"
                opcode: "send"
                instruction_id: 173
                communication_groups {
                  group_ids: 3
                }
                operand_ids: 170
                operand_ids: 171
                operand_ids: 172
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_6"
                opcode: "send"
                instruction_id: 174
                communication_groups {
                  group_ids: 6
                }
                operand_ids: 170
                operand_ids: 171
                operand_ids: 172
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_coordinator_send_to_7"
                opcode: "send"
                instruction_id: 175
                communication_groups {
                  group_ids: 7
                }
                operand_ids: 170
                operand_ids: 171
                operand_ids: 172
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_barrier_centralized_root_2"
                opcode: "null"
                instruction_id: 176
                operand_ids: 173
                operand_ids: 174
                operand_ids: 175
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 177
            bytes_out: 6
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            operand_ids: 169
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 180
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 178
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 179
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 178
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 180
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 179
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 181
            bytes_out: 6
            communication_groups {
              group_ids: 7
              group_ids: 6
              group_ids: 3
              group_ids: 2
            }
            operand_ids: 169
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 184
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 182
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 183
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 182
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 184
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 183
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 185
            operand_ids: 177
            operand_ids: 181
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-0_stage-1"
        opcode: "all-gather"
        instruction_id: 186
        bytes_out: 48
        communication_groups {
          group_ids: 0
          group_ids: 2
          group_ids: 4
          group_ids: 6
        }
        operand_ids: 168
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring"
          subroutine_root_id: 198
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 187
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_barrier_centralized"
              subroutine_root_id: 189
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_barrier_centralized_send_to_0"
                opcode: "send"
                instruction_id: 188
                communication_groups {
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_barrier_centralized_recv_from_0"
                opcode: "recv"
                instruction_id: 189
                communication_groups {
                  group_ids: 0
                }
                operand_ids: 188
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 190
            bytes_out: 24
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            operand_ids: 187
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 193
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 191
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 192
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 191
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 193
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 192
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 194
            bytes_out: 24
            communication_groups {
              group_ids: 6
              group_ids: 4
              group_ids: 2
              group_ids: 0
            }
            operand_ids: 187
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 197
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 195
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 196
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 195
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 197
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 196
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-0_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 198
            operand_ids: 190
            operand_ids: 194
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-1_stage-0"
        opcode: "all-gather"
        instruction_id: 199
        bytes_out: 12
        communication_groups {
          group_ids: 0
          group_ids: 2
          group_ids: 4
          group_ids: 6
        }
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring"
          subroutine_root_id: 211
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 200
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_barrier_centralized"
              subroutine_root_id: 202
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_barrier_centralized_send_to_0"
                opcode: "send"
                instruction_id: 201
                communication_groups {
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_barrier_centralized_recv_from_0"
                opcode: "recv"
                instruction_id: 202
                communication_groups {
                  group_ids: 0
                }
                operand_ids: 201
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 203
            bytes_out: 6
            communication_groups {
              group_ids: 0
              group_ids: 2
              group_ids: 4
              group_ids: 6
            }
            operand_ids: 200
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 206
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 204
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 205
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 204
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 206
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 0
                  group_ids: 4
                }
                operand_ids: 205
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 207
            bytes_out: 6
            communication_groups {
              group_ids: 6
              group_ids: 4
              group_ids: 2
              group_ids: 0
            }
            operand_ids: 200
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 210
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 208
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 209
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 208
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 210
                bytes_in: 1.5
                bytes_out: 1.5
                communication_groups {
                  group_ids: 4
                  group_ids: 0
                }
                operand_ids: 209
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-0_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 211
            operand_ids: 203
            operand_ids: 207
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_stream-1_stage-1"
        opcode: "all-gather"
        instruction_id: 212
        bytes_out: 48
        communication_groups {
          group_ids: 2
          group_ids: 3
          group_ids: 6
          group_ids: 7
        }
        operand_ids: 199
        inner_subroutines {
          name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring"
          subroutine_root_id: 229
          execution_probability: 1
          execution_count: 1
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier"
            opcode: "barrier"
            instruction_id: 213
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized"
              subroutine_root_id: 220
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_3"
                opcode: "recv"
                instruction_id: 214
                communication_groups {
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_6"
                opcode: "recv"
                instruction_id: 215
                communication_groups {
                  group_ids: 6
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_recv_from_7"
                opcode: "recv"
                instruction_id: 216
                communication_groups {
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_3"
                opcode: "send"
                instruction_id: 217
                communication_groups {
                  group_ids: 3
                }
                operand_ids: 214
                operand_ids: 215
                operand_ids: 216
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_6"
                opcode: "send"
                instruction_id: 218
                communication_groups {
                  group_ids: 6
                }
                operand_ids: 214
                operand_ids: 215
                operand_ids: 216
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_coordinator_send_to_7"
                opcode: "send"
                instruction_id: 219
                communication_groups {
                  group_ids: 7
                }
                operand_ids: 214
                operand_ids: 215
                operand_ids: 216
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_barrier_centralized_root_2"
                opcode: "null"
                instruction_id: 220
                operand_ids: 217
                operand_ids: 218
                operand_ids: 219
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw"
            opcode: "all-gather"
            instruction_id: 221
            bytes_out: 24
            communication_groups {
              group_ids: 2
              group_ids: 3
              group_ids: 6
              group_ids: 7
            }
            operand_ids: 213
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring"
              subroutine_root_id: 224
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 222
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 223
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 222
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_cw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 224
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 7
                  group_ids: 3
                }
                operand_ids: 223
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw"
            opcode: "all-gather"
            instruction_id: 225
            bytes_out: 24
            communication_groups {
              group_ids: 7
              group_ids: 6
              group_ids: 3
              group_ids: 2
            }
            operand_ids: 213
            inner_subroutines {
              name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring"
              subroutine_root_id: 228
              execution_probability: 1
              execution_count: 1
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_1"
                opcode: "sendrecv"
                instruction_id: 226
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_2"
                opcode: "sendrecv"
                instruction_id: 227
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 226
              }
              instructions {
                name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_ccw_unidir-ring_sendrecv_3"
                opcode: "sendrecv"
                instruction_id: 228
                bytes_in: 6
                bytes_out: 6
                communication_groups {
                  group_ids: 3
                  group_ids: 7
                }
                operand_ids: 227
              }
            }
          }
          instructions {
            name: "all-reduce_torus-2d_all-gather_stream-1_stage-1_bidir-ring_root_2"
            opcode: "null"
            instruction_id: 229
            operand_ids: 221
            operand_ids: 225
          }
        }
      }
      instructions {
        name: "all-reduce_torus-2d_all-gather_root"
        opcode: "null"
        instruction_id: 230
        operand_ids: 186
        operand_ids: 212
      }
    }
  }
}
      )proto";
  google::protobuf::TextFormat::ParseFromString(test_str,
                                                &proto);
  return proto;
}  // NOLINT

// Tests expanding 2D-Torus all-reduce with barrier
TEST(Torus2dAllReduce, WithBarrier) {
  auto graph = absl::make_unique<paragraph::Graph>("test_graph", 2);
  auto sub = absl::make_unique<paragraph::Subroutine>(
      "test_subroutine", graph.get());
  auto sub_ptr = sub.get();
  sub_ptr->SetId(3);
  graph->SetEntrySubroutine(std::move(sub));

  ASSERT_OK_AND_ASSIGN(auto instr_1, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "first_instruction", sub_ptr));
  instr_1->SetOps(4);

  ASSERT_OK_AND_ASSIGN(auto allreduce, paragraph::Instruction::Create(
      paragraph::Opcode::kAllReduce, "all-reduce", sub_ptr));
  allreduce->SetBytesOut(48);
  paragraph::CommunicationGroup allreduce_group = {0, 1, 2, 3, 4, 5, 6, 7};
  allreduce->AppendCommunicationGroup(allreduce_group);

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
  allreduce->AppendInnerSubroutine(std::move(reduction_sub));

  ASSERT_OK_AND_ASSIGN(auto instr_3, paragraph::Instruction::Create(
      paragraph::Opcode::kDelay, "last_instruction", sub_ptr, true));
  instr_3->SetOps(4);

  nlohmann::json config = R"(
    {
      "all-reduce": {
        "algorithm": "torus-2d",
        "dimension_widths": [2, 2],
        "barrier": {
          "algorithm": "centralized"
        }
      }
    }
  )"_json;

  ASSERT_OK_AND_ASSIGN(auto translators, paragraph::CreateTranslators(
      paragraph::TranslatorType::kCollective, config));
  EXPECT_OK(translators["all-reduce"]->Translate(allreduce));

  paragraph::InstructionProto allreduce_proto = with_barrier_test_proto();
  EXPECT_TRUE(google::protobuf::util::MessageDifferencer::Equals(
      allreduce->ToProto().value(), allreduce_proto));
}
