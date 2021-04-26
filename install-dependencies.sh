#!/bin/bash

# dbus dependencies
#sudo apt-get install libexpat-dev libsigc++-2.0-dev m4

temp_build_dir="./temp/third_party/build"
mkdir -p "${temp_build_dir}"

cmake -B ${temp_build_dir} -S third_party
cmake --build ${temp_build_dir} --parallel 8
cmake --install ${temp_build_dir}
