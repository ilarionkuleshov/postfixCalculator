#include <iostream>
#include <sstream>

#include "stack.hpp"

Stack::Stack()
{
}

Stack::Stack(const string &expression)
{
    this->handle(expression);
}

Stack::Stack(const Stack &otherStack)
{
    this->elements = otherStack.elements;
}

double &Stack::operator[](size_t index)
{
    if (index < this->elements.size())
        return this->elements[this->elements.size() - 1 - index];
    else
        throw std::out_of_range("Index out of range");
}

Stack &Stack::operator=(const Stack &otherStack)
{
    if (this != &otherStack)
        this->elements = otherStack.elements;
    return *this;
}

vector<double> *Stack::operator->()
{
    return &this->elements;
}

void Stack::clear()
{
    this->elements.clear();
}

void Stack::handle(const string &expression)
{
    istringstream iss(expression);
    string token;

    while (iss >> token)
    {
        if (this->isOperand(token))
        {
            double operand = stod(token);
            this->elements.push_back(operand);
        }
        else if (this->isOperator(token))
        {
            if (this->elements.size() < 2)
            {
                cerr << "Not enough operands to operate with!" << endl;
                continue;
            }
            double operand2 = this->elements[this->elements.size() - 1];
            double operand1 = this->elements[this->elements.size() - 2];

            optional<double> result = this->performOperation(operand1, operand2, token);
            if (result.has_value())
            {
                this->elements.pop_back();
                this->elements.pop_back();
                this->elements.push_back(result.value());
            }
        }
        else
        {
            cerr << "Invalid token: " << token << endl;
            continue;
        }
    }
}

void Stack::visualize()
{
    cout << "[";

    for (int i = 0; i < this->elements.size(); i++)
    {
        cout << this->elements[i];
        if (i != this->elements.size() - 1)
            cout << ", ";
    }

    cout << "]" << endl;
}

bool Stack::isOperand(string &token)
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

bool Stack::isOperator(string &token)
{
    return token == "+" || token == "-" || token == "*" || token == "/";
}

optional<double> Stack::performOperation(double operand1, double operand2, string &op)
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
