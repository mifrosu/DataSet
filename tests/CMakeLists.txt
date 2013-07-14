set(test_EXECUTABLE data_set_test)

include_directories(
    $ENV{GTEST_ROOT}/include
    $ENV{GTEST_ROOT}
    )

add_executable(${test_EXECUTABLE} data_set_test.cpp
    )

target_link_libraries(${test_EXECUTABLE}
    gtest
    gtest_main
    pthread
    )
