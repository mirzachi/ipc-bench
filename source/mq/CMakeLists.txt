###########################################################
## TARGETS
###########################################################

add_executable(mq-client client.c mq-common.c)
add_executable(mq-server server.c mq-common.c)
add_executable(mq mq.c mq-common.c)

###########################################################
## COMMON
###########################################################
target_include_directories(mq-client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mq-client ipc-bench-common)
target_include_directories(mq-server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(mq-server ipc-bench-common)
target_link_libraries(mq ipc-bench-common)
