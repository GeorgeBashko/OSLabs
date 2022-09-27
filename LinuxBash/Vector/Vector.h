#ifndef VECTOR_VECTOR_H
#define VECTOR_VECTOR_H

#include "Number.h"

class Vector
{
private:
    Number x;
    Number y;
public:
    Vector(Number, Number);
    void AddVector(Vector a, Vector b);
    double angelCacl();
    double radiusCalc();
    Number getX() const;
    Number getY() const;
};
const Vector ZERO = Vector(Number(0),Number(0));
const Vector ONE = Vector(Number(1), Number(1));

#endif //VECTOR_VECTOR_H
