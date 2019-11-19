#!/bin/bash

conan profile new default --detect
conan profile update settings.compiler.libcxx=libstdc++11 default
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
rm -rf cmake-build-debug
mkdir cmake-build-debug;
cd cmake-build-debug || exit
conan install .. --build=missing -s build_type=Debug
# cmake .. -DCMAKE_BUILD_TYPE=Debug
# cmake --build .
cd ..
rm -rf cmake-build-release
mkdir cmake-build-release;
cd cmake-build-release || exit
conan install .. --build=missing -s build_type=Release
# cmake .. -DCMAKE_BUILD_TYPE=Release
# cmake --build .
cd ..
