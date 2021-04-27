###########################################################
## TARGETS
###########################################################

add_executable(nanomsg-sub-client client.c)
add_executable(nanomsg-sub-server server.c)
add_executable(nanomsg-sub nanomsg-sub.c )

###########################################################
## COMMON
###########################################################

target_link_libraries(nanomsg-sub-server ipc-bench-common nanomsg)
target_link_libraries(nanomsg-sub-client ipc-bench-common nanomsg)
target_link_libraries(nanomsg-sub ipc-bench-common nanomsg)