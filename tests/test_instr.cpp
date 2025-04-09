#include "gtest/gtest.h"

TEST(AddTest, simpleEq) { ASSERT_EQ(0, 0); } // TODO[flops]: Make tests

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}