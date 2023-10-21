#include <iostream>
#include <sstream>
#include <fstream>

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

double &Stack::operator[](int index)
{
    if (index < 0 || index >= this->elements.size())
        throw out_of_range("Index out of range");
    return this->elements[index];
}

void Stack::replace(int index, int replaceSize, Stack &replaceStack)
{
    if (index < 0 || index >= this->elements.size())
        throw out_of_range("Index out of range");
    if (replaceSize < 0 || replaceSize + index >= this->elements.size() || replaceSize != replaceStack->size())
        throw invalid_argument("Invalid `replaceSize` provided");

    for (int i = index; i < index + replaceSize; i++)
        this->elements[i] = replaceStack[i - index];
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

ostream &operator<<(ostream &output, const Stack &stack)
{
    for (const double &element : stack.elements)
        output << element << endl;
    return output;
}

istream &operator>>(istream &input, Stack &stack)
{
    stack.clear();

    double value;
    while (input >> value)
        stack->push_back(value);

    return input;
}

void Stack::saveToFile(string &filePath)
{
    ofstream outputFile(filePath);
    if (!outputFile.is_open())
        throw runtime_error("Cannot open file '" + filePath + "' for writing");

    outputFile << *this;
    outputFile.close();
}

void Stack::loadFromFile(string &filePath)
{
    ifstream inputFile(filePath);
    if (!inputFile.is_open())
        throw runtime_error("Cannot open file '" + filePath + "' for reading");

    inputFile >> *this;
    inputFile.close();
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
