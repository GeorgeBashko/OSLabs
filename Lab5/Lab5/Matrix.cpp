#include "Matrix.h"

Matrix::Matrix(int m, int n) : elements_(m, std::vector<double>(n))
{}

double Matrix::operator()(int i, int j) const
{
	return elements_[i][j];
}

double& Matrix::operator()(int i, int j)
{
	return elements_[i][j];
}

int Matrix::GetRows() const
{
	return elements_.size();
}

int Matrix::GetColumns() const
{
	return elements_[0].size();
}
Matrix Matrix::RandomFill(int rows, int columns, double max_value)
{
	Matrix result_matrix(rows, columns);
	srand(time(0));
	for (int i = 0; i < rows; ++i)
	{
		for (int j = 0; j < columns; ++j)
		{
			result_matrix(i, j) = rand() % (int)max_value;
		}
	}
	return result_matrix;
}
