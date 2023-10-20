#ifndef STACK_H
#define STACK_H

#include <string>
#include <vector>
#include <optional>
using namespace std;

class Stack
{
public:
    Stack();
    Stack(const string &expression);

    void clear();
    void visualize();
    void handle(const string &expression);

private:
    vector<double> elements;

    bool isOperand(string &token);
    bool isOperator(string &token);
    optional<double> performOperation(double operand1, double operand2, string &op);
};

#endif
