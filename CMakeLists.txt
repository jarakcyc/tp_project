cmake_minimum_required(VERSION 2.8)

project(project)

#find_package(GTest REQUIRED)
#include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

set(SOURCE_EXE main.cpp)

include_directories(./army)

add_executable(main ${SOURCE_EXE})

add_subdirectory(army)

target_link_libraries(main army)
target_link_libraries(main horde)
target_link_libraries(main aliance)

#---------------------GTEST-------------------------------

option(BUILD_TESTS "Build unit tests" OFF)

if (BUILD_TESTS)
	add_subdirectory(ext/gtest-1.8.0)
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

	set(SOURCE_EXE tests.cpp)

	add_executable(tests ${SOURCE_EXE})

	target_link_libraries(tests army)
	target_link_libraries(tests horde)
	target_link_libraries(tests aliance)
	
	#target_link_libraries(tests ${GTEST_LIBRARIES} pthread)
	target_link_libraries(tests gtest gtest_main)
endif()
