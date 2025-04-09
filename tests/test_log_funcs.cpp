#include "gtest/gtest.h"

void log_function_init();
void log_function_call(char *function);
void log_function_deinit();

TEST(InitTest, log_function_init) { ASSERT_EQ(0, 0); }      // TODO[flops]: Make tests
TEST(CallTest, log_function_call) { ASSERT_EQ(0, 0); }      // TODO[flops]: Make tests
TEST(DeinitTest, log_function_deinit) { ASSERT_EQ(0, 0); }  // TODO[flops]: Make tests

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}