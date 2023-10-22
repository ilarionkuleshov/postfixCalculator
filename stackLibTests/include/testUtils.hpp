#ifndef TESTUTILS_H
#define TESTUTILS_H

#include <string>
#include "stack.hpp"
using namespace std;

extern const string tempFilePath;

string getStackContent(Stack &stack);
string getTempFileContent();
void removeTempFile();

#endif
