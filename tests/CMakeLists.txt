add_executable(test_log_funcs test_log_funcs.cpp)
target_link_libraries(test_log_funcs log_funcs)

target_link_libraries(${PROJECT_TEST_NAME}
  test_log_funcs
  gtest
  gtest_main
)

include(GoogleTest)
gtest_discover_tests(test_log_funcs)

add_test(
  NAME test_loggercxx
  COMMAND $<TARGET_FILE:loggercxx> -g -O0 -S -emit-llvm -fno-discard-value-names ${CMAKE_CURRENT_SOURCE_DIR}/instr_target.cpp -o test_log_pass.ll
)
