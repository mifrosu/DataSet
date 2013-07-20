set(test_EXECUTABLE data_set_test)

include_directories(
    ${data_set_SOURCE_DIR}
    $ENV{GTEST_ROOT}/include
    $ENV{GTEST_ROOT}
#    $ENV{GMOCK_ROOT}/include
#    $ENV{GMOCK_ROOT}
)

add_executable(${test_EXECUTABLE} string_clean_test.cpp
                      data_set_test.cpp
                      item_test.cpp
                      compare_test.cpp
                      ${PROJECT_SOURCE_DIR}/data_set.cpp
                      ${PROJECT_SOURCE_DIR}/item.cpp
                      ${PROJECT_SOURCE_DIR}/string_clean.cpp
              )

target_link_libraries(${test_EXECUTABLE}
                      gtest
                      gtest_main
                      pthread
                     )
#target_link_libraries(${test_EXECUTABLE}
#                      gmock
#                      gmock_main
#                     )
