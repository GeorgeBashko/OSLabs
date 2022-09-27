#ifndef NUMBER_NUMBER_H
#define NUMBER_NUMBER_H
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
void qq();

#endif //NUMBER_NUMBER_H
