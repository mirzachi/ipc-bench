cmake_minimum_required(VERSION 3.14)

# make the ExternalProject commands available
include(ExternalProject)

# enable seeing GIT clone progress
set(FETCHCONTENT_QUIET FALSE)

# nng version
set(nng_VERSION 1.4.0)

# download, configure, build and install the dependency
# note: The install location is set to the local path
ExternalProject_Add(
        nng
        GIT_REPOSITORY https://github.com/nanomsg/nng.git
        GIT_TAG v${nng_VERSION}
        CMAKE_ARGS
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=${LOCAL_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_DIR}
)
