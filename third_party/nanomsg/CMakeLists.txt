cmake_minimum_required(VERSION 3.14)

# make the ExternalProject commands available
include(ExternalProject)

# enable seeing GIT clone progress
set(FETCHCONTENT_QUIET FALSE)

# nanomsg version
set(nanomsg_VERSION 1.1.5)

# download, configure, build and install the dependency
# note: The install location is set to the local path
ExternalProject_Add(
        nanomsg
        GIT_REPOSITORY https://github.com/nanomsg/nanomsg.git
        GIT_TAG ${nanomsg_VERSION}
        CMAKE_ARGS
        -DNN_ENABLE_DOC=OFF
        -DNN_TESTS=OFF
        -DNN_TOOLS=OFF
        -DCMAKE_BUILD_TYPE=Release
        -DCMAKE_PREFIX_PATH=${LOCAL_INSTALL_DIR}
        -DCMAKE_INSTALL_PREFIX=${LOCAL_INSTALL_DIR}
)
