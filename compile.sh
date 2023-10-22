#!/bin/bash

echo "Cleaning build/ directory..."
cd build/
rm -rf *

echo "Running CMake..."
cmake ..

echo "Compiling the project..."
make

executable_in_build="postfixCalculatorApp/postfixCalculatorApp"
if [ -e "$executable_in_build" ]
then
    echo "Copying executable to bin/ directory..."

    executable_in_bin="../bin/postfixCalculatorApp"
    if [ -e "$executable_in_bin" ]
    then
        rm "$executable_in_bin"
    fi

    cp $executable_in_build $executable_in_bin

else
    echo "An error occurred during compilation"
fi
