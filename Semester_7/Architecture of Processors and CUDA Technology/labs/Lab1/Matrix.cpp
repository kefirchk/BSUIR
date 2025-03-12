#include "Matrix.h"


Matrix::Matrix(size_t row_count, size_t col_count) {
    this->cols = col_count;
    this->rows = row_count;
    matrix.resize(row_count);
    for (size_t i = 0; i < row_count; ++i)
        matrix[i].resize(col_count);
    this->init();
}


void Matrix::init() {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j)
            this->matrix[i][j] = static_cast<MatrixType>(rand() % 4 + 1);
    }
}


void Matrix::print() const {
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix[0].size(); ++j)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}


bool Matrix::compare(const Matrix& m2) const {
    if (this->rows != m2.rows || this->cols != m2.cols) {
        cout << "[ERROR] Sizes of matrices are not equal.\n";
        return false;
    }
    for (size_t i = 0; i < rows; ++i) {
        for (size_t j = 0; j < cols; ++j) {
            if (this->matrix[i][j] != m2.matrix[i][j]) {
                return false;
            }
        }
    }
    return true;
}


Matrix Matrix::transpose() const {
    Matrix result(this->cols, this->rows);
    for (size_t i = 0; i < this->rows; ++i) {
        for (size_t j = 0; j < this->cols; ++j) {
            result.matrix[j][i] = this->matrix[i][j];
        }
    }
    return result;
}


Matrix Matrix::multiply_without_cache(const Matrix& m2, string impl_name) {
	Matrix ans(this->rows, m2.cols);

	const auto start = std::chrono::high_resolution_clock::now();

	for (int i = 0; i < this->rows; ++i) {
		for (int j = 0; j < m2.cols; ++j) {
			for (int k = 0; k < this->cols; ++k) {
				ans.matrix[i][j] += this->matrix[i][k] * m2.matrix[k][j];
			}
		}
	}

	const auto end = std::chrono::high_resolution_clock::now();
	auto duration_micro = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	std::cout << "Time (" << impl_name << "): " << duration_micro.count() << " us" << endl;

	return ans;
}


Matrix Matrix::multiply_with_cache_using_blocks(const Matrix& m2, int blockSize, string impl_name) {
	Matrix ans(this->rows, m2.cols);

	const auto start = chrono::high_resolution_clock::now();

	for (int rowBlock = 0; rowBlock < this->rows; rowBlock += blockSize) {
		for (int colBlock = 0; colBlock < m2.cols; colBlock += blockSize) {
			for (int kBlock = 0; kBlock < this->cols; kBlock += blockSize) {
				for (int i = rowBlock; i < min(rowBlock + blockSize, (int)this->rows); ++i) {
					for (int j = colBlock; j < min(colBlock + blockSize, (int)m2.cols); ++j) {
						MatrixType sum = 0;

						for (int k = kBlock; k < min(kBlock + blockSize, (int)this->cols); ++k) {
							sum += this->matrix[i][k] * m2.matrix[k][j];
						}

						ans.matrix[i][j] += sum;
					}
				}
			}
		}
	}

	const auto end = chrono::high_resolution_clock::now();
	auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start);
	cout << "Time (" << impl_name << "): " << duration_micro.count() << " us" << endl;

	return ans;
}


Matrix Matrix::multiply_with_cache_using_transposition(const Matrix& m2, int blockSize, string impl_name) {
	const auto start = chrono::high_resolution_clock::now();


	Matrix m2T = m2.transpose();
    Matrix ans(this->rows, m2.cols);


    for (int rowBlock = 0; rowBlock < this->rows; rowBlock += blockSize) {
        for (int colBlock = 0; colBlock < m2T.rows; colBlock += blockSize) {
            for (int kBlock = 0; kBlock < this->cols; kBlock += blockSize) {
                for (int i = rowBlock; i < min(rowBlock + blockSize, (int)this->rows); ++i) {
                    for (int j = colBlock; j < min(colBlock + blockSize, (int)m2T.rows); ++j) {
                        MatrixType sum = 0;

                        for (int k = kBlock; k < min(kBlock + blockSize, (int)this->cols); ++k) {
                            sum += this->matrix[i][k] * m2T.matrix[j][k];
                        }

                        ans.matrix[i][j] += sum;
                    }
                }
            }
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::microseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " us" << endl;

    return ans;
}
