// lab3.cpp
#include "lab3.h"

int MathFunctions::add(int a, int b) {
    return a + b;
}

float MathFunctions::add(float a, float b) {
    return a + b;
}

int MathFunctions::subtract(int a, int b) {
    return a - b;
}

double MathFunctions::subtract(double a, double b) {
    return a - b;
}

int MathFunctions::multiply(int a, int b) {
    return a * b;
}

double MathFunctions::multiply(double a, double b) {
    return a * b;
}

float MathFunctions::divide(float a, float b) {
    if (b == 0) {
        throw "Division by zero!";
    }
    return a / b;
}

std::string MathFunctions::concat(std::string a, std::string b)
{
	return a + b;
}