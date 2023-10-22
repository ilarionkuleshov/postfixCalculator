#include <gtest/gtest.h>
#include "testUtils.hpp"

using namespace testing;

int main(int argc, char **argv)
{
    InitGoogleTest(&argc, argv);
    int code = RUN_ALL_TESTS();

    removeTempFile();

    return code;
}
