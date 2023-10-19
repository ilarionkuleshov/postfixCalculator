#include <iostream>
#include "postfixCalculator.hpp"

using namespace std;

int main()
{
    PostfixCalculator calculator;

    string postfixExpression = "23 10 +";
    double result = calculator.evaluate(postfixExpression);

    cout << "Result: " << result << endl;

    return 0;
}
