###########################################################
## TARGETS
###########################################################

add_executable(zeromq-client client.c)
add_executable(zeromq-server server.c)
add_executable(zeromq zeromq.c)

###########################################################
## COMMON
###########################################################

target_link_libraries(zeromq-server ipc-bench-common libzmq)
target_link_libraries(zeromq-client ipc-bench-common libzmq)
target_link_libraries(zeromq ipc-bench-common libzmq)
