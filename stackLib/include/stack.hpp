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
    void saveToFile(const string &filePath);
    void loadFromFile(const string &filePath);
    void replace(int index, int replaceSize, Stack &replaceStack);
    void handle(const string &expression);

    double &operator[](int index);
    Stack &operator=(const Stack &otherStack);
    vector<double> *operator->();

    friend ostream &operator<<(ostream &output, const Stack &stack);
    friend istream &operator>>(istream &input, Stack &stack);

private:
    vector<double> elements;

    bool isOperand(string &token);
    bool isOperator(string &token);
    optional<double> performOperation(double operand1, double operand2, string &op);
};

#endif
