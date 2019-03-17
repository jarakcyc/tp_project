cmake_minimum_required(VERSION 2.8)

project(project)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_EXE main.cpp)

include_directories(./army)

add_executable(main ${SOURCE_EXE})

add_subdirectory(army)

target_link_libraries(main army)
target_link_libraries(main horde)
target_link_libraries(main aliance)
