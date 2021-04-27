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
