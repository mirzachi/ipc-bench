###########################################################
## TARGETS
###########################################################

add_executable(zeromq-sub-client client.c)
add_executable(zeromq-sub-server server.c)
add_executable(zeromq-sub zeromq-sub.c )

###########################################################
## COMMON
###########################################################

target_link_libraries(zeromq-sub-server ipc-bench-common libzmq)
target_link_libraries(zeromq-sub-client ipc-bench-common libzmq)
target_link_libraries(zeromq-sub ipc-bench-common libzmq)
