###########################################################
## TARGETS
###########################################################

add_executable( dbus-client client.cc )
add_executable( dbus-server server.cc )
add_executable( dbus dbus.c )

###########################################################
## COMMON
###########################################################

target_include_directories( dbus-client PRIVATE ${dbus-cxx_INCLUDE_DIRS} )
target_include_directories( dbus-server PRIVATE ${dbus-cxx_INCLUDE_DIRS} )

target_link_directories( dbus-server PRIVATE ${dbus-cxx_LIBRARY_DIRS} )
target_link_libraries( dbus-server PRIVATE ipc-bench-common ${dbus-cxx_LIBRARIES} )
target_link_directories( dbus-client PRIVATE ${dbus-cxx_LIBRARY_DIRS} )
target_link_libraries( dbus-client PRIVATE ipc-bench-common ${dbus-cxx_LIBRARIES} )
target_link_libraries( dbus PRIVATE ipc-bench-common )
