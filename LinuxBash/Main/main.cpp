#include <iostream>
#include <Vector.h>
#include <Number.h>

    int main()
    {
        Number n1(10), n2(10);
        Number zero = Zero;
        Number one = One;
        std::cout << n1.Add(n1.Add(n2, n1), n1.Add(zero, one)) << std::endl;
        std::cout << one.getValue() << std::endl;
        Vector v1(one, one);
        Vector v2(n1, n2);
        Vector Zero_ = ZERO;
        Vector One_ = ONE;
        std::cout << One_.getX().getValue() << " " << One_.getY().getValue() << std::endl;
        std::cout << (Zero_.getX()).getValue() << " " << Zero_.getY().getValue() << std::endl;
        v1.AddVector(v1, v2);
        std::cout << (v1.getX()).getValue() << " " << (v1.getX()).getValue() << std::endl;
        Vector v3(n1, n2);
        std::cout << (v3.getX()).getValue() << " " << (v3.getY()).getValue() << std::endl;
        std::cout << v1.angelCacl() << " " << v1.radiusCalc();
    }
