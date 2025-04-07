enable_testing()

add_executable(test_instr test_instr.cpp)

target_link_libraries(${PROJECT_TEST_NAME}
  test_instr
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_instr)
