###########################################################
## TARGETS
###########################################################

add_executable(nng-sub-client client.c)
add_executable(nng-sub-server server.c)
add_executable(nng-sub nng-sub.c )

###########################################################
## COMMON
###########################################################

target_link_libraries(nng-sub-server ipc-bench-common nng::nng)
target_link_libraries(nng-sub-client ipc-bench-common nng::nng)
target_link_libraries(nng-sub ipc-bench-common nng::nng)
