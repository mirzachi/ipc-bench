###########################################################
## CONFIGURATION
###########################################################

# Injecting in process.c
add_definitions( -DBUILD_PATH="${PROJECT_BINARY_DIR}/source" )

add_compile_options( -g -O3 -Wall )

link_libraries( m )
link_libraries( pthread )
link_libraries( rt )

###########################################################
## DEPENDENCIES
###########################################################

## pthread
find_package( Threads REQUIRED )

## ZMQ
find_package( ZeroMQ 4.3.3 EXACT REQUIRED CONFIG )

## nng
find_package( nng 1.4.0 EXACT REQUIRED CONFIG )

## nanomsg
find_package( nanomsg 1.1.5 EXACT REQUIRED CONFIG )

# Our required dependencies are libdbus and libsigc++
find_package( PkgConfig REQUIRED )
pkg_check_modules( dbus REQUIRED dbus-1>=1.3 )
pkg_check_modules( sigc REQUIRED sigc++-2.0 )
pkg_check_modules( dbus-cxx REQUIRED dbus-cxx-1.0 )

###########################################################
## SUBDIRECTORIES
###########################################################

add_subdirectory( common )
add_subdirectory( tcp )
add_subdirectory( shm )
add_subdirectory( mmap )
add_subdirectory( fifo )
add_subdirectory( pipe )
add_subdirectory( domain )
add_subdirectory( mq )
add_subdirectory( signal )
add_subdirectory( shm-sync )
add_subdirectory( eventfd )

if ( ZeroMQ_FOUND )
    add_subdirectory( zeromq )
    add_subdirectory( zeromq-sub )
endif ()

if ( nng_FOUND )
    add_subdirectory( nng )
    add_subdirectory( nng-sub )
endif ()

if ( nanomsg_FOUND )
    add_subdirectory( nanomsg )
    add_subdirectory( nanomsg-sub )
endif ()

if ( dbus-cxx_FOUND )
    add_subdirectory( dbus )
endif ()
