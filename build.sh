#!/bin/bash

mkdir build;
cd build;

conan install .. --install-folder cmake-build-release --build=outdated;
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake-build-release/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Debug;

ninja all;