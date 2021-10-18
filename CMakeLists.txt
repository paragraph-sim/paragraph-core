cmake_minimum_required(VERSION 3.20)
project(paragraph-core)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FindPkgConfig)

# absl
find_package(absl REQUIRED)
get_target_property(
  ABSL_BASE_INC
  absl::base
  INTERFACE_INCLUDE_DIRECTORIES
  )
list(APPEND ABSL_LIBS
  absl::bad_any_cast_impl
  absl::bad_optional_access
  absl::bad_variant_access
  absl::base
  absl::city
  absl::civil_time
  absl::cord
  absl::debugging_internal
  absl::demangle_internal
  absl::examine_stack
  absl::exponential_biased
  absl::failure_signal_handler
  absl::flags_commandlineflag_internal
  absl::flags_commandlineflag
  absl::flags_config
  absl::flags_internal
  absl::flags_marshalling
  absl::flags_parse
  absl::flags_private_handle_accessor
  absl::flags_program_name
  absl::flags_reflection
  absl::flags
  absl::flags_usage_internal
  absl::flags_usage
  absl::graphcycles_internal
  absl::hash
  absl::hashtablez_sampler
  absl::int128
  absl::leak_check_disable
  absl::leak_check
  absl::log_severity
  absl::malloc_internal
  absl::periodic_sampler
  absl::random_distributions
  absl::random_internal_distribution_test_util
  absl::random_internal_platform
  absl::random_internal_pool_urbg
  absl::random_internal_randen_hwaes_impl
  absl::random_internal_randen_hwaes
  absl::random_internal_randen_slow
  absl::random_internal_randen
  absl::random_internal_seed_material
  absl::random_seed_gen_exception
  absl::random_seed_sequences
  absl::raw_hash_set
  absl::raw_logging_internal
  absl::scoped_set_env
  absl::spinlock_wait
  absl::stacktrace
  absl::statusor
  absl::status
  absl::strerror
  absl::str_format_internal
  absl::strings_internal
  absl::strings
  absl::symbolize
  absl::synchronization
  absl::throw_delegate
  absl::time
  absl::time_zone
  )

# protobuf
find_package(Protobuf REQUIRED)
get_target_property(
  PROTOBUF_INC
  protobuf::libprotobuf
  INTERFACE_INCLUDE_DIRECTORIES
  )

# libfactory
pkg_check_modules(libfactory REQUIRED IMPORTED_TARGET libfactory)
get_target_property(
  LIBFACTORY_INC
  PkgConfig::libfactory
  INTERFACE_INCLUDE_DIRECTORIES
)

# nlohmann_json
pkg_check_modules(nlohmann_json REQUIRED IMPORTED_TARGET nlohmann_json)
  get_target_property(
  NLOHMANN_JSON_INC
  PkgConfig::nlohmann_json
  INTERFACE_INCLUDE_DIRECTORIES
)

# compiles protobufs
add_subdirectory(
  ${PROJECT_SOURCE_DIR}/paragraph/graph/
  ${CMAKE_CURRENT_BINARY_DIR}/paragraph/graph/
  )

add_library(
  paragraph
  SHARED
  $<TARGET_OBJECTS:paragraph_proto>
  ${PROJECT_SOURCE_DIR}/paragraph/graph/graph.cc
  ${PROJECT_SOURCE_DIR}/paragraph/graph/subroutine.cc
  ${PROJECT_SOURCE_DIR}/paragraph/graph/instruction.cc
  ${PROJECT_SOURCE_DIR}/paragraph/graph/opcode.cc
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/instruction_fsm.cc
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/logger.cc
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/graph_scheduler.cc
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/subroutine_fsm.cc
  ${PROJECT_SOURCE_DIR}/paragraph/simulator/simple_sim.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation_map.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/utils.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/push_recv_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/recv_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/sendrecv_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/push_sendrecv_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/ring_over_2d_grid_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_1d_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_2d_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/torus_2d_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/bidir_ring_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/unidir_ring_reducescatter_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_2d_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/torus_2d_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_1d_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/bidir_ring_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/ring_over_2d_grid_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/unidir_ring_allgather_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/unidir_ring_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/ring_over_2d_grid_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_2d_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/torus_2d_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_1d_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/bidir_ring_allreduce_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/barrier_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/centralized_barrier_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/push_send_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/send_translator.cc
  ${PROJECT_SOURCE_DIR}/paragraph/graph/graph.h
  ${PROJECT_SOURCE_DIR}/paragraph/graph/subroutine.h
  ${PROJECT_SOURCE_DIR}/paragraph/graph/instruction.h
  ${PROJECT_SOURCE_DIR}/paragraph/graph/opcode.h
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/subroutine_fsm.h
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/logger.h
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/instruction_fsm.h
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/graph_scheduler.h
  ${PROJECT_SOURCE_DIR}/paragraph/simulator/simple_sim.h
  ${PROJECT_SOURCE_DIR}/paragraph/shim/test_macros.h
  ${PROJECT_SOURCE_DIR}/paragraph/shim/macros.h
  ${PROJECT_SOURCE_DIR}/paragraph/shim/statusor.h
  ${PROJECT_SOURCE_DIR}/paragraph/shim/statusor_internals.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation_map.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/utils.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/recv_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/push_recv_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/sendrecv_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/push_sendrecv_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_2d_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_1d_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/unidir_ring_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/bidir_ring_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/torus_2d_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/ring_over_2d_grid_reducescatter_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/bidir_ring_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_1d_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/torus_2d_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/ring_over_2d_grid_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/unidir_ring_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_2d_allgather_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/unidir_ring_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/torus_2d_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/ring_over_2d_grid_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_2d_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/bidir_ring_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_1d_allreduce_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/barrier_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/centralized_barrier_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/push_send_translator.h
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/send_translator.h
  )

