#pragma once

#ifdef VECTOR_EXPORTS
#define VECTORDll __declspec(dllexport)
#else
#define VECTORDll __declspec(dllimport)
#endif

#include <MyNumber.h>

class VECTORDll Vector
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
const Vector ZERO = Vector(Zero, Zero);
const Vector ONE = Vector(One, One);