set(test_EXECUTABLE data_set_test)

include_directories(
    $ENV{GTEST_ROOT}/include
    $ENV{GTEST_ROOT}
#    $ENV{GMOCK_ROOT}/include
#    $ENV{GMOCK_ROOT}
)

add_executable(${test_EXECUTABLE}
               split_string_test.cpp data_set_test.cpp
              )

target_link_libraries(${test_EXECUTABLE}
                      pthread
)
target_link_libraries(${test_EXECUTABLE}
                      gtest
                      gtest_main
                     )
#target_link_libraries(${test_EXECUTABLE}
#                      gmock
#                      gmock_main
#                     )
