#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <string>
#include <stack>
#include <optional>
using namespace std;

class PostfixCalculator
{
public:
    stack<double> operandStack;

    PostfixCalculator();
    PostfixCalculator(string &expression);

    void clear();
    void visualize();
    void handle(string &expression);

private:
    bool isOperand(string &token);
    bool isOperator(string &token);

    optional<double> calculate(string &expression);
    optional<double> performOperation(double operand1, double operand2, string &op);
};

#endif
