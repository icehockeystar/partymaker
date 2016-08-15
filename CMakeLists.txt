project(partymaker)
cmake_minimum_required(VERSION 2.8.12)

set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -g")

subdirs(src)
subdirs(test)

include(build/conanbuildinfo.cmake)
conan_basic_setup()
