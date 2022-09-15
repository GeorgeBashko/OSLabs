// MathLibrary.cpp : Defines the exported functions for the DLL.
#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "MyVector.h";
#include <math.h>

const Vector ONE = Vector(One, One);
const Vector ZERO = Vector(Zero, Zero);

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