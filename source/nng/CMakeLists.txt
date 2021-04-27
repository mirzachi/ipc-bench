###########################################################
## DEPENDENCIES
###########################################################

if (NOT nng_FOUND)
    message(FATAL_ERROR "nng not found!")
endif()

include_directories(${nng_INCLUDE_DIRS})

###########################################################
## TARGETS
###########################################################

add_executable(nng-client client.c)
add_executable(nng-server server.c)
add_executable(nng nng.c)

###########################################################
## COMMON
###########################################################
target_link_libraries(nng-server ipc-bench-common nng::nng)
target_link_libraries(nng-client ipc-bench-common nng::nng)
target_link_libraries(nng ipc-bench-common nng::nng)
