#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cmath>

#include "postfixCalculator.hpp"

PostfixCalculator::PostfixCalculator() {}

double PostfixCalculator::evaluate(const string &expression)
{
    istringstream iss(expression);
    string token;
    stack<double> operandStack;

    while (iss >> token)
    {
        if (isOperand(token))
        {
            double operand = stod(token);
            operandStack.push(operand);
        }
        else if (isOperator(token))
        {
            if (operandStack.size() < 2)
            {
                cerr << "Invalid postfix expression." << endl;
                return 0.0;
            }
            double operand2 = operandStack.top();
            operandStack.pop();
            double operand1 = operandStack.top();
            operandStack.pop();

            double result = performOperation(operand1, operand2, token);
            operandStack.push(result);
        }
        else
        {
            cerr << "Invalid token: " << token << endl;
            return 0.0;
        }
    }

    if (operandStack.size() == 1)
    {
        return operandStack.top();
    }
    else
    {
        cerr << "Invalid postfix expression." << endl;
        return 0.0;
    }
}

bool PostfixCalculator::isOperand(const string &token)
{
    try
    {
        stod(token);
        return true;
    }
    catch (const invalid_argument &)
    {
        return false;
    }
}

bool PostfixCalculator::isOperator(const string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

double PostfixCalculator::performOperation(double operand1, double operand2, const string &op)
{
    if (op == "+")
    {
        return operand1 + operand2;
    }
    else if (op == "-")
    {
        return operand1 - operand2;
    }
    else if (op == "*")
    {
        return operand1 * operand2;
    }
    else if (op == "/")
    {
        if (operand2 != 0)
        {
            return operand1 / operand2;
        }
        else
        {
            cerr << "Division by zero." << endl;
            return 0.0;
        }
    }
    return 0.0;
}
