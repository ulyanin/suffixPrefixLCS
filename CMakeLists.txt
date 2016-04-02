cmake_minimum_required(VERSION 3.4)
project(suffixPrefixLCS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp suffix_prefix_lcs.cpp)
add_executable(suffixPrefixLCS ${SOURCE_FILES})