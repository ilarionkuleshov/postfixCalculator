#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "testUtils.hpp"

const string tempFilePath = "temp.txt";

string getStackContent(Stack &stack)
{
    stringstream buffer;
    streambuf *oldCout = cout.rdbuf(buffer.rdbuf());

    stack.visualize();

    cout.rdbuf(oldCout);
    return buffer.str();
}

string getTempFileContent()
{
    ifstream file(tempFilePath);
    if (!file.is_open())
        throw runtime_error("Cannot open file " + tempFilePath);

    string file_content, line;
    while (getline(file, line))
        file_content += line + "\n";

    file.close();
    return file_content;
}

void removeTempFile()
{
    if (filesystem::exists(tempFilePath))
        remove(tempFilePath.c_str());
}
