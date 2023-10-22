#include <gtest/gtest.h>
#include <fstream>

#include "stack.hpp"
#include "testUtils.hpp"

TEST(stackInit, initWithoutArg)
{
    Stack stack;
    EXPECT_EQ(getStackContent(stack), "[]\n");
}

TEST(stackInit, initWithArg)
{
    Stack stack("23 5 4");
    EXPECT_EQ(getStackContent(stack), "[23, 5, 4]\n");
}

TEST(stackInit, copyInit)
{
    Stack stack("23 5 4");
    Stack copyStack(stack);
    EXPECT_EQ(getStackContent(stack), "[23, 5, 4]\n");
}

TEST(stackClear, clearEmpty)
{
    Stack stack;
    stack.clear();
    EXPECT_EQ(getStackContent(stack), "[]\n");
}

TEST(stackClear, clearWithElements)
{
    Stack stack("23 5 4");
    stack.clear();
    EXPECT_EQ(getStackContent(stack), "[]\n");
}

TEST(stackVisualize, visualizeEmpty)
{
    Stack stack;
    EXPECT_EQ(getStackContent(stack), "[]\n");
}

TEST(stackVisualize, visualizeNonEmpty)
{
    Stack stack("23 5 4");
    EXPECT_EQ(getStackContent(stack), "[23, 5, 4]\n");
}

TEST(stackSaveToFile, saveEmpty)
{
    Stack stack;
    stack.saveToFile(tempFilePath);
    try
    {
        string file_content = getTempFileContent();
        EXPECT_EQ(file_content, "");
    }
    catch (const runtime_error &error)
    {
        FAIL() << error.what();
    }
}

TEST(stackSaveToFile, saveNonEmpty)
{
    Stack stack("23 5 4");
    stack.saveToFile(tempFilePath);
    try
    {
        string file_content = getTempFileContent();
        EXPECT_EQ(file_content, "23\n5\n4\n");
    }
    catch (const runtime_error &error)
    {
        FAIL() << error.what();
    }
}

TEST(stackLoadFromFile, loadEmpty)
{
    Stack stack;
    stack.saveToFile(tempFilePath);

    Stack newStack;
    newStack.loadFromFile(tempFilePath);

    EXPECT_EQ(getStackContent(newStack), "[]\n");
}

TEST(stackLoadFromFile, loadNonEmpty)
{
    Stack stack("23 5 4");
    stack.saveToFile(tempFilePath);

    Stack newStack;
    newStack.loadFromFile(tempFilePath);

    EXPECT_EQ(getStackContent(newStack), "[23, 5, 4]\n");
}

TEST(stackHandle, handleFewExps)
{
    Stack stack;
    stack.handle("23");
    stack.handle("5");
    stack.handle("4");
    stack.handle("+");
    stack.handle("9");
    stack.handle("-");

    EXPECT_EQ(getStackContent(stack), "[23, 0]\n");
}

TEST(stackHandle, handleOneExp)
{
    Stack stack;
    stack.handle("23 5 4 + 9 -");

    EXPECT_EQ(getStackContent(stack), "[23, 0]\n");
}

TEST(stackHandle, handleDivByZero)
{
    Stack stack;
    stack.handle("23 5 0 /");

    EXPECT_EQ(getStackContent(stack), "[23, 5, 0]\n");
}

TEST(stackHandle, handleCaseFromTask)
{
    Stack stack;
    stack.handle("2 3 + 10 *");

    EXPECT_EQ(getStackContent(stack), "[50]\n");
}

TEST(stackReplace, replaceEmpty)
{
    Stack stack("2 3 4 5 6 7");
    Stack replaceStack("");

    stack.replace(1, 0, replaceStack);

    EXPECT_EQ(getStackContent(stack), "[2, 3, 4, 5, 6, 7]\n");
}

TEST(stackReplace, replaceNonEmpty)
{
    Stack stack("2 3 4 5 6 7");
    Stack replaceStack("10 11 12");

    stack.replace(1, 3, replaceStack);

    EXPECT_EQ(getStackContent(stack), "[2, 10, 11, 12, 6, 7]\n");
}

TEST(stackReplace, replaceIncorrect)
{
    Stack stack("2 3 4 5 6 7");
    Stack replaceStack("10 11 12");

    try
    {
        stack.replace(1, 4, replaceStack);
        FAIL() << "Incorrect replacing not handled";
    }
    catch (const std::exception &)
    {
        EXPECT_EQ(getStackContent(stack), "[2, 3, 4, 5, 6, 7]\n");
    }
}

TEST(stackOperatorSqBr, sqBrGet)
{
    Stack stack("2 3 4 5 6 7");

    double element1 = stack[0];
    double element2 = stack[2];
    double element3 = stack[5];

    EXPECT_EQ(element1, 2.0);
    EXPECT_EQ(element2, 4.0);
    EXPECT_EQ(element3, 7.0);
}

TEST(stackOperatorSqBr, sqBrSet)
{
    Stack stack("2 3 4 5 6 7");

    stack[0] = 10.0;
    stack[2] = 11.55;
    stack[5] = -2.343;

    EXPECT_EQ(getStackContent(stack), "[10, 3, 11.55, 5, 6, -2.343]\n");
}

TEST(stackOperatorEq, eqEmpty)
{
    Stack stack1("2 3 4 5 6 7");
    Stack stack2;

    stack1 = stack2;

    EXPECT_EQ(getStackContent(stack1), "[]\n");
}

TEST(stackOperatorEq, eqNonEmpty)
{
    Stack stack1("2 3 4 5 6 7");
    Stack stack2("10 11 12 +");

    stack1 = stack2;

    EXPECT_EQ(getStackContent(stack1), "[10, 23]\n");
}

TEST(stackOperatorSmPntr, smPntrCheckEmpty)
{
    Stack stack1("2 3 4 5 6 7");
    Stack stack2;

    EXPECT_EQ(stack1->empty(), false);
    EXPECT_EQ(stack2->empty(), true);
}

TEST(stackOperatorSmPntr, smPntrPushBack)
{
    Stack stack("2 3 4 5 6 7");
    stack->push_back(-43.55);

    EXPECT_EQ(getStackContent(stack), "[2, 3, 4, 5, 6, 7, -43.55]\n");
}

TEST(stackOperatorSmPntr, smPntrPopBack)
{
    Stack stack("2 3 4 5 6 7");
    stack->pop_back();
    stack->pop_back();

    EXPECT_EQ(getStackContent(stack), "[2, 3, 4, 5]\n");
}

TEST(stackOperatorArrows, backArrowsGet)
{
    Stack stack("2 3 4 5 6 7");

    ostringstream oss;
    oss << stack;

    EXPECT_EQ(oss.str(), "2\n3\n4\n5\n6\n7\n");
}

TEST(stackOperatorArrows, forwardArrowsSet)
{
    Stack stack1("2 3 4 5 6 7");

    Stack stack2("10 11 12");
    stack2.saveToFile(tempFilePath);

    ifstream file(tempFilePath);
    if (!file.is_open())
        FAIL() << "Cannot open file " << tempFilePath;

    file >> stack1;
    file.close();

    EXPECT_EQ(getStackContent(stack1), "[10, 11, 12]\n");
}
