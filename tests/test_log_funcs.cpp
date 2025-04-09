#include <fstream>
#include "gtest/gtest.h"

extern "C" void log_function_init();
extern "C" void log_function_call(char *function);
extern "C" void log_function_deinit();

TEST(InitTest, log_function_init) {  // Checks that init opens output stream
    ASSERT_TRUE(access("logger.log", F_OK) != -1);
}

TEST(CallTest, log_function_call) {
    std::ifstream logger_output("logger.log");

    std::string content;
    logger_output >> content;

    ASSERT_TRUE(content == "test_function");
}

TEST(DeinitTest, log_function_deinit) {
    std::ifstream logger_output("logger.log");

    ASSERT_TRUE(logger_output.good());
}

int main(int argc, char **argv) {
    log_function_init();

    char test_function_name[32];
    strcpy(test_function_name, "test_function");
    log_function_call(test_function_name);

    log_function_deinit();

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}