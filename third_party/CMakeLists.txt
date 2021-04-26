cmake_minimum_required(VERSION 3.14)

project(
        third-party-dependencies
        VERSION 1.0
        DESCRIPTION "Project third-party dependencies"
        LANGUAGES CXX
)

# set local install path for the third party libs
set(LOCAL_INSTALL_DIR "${CMAKE_SOURCE_DIR}/../temp/third_party/install")

add_subdirectory(zmq)
add_subdirectory(nng)
add_subdirectory(nanomsg)
