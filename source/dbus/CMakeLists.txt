###########################################################
## TARGETS
###########################################################

add_executable( dbus-client client.cc )
add_executable( dbus-server server.cc )
add_executable( dbus dbus.cc )

###########################################################
## COMMON
###########################################################

target_compile_options( dbus-client PRIVATE -Wno-uninitialized -Wno-write-strings )
target_compile_options( dbus-server PRIVATE -Wno-uninitialized -Wno-write-strings )
target_compile_options( dbus PRIVATE -Wno-uninitialized -Wno-write-strings )

target_include_directories( dbus-client PRIVATE ${dbus-cxx_INCLUDE_DIRS} )
target_include_directories( dbus-server PRIVATE ${dbus-cxx_INCLUDE_DIRS} )

target_link_directories( dbus-server PRIVATE ${dbus-cxx_LIBRARY_DIRS} )
target_link_libraries( dbus-server PRIVATE ipc-bench-common ${dbus-cxx_LIBRARIES} )
target_link_directories( dbus-client PRIVATE ${dbus-cxx_LIBRARY_DIRS} )
target_link_libraries( dbus-client PRIVATE ipc-bench-common ${dbus-cxx_LIBRARIES} )
target_link_libraries( dbus PRIVATE ipc-bench-common )
