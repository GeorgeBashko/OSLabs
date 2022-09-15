#pragma once
class Number
{
private:
    int value;
public:

    Number(int a);

    int Add(Number a, Number b);

    int Subtract(Number a, Number b);

    int Multiply(Number a, Number b);

    double Divide(Number a, Number b);

    int getValue();
};
extern const Number One;
extern const Number Zero;