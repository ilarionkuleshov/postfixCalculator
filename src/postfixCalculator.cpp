#include <iostream>

#include "stack.hpp"
#include "postfixCalculator.hpp"

PostfixCalculator::PostfixCalculator()
{
    Stack initialStack;
    this->stacks.push_back(initialStack);
}

int PostfixCalculator::run()
{
    string prompt;

    cout << "Welcome to PostfixCalculator!\n"
         << "Enter 'h' for help.\n"
         << endl;

    while (prompt != "q")
    {
        cout << ">>> ";
        getline(cin, prompt);

        if (prompt.empty() || prompt == "q")
            continue;
        else if (prompt == "h")
        {
            cout << "Available commands:\n"
                 << "'h': Display a list of available commands (help).\n"
                 << "'q': Quit the program.\n"
                 << "'l': Display a list of existing stacks.\n"
                 << "'n': Create new stack.\n"
                 << "'r': Remove specific stack.\n"
                 << "'e': Equate one stack to another.\n"
                 << "'o': Choose specific stack to operate with.\n"
                 << endl;
        }
        else if (prompt == "l")
            this->printStacks();
        else if (prompt == "n")
            this->createNewStack();
        else if (prompt == "r")
            this->removeStack();
        else if (prompt == "e")
            this->equateStacks();
        else if (prompt == "o")
            this->operateStack();
    }

    return 0;
}

void PostfixCalculator::equateStacks()
{
    optional<int> stackId1 = this->getValidatedStackId("to which you want to replace the values");
    if (!stackId1.has_value())
        return;

    optional<int> stackId2 = this->getValidatedStackId("from which you want to take the values");
    if (!stackId2.has_value())
        return;

    this->stacks[stackId1.value()] = this->stacks[stackId2.value()];

    cout << endl;
    this->printStacks();
}

void PostfixCalculator::operateStack()
{
    optional<int> stackId = this->getValidatedStackId("to operate with");

    if (!stackId.has_value())
        return;

    string prompt;
    cout << endl;

    while (prompt != "b")
    {
        cout << "(stack " << stackId.value() << ") "
             << ">>> ";
        getline(cin, prompt);

        if (prompt.empty() || prompt == "b")
            continue;
        else if (prompt == "h")
        {
            cout << "Available commands (for stack " << stackId.value() << "):\n"
                 << "'h': Display a list of available commands (help).\n"
                 << "'b': Go back to main menu.\n"
                 << "'v': Visualize the current stack.\n"
                 << "'g': Get specific element of the current stack.\n"
                 << "<expression>: Handle <expression> for the current stack (numbers and operators).\n"
                 << endl;
        }
        else if (prompt == "v")
        {
            this->stacks[stackId.value()].visualize();
            cout << endl;
        }
        else if (prompt == "g")
            this->getStackElement(stackId.value());
        else
        {
            this->stacks[stackId.value()].handle(prompt);
            this->stacks[stackId.value()].visualize();
            cout << endl;
        }
    }
    cout << endl;
}

void PostfixCalculator::getStackElement(int stackId)
{
    cout << "Enter ID of the stack element to get: ";

    string rawElementId;
    getline(cin, rawElementId);

    try
    {
        int elementId = stoi(rawElementId);
        cout << this->stacks[stackId][elementId] << endl
             << endl;
    }
    catch (const exception &e)
    {
        cerr << "Invalid ID specified!\n"
             << endl;
    }
}

void PostfixCalculator::printStacks()
{
    if (this->stacks.empty())
    {
        cout << "There are no stacks! To create one, enter 'n'.\n"
             << endl;
        return;
    }

    cout << "Existing stacks:" << endl;
    for (int i = 0; i < this->stacks.size(); i++)
    {
        cout << "Stack (" << i << "): ";
        this->stacks[i].visualize();
    }
    cout << endl;
}

void PostfixCalculator::createNewStack()
{
    string expression;

    cout << "If you want, enter the starting expression for the stack: ";
    getline(cin, expression);

    Stack newStack(expression);

    this->stacks.push_back(newStack);

    cout << "Stack (" << this->stacks.size() - 1 << "): ";
    newStack.visualize();

    cout << endl;
}

void PostfixCalculator::removeStack()
{
    optional<int> stackId = this->getValidatedStackId("to remove");

    if (stackId.has_value())
    {
        this->stacks.erase(this->stacks.begin() + stackId.value());
        cout << "Done!\n"
             << endl;
    }
}

optional<int> PostfixCalculator::getValidatedStackId(const string &details)
{
    string rawStackId;

    cout << "Enter ID of the stack " << details << ": ";
    getline(cin, rawStackId);

    try
    {
        int stackId = stoi(rawStackId);
        if (stackId < 0 || stackId >= this->stacks.size())
            throw invalid_argument("");

        return stackId;
    }
    catch (const exception &e)
    {
        cerr << "Invalid ID specified!\n"
             << endl;
    }
    return nullopt;
}
