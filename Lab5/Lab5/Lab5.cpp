#include <iostream>
#include <ctime>
#include "Matrix.h"
#include "MatrixMultiplicator.h"

int main()
{
	int n = 100;
	Matrix matrix1 = matrix1.RandomFill(n, n, 100);
	Matrix matrix2 = matrix2.RandomFill(n, n, 100);
	MatrixMultiplicator matrix_multiplicator;
	int start_time = clock();
	Matrix matrix3 = matrix_multiplicator.Multiply(matrix1, matrix2);
	int end_time = clock();
	std::cout << "Multiply time: " << end_time - start_time << std::endl;
	for (int k = 1; k <= n; ++k)
	{
		if (n % k == 0)
		{
			int start_time = clock();
			Matrix matrix4 = matrix_multiplicator.MultiplyBlock(matrix1, matrix2, k);
			int end_time = clock();
			std::cout << k * k << " blocks: " << end_time - start_time << std::endl;
		}
	}
}
