cmake_minimum_required(VERSION 2.8)
project(data_set)

set(PROJECT_SRCS main.cpp data_set.cpp)

add_executable(${PROJECT_NAME} ${PROJECT_SRCS})

option(build_tests "Build the project's unit tests" OFF)

if (build_tests)    # cmake -Dbuild_tests=BOOL:ON <path>
    add_subdirectory(tests)
    if(DEFINED ENV{GTEST_ROOT})
        message("... using gtest found in $ENV{GTEST_ROOT}")
    ELSE()
        message("GTEST_ROOT is not defined. You must tell CMAKE where to find
        the gtest_source")
        #exit early
        return()
    endif()

    # a target binary directory is specified for out of tree sources
    add_subdirectory($ENV{GTEST_ROOT} ${CMAKE_CURRENT_BINARY_DIR}/gtest)
endif()

