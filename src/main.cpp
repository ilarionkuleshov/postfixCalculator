#include <iostream>
#include "postfixCalculator.hpp"

using namespace std;

int main()
{
    PostfixCalculator calculator;
    string prompt;
    optional<double> result;

    cout << "Welcome to PostfixCalculator!\n"
         << "Enter 'h' for help.\n"
         << endl;

    while (prompt != "q")
    {
        cout << ">>> ";
        getline(cin, prompt);

        if (prompt.empty() || prompt == "q")
            continue;
        else if (prompt == "h")
        {
            cout << "Available commands:\n"
                 << "'h': Display a list of available commands (help).\n"
                 << "'q': Quit the program.\n"
                 << "'v': Visualize the current stack.\n"
                 << "'c': Clear stack.\n"
                 << "<expression>: Handle <expression> (numbers and operators).\n"
                 << endl;
        }
        else if (prompt == "v")
            calculator.visualize();
        else if (prompt == "c")
            calculator.clear();
        else
            calculator.handle(prompt);
    }

    return 0;
}
