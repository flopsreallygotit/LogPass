add_executable(test_log_funcs test_log_funcs.cpp)

target_link_libraries(${PROJECT_TEST_NAME}
  test_log_funcs
  gtest
  gtest_main
  log_funcs
)

include(GoogleTest)
gtest_discover_tests(test_log_funcs)
