cmake_minimum_required(VERSION 2.8)

project(army)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_LIB army.cpp)
add_library(army STATIC ${SOURCE_LIB})

set(SOURCE_LIB items.cpp)
add_library(items STATIC ${SOURCE_LIB})

target_link_libraries(items army)
target_link_libraries(army items)

set(SOURCE_LIB aliance.cpp)
add_library(aliance STATIC ${SOURCE_LIB})
target_link_libraries(aliance army)

set(SOURCE_LIB horde.cpp)
add_library(horde STATIC ${SOURCE_LIB})
target_link_libraries(horde army)
