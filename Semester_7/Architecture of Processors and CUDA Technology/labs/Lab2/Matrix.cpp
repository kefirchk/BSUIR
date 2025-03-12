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

    const auto end = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " ms" << endl;

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
    auto duration_micro = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " ms" << endl;

    return ans;
}


Matrix Matrix::multiply_with_cache_using_avx(const Matrix& m2, int blockSize, string impl_name) {
    Matrix ans(this->rows, m2.cols);

    const auto start = chrono::high_resolution_clock::now();

    for (int rowBlock = 0; rowBlock < this->rows; rowBlock += blockSize) {
        for (int colBlock = 0; colBlock < m2.cols; colBlock += blockSize) {
            for (int kBlock = 0; kBlock < this->cols; kBlock += blockSize) {
                for (int i = rowBlock; i < min(rowBlock + blockSize, (int)this->rows); ++i) {
                    for (int j = colBlock; j < min(colBlock + blockSize, (int)m2.cols); j += 8) { // обрабатываем по 8 столбцов за раз
                        __m256 sum = _mm256_setzero_ps(); // 256-битный регистр для хранения сумм (float, 8 элементов)

                        for (int k = kBlock; k < min(kBlock + blockSize, (int)this->cols); ++k) {
                            __m256 a = _mm256_set1_ps(this->matrix[i][k]); // загружаем элемент строки из первой матрицы
                            __m256 b = _mm256_loadu_ps(&m2.matrix[k][j]); // загружаем 8 элементов столбца из второй матрицы
                            sum = _mm256_fmadd_ps(a, b, sum); // умножаем и прибавляем к сумме
                        }

                        // сохраняем результат обратно в итоговую матрицу
                        __m256 c = _mm256_loadu_ps(&ans.matrix[i][j]);
                        c = _mm256_add_ps(c, sum);
                        _mm256_storeu_ps(&ans.matrix[i][j], c);
                    }
                }
            }
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " ms" << endl;

    return ans;
}


Matrix Matrix::multiply_with_cache_using_sse(const Matrix& m2, int blockSize, string impl_name) {
    Matrix ans(this->rows, m2.cols);

    const auto start = chrono::high_resolution_clock::now();

    for (int rowBlock = 0; rowBlock < this->rows; rowBlock += blockSize) {
        for (int colBlock = 0; colBlock < m2.cols; colBlock += blockSize) {
            for (int kBlock = 0; kBlock < this->cols; kBlock += blockSize) {
                for (int i = rowBlock; i < min(rowBlock + blockSize, (int)this->rows); ++i) {
                    for (int j = colBlock; j < min(colBlock + blockSize, (int)m2.cols); j += 4) { // обрабатываем по 4 столбца за раз
                        __m128 sum = _mm_setzero_ps(); // 128-битный регистр для хранения сумм (float, 4 элемента)

                        for (int k = kBlock; k < min(kBlock + blockSize, (int)this->cols); ++k) {
                            __m128 a = _mm_set1_ps(this->matrix[i][k]); // загружаем элемент строки из первой матрицы
                            __m128 b = _mm_loadu_ps(&m2.matrix[k][j]); // загружаем 4 элемента столбца из второй матрицы
                            sum = _mm_add_ps(sum, _mm_mul_ps(a, b)); // умножаем и прибавляем к сумме
                        }

                        // сохраняем результат обратно в итоговую матрицу
                        __m128 c = _mm_loadu_ps(&ans.matrix[i][j]);
                        c = _mm_add_ps(c, sum);
                        _mm_storeu_ps(&ans.matrix[i][j], c);
                    }
                }
            }
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " ms" << endl;

    return ans;
}


Matrix Matrix::multiply_with_cache_using_openmp(const Matrix& m2, int blockSize, string impl_name) {    
    omp_set_num_threads(4); // оптимальное количество потоков в зависимости от системы

    Matrix ans(this->rows, m2.cols);

    const auto start = chrono::high_resolution_clock::now();

#pragma omp parallel for collapse(4) schedule(dynamic, 1)
    for (int rowBlock = 0; rowBlock < this->rows; rowBlock += blockSize) {
        for (int colBlock = 0; colBlock < m2.cols; colBlock += blockSize) {
            for (int kBlock = 0; kBlock < this->cols; kBlock += blockSize) {
                for (int i = rowBlock; i < min(rowBlock + blockSize, (int)this->rows); ++i) {
                    for (int j = colBlock; j < min(colBlock + blockSize, (int)m2.cols); j += 8) { // обрабатываем по 8 столбцов за раз
                        __m256 sum = _mm256_setzero_ps(); // 256-битный регистр для хранения сумм (float, 8 элементов)
                        for (int k = kBlock; k < min(kBlock + blockSize, (int)this->cols); ++k) {
                            __m256 a = _mm256_set1_ps(this->matrix[i][k]); // загружаем элемент строки из первой матрицы
                            __m256 b = _mm256_loadu_ps(&m2.matrix[k][j]); // загружаем 8 элементов столбца из второй матрицы
                            sum = _mm256_fmadd_ps(a, b, sum); // умножаем и прибавляем к сумме
                        }

                        // сохраняем результат обратно в итоговую матрицу
                        __m256 c = _mm256_loadu_ps(&ans.matrix[i][j]);
                        c = _mm256_add_ps(c, sum);
                        _mm256_storeu_ps(&ans.matrix[i][j], c);
                    }
                }
            }
        }
    }

    const auto end = chrono::high_resolution_clock::now();
    auto duration_micro = chrono::duration_cast<chrono::milliseconds>(end - start);
    cout << "Time (" << impl_name << "): " << duration_micro.count() << " ms" << endl;
    return ans;
}
