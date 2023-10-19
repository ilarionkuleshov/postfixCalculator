#!/bin/bash

echo "Cleaning build/ directory..."
cd build/
rm -rf *

echo "Running CMake..."
cmake ..

echo "Compiling the project..."
make

echo "Copying executable to bin/ directory..."
executable_in_bin="../bin/postfixCalculator"

if [ -e "$executable_in_bin" ]; then
    rm "$executable_in_bin"
fi

cp postfixCalculator $executable_in_bin
