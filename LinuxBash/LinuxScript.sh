#!/bin/bash

#Number
g++ -c Number/Number.cpp -o Number/Number.o
ar rc Number/Number.a Number/Number.o

#Vector
g++ -c -INumber Vector/Vector.cpp -o Vector/Vector.o
g++ Number/Number.a Vector/Vector.o -shared -o Vector/Vector.so

#Main
g++ -o LinuxScript Main/main.cpp -IVector -INumber Vector/Vector.so Number/Number.a;
./LinuxScript