set_target_properties(
  paragraph
  PROPERTIES
  LINKER_LANGUAGE
  CXX
  POSITION_INDEPENDENT_CODE
  ON
  )

target_include_directories(
  paragraph
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROTOBUF_INC}
  ${ABSL_BASE_INC}
  ${LIBFACTORY_INC}
  ${NLOHMANN_JSON_INC}
  )

target_link_libraries(
  paragraph
  PUBLIC
  protobuf::libprotobuf
  "${ABSL_LIBS}"
  PkgConfig::libfactory
  )

include(GNUInstallDirs)

install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/paragraph/graph/graph.pb.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/graph/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/graph/graph.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/graph/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/graph/subroutine.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/graph/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/graph/instruction.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/graph/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/graph/opcode.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/graph/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/subroutine_fsm.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/scheduling/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/logger.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/scheduling/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/instruction_fsm.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/scheduling/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/scheduling/graph_scheduler.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/scheduling/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/simulator/simple_sim.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/simulator/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/shim/test_macros.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/shim/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/shim/macros.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/shim/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/shim/statusor.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/shim/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/shim/statusor_internals.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/shim/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translation_map.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/utils.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/recv_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/recv/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/recv/push_recv_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/recv/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/sendrecv_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/sendrecv/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/sendrecv/push_sendrecv_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/sendrecv/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_2d_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/mesh_1d_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/unidir_ring_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/bidir_ring_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/torus_2d_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/reducescatter/ring_over_2d_grid_reducescatter_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/reducescatter/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/bidir_ring_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_1d_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/torus_2d_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/ring_over_2d_grid_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/unidir_ring_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allgather/mesh_2d_allgather_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allgather/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/unidir_ring_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/torus_2d_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/ring_over_2d_grid_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_2d_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/bidir_ring_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/allreduce/mesh_1d_allreduce_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/allreduce/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/barrier_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/barrier/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/barrier/centralized_barrier_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/barrier/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/push_send_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/send/
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/paragraph/translation/send/send_translator.h
  DESTINATION
  ${CMAKE_INSTALL_INCLUDEDIR}/paragraph/translation/send/
  )

install(
  TARGETS
  paragraph
  )

configure_file(
  ${PROJECT_SOURCE_DIR}/libparagraph.pc.in
  ${CMAKE_CURRENT_BINARY_DIR}/libparagraph.pc
  @ONLY
  )
install(
  FILES
  ${CMAKE_CURRENT_BINARY_DIR}/libparagraph.pc
  DESTINATION
  ${CMAKE_INSTALL_LIBDIR}/pkgconfig/
  )

add_executable(
  graph_converter
  ${PROJECT_SOURCE_DIR}/paragraph/graph/graph_converter.cc
  )

target_include_directories(
  graph_converter
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROTOBUF_INC}
  ${ABSL_BASE_INC}
  ${LIBFACTORY_INC}
  ${NLOHMANN_JSON_INC}
  )

target_link_libraries(
  graph_converter
  protobuf::libprotobuf
  "${ABSL_LIBS}"
  PkgConfig::libfactory
  paragraph
  )

install(
  TARGETS
  graph_converter
  )

add_executable(
  graph_translator
  ${PROJECT_SOURCE_DIR}/paragraph/translation/graph_translator.cc
  )

target_include_directories(
  graph_translator
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROTOBUF_INC}
  ${ABSL_BASE_INC}
  ${LIBFACTORY_INC}
  ${NLOHMANN_JSON_INC}
  )

target_link_libraries(
  graph_translator
  protobuf::libprotobuf
  "${ABSL_LIBS}"
  PkgConfig::libfactory
  paragraph
  )

install(
  TARGETS
  graph_translator
  )

add_executable(
  simulator
  ${PROJECT_SOURCE_DIR}/paragraph/simulator/simulator.cc
  )

target_include_directories(
  simulator
  PUBLIC
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${PROTOBUF_INC}
  ${ABSL_BASE_INC}
  ${LIBFACTORY_INC}
  ${NLOHMANN_JSON_INC}
  )

target_link_libraries(
  simulator
  protobuf::libprotobuf
  "${ABSL_LIBS}"
  PkgConfig::libfactory
  paragraph
  )

install(
  TARGETS
  simulator
  )
