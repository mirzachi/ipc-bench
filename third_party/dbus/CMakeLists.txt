cmake_minimum_required(VERSION 3.14)

# make the ExternalProject commands available
include(ExternalProject)

# enable seeing GIT clone progress
set(FETCHCONTENT_QUIET FALSE)

# dbus version
set(dbus_VERSION 1.13.18)

# download, configure, build and install the dependency
# note: The install location is set to the local path
ExternalProject_Add(
        dbus
        GIT_REPOSITORY https://github.com/freedesktop/dbus.git
        GIT_TAG dbus-${dbus_VERSION}
        CMAKE_ARGS
        -DDBUS_BUILD_TESTS=OFF
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=${LOCAL_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_DIR}
)

# dbus-cxx version
set(dbus-cxx_VERSION 0.12.0)

# download, configure, build and install the dependency
# note: The install location is set to the local path
ExternalProject_Add(
        dbusc-cxx
        GIT_REPOSITORY https://github.com/dbus-cxx/dbus-cxx.git
        GIT_TAG ${dbus-cxx_VERSION}
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=${LOCAL_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_DIR}
)


