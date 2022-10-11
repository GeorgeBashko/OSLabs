#pragma once
#include <vector>
#include <ctime>

class Matrix
{
public:
	Matrix(int m, int n);
	double& operator()(int i, int j);
	double operator()(int i, int j) const;
	int GetRows() const;
	int GetColumns() const;
	Matrix RandomFill(int rows, int columns, double max_value);

private:
	std::vector<std::vector<double>> elements_;
};