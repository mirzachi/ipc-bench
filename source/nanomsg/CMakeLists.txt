###########################################################
## TARGETS
###########################################################

add_executable(nanomsg-client client.c)
add_executable(nanomsg-server server.c)
add_executable(nanomsg-exec nanomsg.c)
set_target_properties(nanomsg-exec PROPERTIES OUTPUT_NAME "nanomsg")

###########################################################
## COMMON
###########################################################

target_link_libraries(nanomsg-server ipc-bench-common nanomsg)
target_link_libraries(nanomsg-client ipc-bench-common nanomsg)
target_link_libraries(nanomsg-exec ipc-bench-common nanomsg)
