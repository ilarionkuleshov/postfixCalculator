# Postfix Calculator
Stack-based postfix calculator in C++.

## Requirements (on Linux)
- cmake (3.10+)
- make
- libgtest-dev

## Building (on Linux)
Run the script in root project directory:
```
./compile.sh
```
The static `Stack` library will be in the `build/stackLib` directory (with the `.a` extension).

## Usage (on Linux)
To run `Stack` library tests:
```
./bin/stackLibTests
```
To run `postfixCalculator` app:
```
./bin/postfixCalculatorApp
```
