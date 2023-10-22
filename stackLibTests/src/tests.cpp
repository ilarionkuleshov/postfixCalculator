#include <gtest/gtest.h>
#include "stack.hpp"

TEST(StackInit, InitWithoutArg)
{
    Stack stack;

    ostringstream oss;
    oss << stack;

    EXPECT_EQ(oss.str(), "");
}

TEST(StackInit, InitWithArg)
{
    Stack stack("23 5 4");

    ostringstream oss;
    oss << stack;

    EXPECT_EQ(oss.str(), "23\n5\n4\n");
}
