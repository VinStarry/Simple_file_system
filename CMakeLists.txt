cmake_minimum_required(VERSION 3.12)
project(vfs C)

set(CMAKE_C_STANDARD 11)

add_definitions(-std=c++11)

include_directories(${PROJECT_SOURCE_DIR}/include)

aux_source_directory(${PROJECT_SOURCE_DIR}/src SRC_LIST)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

add_executable(vfs ${SRC_LIST})