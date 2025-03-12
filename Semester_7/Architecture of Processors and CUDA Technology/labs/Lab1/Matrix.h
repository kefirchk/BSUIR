#pragma once

#include <iomanip>
#include <iostream>
#include <vector>
#include <chrono>
#include <string>

using namespace std;


class Matrix
{
public:
	typedef float MatrixType;
	size_t rows;
	size_t cols;
	vector<vector<MatrixType>> matrix;
	
	Matrix(size_t row_count, size_t col_count);
	void init();
	void print() const;
	bool compare(const Matrix& m2) const;
	Matrix transpose() const;
	Matrix multiply_without_cache(const Matrix& m2, string impl_name);
	Matrix multiply_with_cache_using_blocks(const Matrix& m2, int blockSize, string impl_name);
	Matrix multiply_with_cache_using_transposition(const Matrix& m2, int blockSize, string impl_name);
};
