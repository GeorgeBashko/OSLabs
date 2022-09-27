#include "Vector.h"
#include <cmath>

Vector::Vector(Number a, Number b) : x(a), y(b) {}

double Vector::angelCacl()
{
    return (x.getValue() != 0 ? atan((double)y.Divide(y, x)) : 0);
}

double Vector::radiusCalc()
{
    return sqrt(x.Add(x.Multiply(x, x), y.Multiply(y, y)));
}

Number Vector::getX() const
{
    return x;
}

Number Vector::getY() const
{
    return y;
}

void Vector::AddVector(Vector a, Vector b)
{
    x = a.x.Add(a.x, b.x);
    y = a.y.Add(a.y, b.y);
}
