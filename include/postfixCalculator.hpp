#ifndef POSTFIXCALCULATOR_H
#define POSTFIXCALCULATOR_H

#include <string>
using namespace std;

class PostfixCalculator
{
public:
    PostfixCalculator();

    double evaluate(const string &expression);

private:
    bool isOperand(const string &token);

    bool isOperator(const string &token);

    double performOperation(double operand1, double operand2, const string &op);
};

#endif
