#include "Number.h"
#include <iostream>
const Number One = Number(1);
const Number Zero = Number(0);

Number::Number(int a) { value = a; }

int Number::Add(Number a, Number b)
{
    return a.value + b.value;
}

int Number::Subtract(Number a, Number b)
{
    return a.value - b.value;
}

int Number::Multiply(Number a, Number b)
{
    return a.value * b.value;
}

double Number::Divide(Number a, Number b)
{
    return a.value / b.value;
}

int Number::getValue()
{
    return value;
}
void qq()
{
    std::cout << "asd";
}