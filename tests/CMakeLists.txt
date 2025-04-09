add_executable(test_log_funcs test_log_funcs.cpp)
target_link_libraries(test_log_funcs log_funcs)

target_link_libraries(${PROJECT_TEST_NAME}
  test_log_funcs
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_log_funcs)
