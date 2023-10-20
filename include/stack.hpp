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
    Stack(const Stack &otherStack);

    void clear();
    void visualize();
    void handle(const string &expression);

    double &operator[](size_t index);
    Stack &operator=(const Stack &otherStack);
    vector<double> *operator->();

private:
    vector<double> elements;

    bool isOperand(string &token);
    bool isOperator(string &token);
    optional<double> performOperation(double operand1, double operand2, string &op);
};

#endif
