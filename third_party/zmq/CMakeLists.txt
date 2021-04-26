cmake_minimum_required(VERSION 3.14)

# make the ExternalProject commands available
include(ExternalProject)

# enable seeing GIT clone progress
set(FETCHCONTENT_QUIET FALSE)

# zmq version
set(zmq_VERSION 4.3.3)

# download, configure, build and install the dependency
# note: The install location is set to the local path
ExternalProject_Add(
        zmq
        GIT_REPOSITORY https://github.com/zeromq/libzmq.git
        GIT_TAG v${zmq_VERSION}
        GIT_PROGRESS TRUE
        CMAKE_ARGS -DENABLE_WS=OFF
        -DENABLE_CURVE=OFF
        -DWITH_DOC=OFF
        -DBUILD_TESTS=OFF
        -DWITH_PERF_TOOL=OFF
        -DBUILD_STATIC=ON
        -DBUILD_SHARED=ON
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=${LOCAL_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_DIR}
)
