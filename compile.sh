#!/bin/bash

echo "Cleaning build/ directory..."
cd build/
rm -rf *

echo "Running CMake..."
cmake ..

echo "Compiling the project..."
make

app_executable_in_build="postfixCalculatorApp/postfixCalculatorApp"
tests_executable_in_build="stackLibTests/stackLibTests"
if [ -e "$app_executable_in_build" ] && [ -e "$tests_executable_in_build" ]
then
    echo "Copying executables to bin/ directory..."

    app_executable_in_bin="../bin/postfixCalculatorApp"
    if [ -e "$app_executable_in_bin" ]
    then
        rm "$app_executable_in_bin"
    fi

    tests_executable_in_bin="../bin/stackLibTests"
    if [ -e "$tests_executable_in_bin" ]
    then
        rm "$tests_executable_in_bin"
    fi

    cp $app_executable_in_build $app_executable_in_bin
    cp $tests_executable_in_build $tests_executable_in_bin

else
    echo "An error occurred during compilation"
fi
