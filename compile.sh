#!/bin/bash

echo "Cleaning build/ directory..."
cd build/
rm -rf *

echo "Running CMake..."
cmake ..

echo "Compiling the project..."
make

echo "Copying executable to bin/ directory..."
cp postfixCalculator ../bin/postfixCalculator
