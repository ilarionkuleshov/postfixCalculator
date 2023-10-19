#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

#include "postfixCalculator.hpp"

PostfixCalculator::PostfixCalculator() {}
PostfixCalculator::PostfixCalculator(string &expression)
{
}

void PostfixCalculator::clear()
{
    while (!this->operandStack.empty())
        this->operandStack.pop();
    cout << "Done!\n"
         << endl;
}

void PostfixCalculator::handle(string &expression)
{
    optional<double> result = this->calculate(expression);
    if (result.has_value())
        cout << "Last stack element: " << result.value() << endl;
    cout << endl;
}

optional<double> PostfixCalculator::calculate(string &expression)
{
    istringstream iss(expression);
    string token;

    while (iss >> token)
    {
        if (this->isOperand(token))
        {
            double operand = stod(token);
            this->operandStack.push(operand);
        }
        else if (this->isOperator(token))
        {
            if (this->operandStack.size() < 2)
            {
                cerr << "Not enough operands to operate with!" << endl;
                continue;
            }
            double operand2 = this->operandStack.top();
            this->operandStack.pop();
            double operand1 = this->operandStack.top();

            this->operandStack.push(operand2);

            optional<double> result = this->performOperation(operand1, operand2, token);
            if (result.has_value())
            {
                this->operandStack.pop();
                this->operandStack.pop();
                this->operandStack.push(result.value());
            }
        }
        else
        {
            cerr << "Invalid token: " << token << endl;
            continue;
        }
    }

    if (!this->operandStack.empty())
        return this->operandStack.top();

    return nullopt;
}

void PostfixCalculator::visualize()
{
    stack<double> tempStack = this->operandStack;
    vector<double> stackElements;

    while (!tempStack.empty())
    {
        stackElements.push_back(tempStack.top());
        tempStack.pop();
    }

    cout << "Current stack: [";

    for (int i = stackElements.size() - 1; i >= 0; i--)
    {
        cout << stackElements[i];
        if (i != 0)
            cout << ", ";
    }

    cout << "]\n"
         << endl;
}

bool PostfixCalculator::isOperand(string &token)
{
    try
    {
        stod(token);
        return true;
    }
    catch (invalid_argument &)
    {
        return false;
    }
}

bool PostfixCalculator::isOperator(string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

optional<double> PostfixCalculator::performOperation(double operand1, double operand2, string &op)
{
    if (op == "+")
        return operand1 + operand2;
    else if (op == "-")
        return operand1 - operand2;
    else if (op == "*")
        return operand1 * operand2;
    else if (op == "/")
    {
        if (operand2 != 0)
            return operand1 / operand2;
        else
            cerr << "Division by zero is not allowed." << endl;
    }
    return nullopt;
}
