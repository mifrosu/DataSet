cmake_minimum_required(VERSION 2.8)
project(data_set)

set(project_SRCS main.cpp data_set.cpp item.cpp)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

add_executable(${PROJECT_NAME} ${project_SRCS})

option(build_tests "Build the project's unit tests" OFF)

if (build_tests)    # cmake -Dbuild_tests=BOOL:ON <path>
    add_subdirectory(tests)
    if(DEFINED ENV{GTEST_ROOT})
    # e.g.(Linux) export GTEST_ROOT=/home/michael/gtest/gtest-1.6.0
        message("... using gtest found in $ENV{GTEST_ROOT}")
    ELSE()
        message("GTEST_ROOT is not defined. You must tell CMAKE where to find
        the gtest_source")
        #exit early
        return()
    endif()

    # a target binary directory is specified for out of tree sources
    add_subdirectory($ENV{GTEST_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/gtest)
    #add_subdirectory($ENV{GMOCK_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/gmock)
endif()

