###########################################################
## SOURCES
###########################################################

set( IPC_BENCH_COMMON_SOURCES
     ${CMAKE_CURRENT_SOURCE_DIR}/src/utility.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/benchmarks.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/signals.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/arguments.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/process.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/sockets.c
     ${CMAKE_CURRENT_SOURCE_DIR}/src/parent.c
     )

###########################################################
## TARGETS
###########################################################

add_library( ipc-bench-common STATIC ${IPC_BENCH_COMMON_SOURCES} )
target_include_directories( ipc-bench-common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include )
target_compile_options( ipc-bench-common PUBLIC -fPIC )
