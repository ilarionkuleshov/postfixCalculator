#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <vector>
#include <string>
#include <optional>
#include "stack.hpp"

using namespace std;

class PostfixCalculator
{
public:
    PostfixCalculator();

    int run();

private:
    vector<Stack> stacks;
    int stackCounter;

    void printStacks();
    void createNewStack();
    void removeStack();
    void operateStack();
    void equateStacks();
    void saveOrLoadStack(int stackId, string &operation);
    void getStackElement(int stackId);
    optional<int> getValidatedStackId(const string &details);
};

#endif
