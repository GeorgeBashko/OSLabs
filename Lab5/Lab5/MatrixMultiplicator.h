#pragma once

#include <mutex>
#include "Matrix.h"

class MatrixMultiplicator
{
public:
	Matrix Multiply(const Matrix& matrix1, const Matrix& matrix2);
	Matrix MultiplyBlock(const Matrix& matrix1, const Matrix& matrix2, int k);
	void MultiplyBlocks(Matrix& result, const Matrix& matrix1, const Matrix& matrix2,
		int row1, int column1, int row2, int column2, int block_size);

private:
	std::mutex lock_;
};
