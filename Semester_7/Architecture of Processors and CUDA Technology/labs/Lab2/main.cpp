#include "Matrix.h"

// Исходные данные:
// - кэш L3 = 6 Мб;
// - кэш L2 = 2 Мб;
// - кэш L1 = 320 Кб.

int main() {


    srand(time(0));
    // 8192,512   512, 1024
    Matrix m1(8192, 512), m2(512, 1024);
    vector<Matrix> res_matrices;

    Matrix m3 = m1.multiply_without_cache(m2, "without cache");

    //cout << "=============== USING << BLOCKS >> ===============" << endl;
    //res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 512, "with L3 cache"));
    //res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 128, "with L2 cache"));
    //res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 16, "with L1 cache"));

    cout << "=============== USING << AVX >> ===============" << endl;
    res_matrices.push_back(m1.multiply_with_cache_using_avx(m2, 512, "with L3 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_avx(m2, 128, "with L2 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_avx(m2, 16, "with L1 cache"));

    //cout << "=============== USING << SSE >> ===============" << endl;
    //res_matrices.push_back(m1.multiply_with_cache_using_sse(m2, 512, "with L3 cache"));
    //res_matrices.push_back(m1.multiply_with_cache_using_sse(m2, 128, "with L2 cache"));
    //res_matrices.push_back(m1.multiply_with_cache_using_sse(m2, 16, "with L1 cache"));

    cout << "=============== USING << OpenMP >> ===============" << endl;
    res_matrices.push_back(m1.multiply_with_cache_using_openmp(m2, 512, "with L3 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_openmp(m2, 128, "with L2 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_openmp(m2, 16, "with L1 cache"));

    for (size_t i = 0; i < res_matrices.size(); ++i)
    {
        if (m3.compare(res_matrices[i]) == false) {
            cout << "\n[ERROR] Matrices are NOT EQUAL: m3 and m" << (i + 4) << endl;
            return 1;
        }
    }
    cout << "\n[INFO] Matrices are EQUAL\n";
    return 0;
}






//#include <iostream>
//#include <cstdlib>
//#include <chrono>
//#include <algorithm>
//#include <immintrin.h> 
//#include <omp.h> 
//
//
//using namespace std;
//
//const int MATRIX_SIZE = 1600;
//const int BLOCK_SIZE_L3 = 768;
//const int BLOCK_SIZE_L2 = 448;
//const int BLOCK_SIZE_L1 = 128;
//
//void fillMatrix(int** matrix) {
//    for (int i = 0; i < MATRIX_SIZE; ++i) {
//        for (int j = 0; j < MATRIX_SIZE; ++j) {
//            matrix[i][j] = rand() % 100;
//        }
//    }
//}
//
//void multiplyMatricesStandard(int** A, int** B, int** C) {
//    for (int i = 0; i < MATRIX_SIZE; ++i) {
//        for (int j = 0; j < MATRIX_SIZE; ++j) {
//            C[i][j] = 0;
//            for (int k = 0; k < MATRIX_SIZE; ++k) {
//                C[i][j] += A[i][k] * B[k][j];
//            }
//        }
//    }
//}
//
//void multiplyMatricesBlocked(int** A, int** B, int** C, int blockSize) {
//    for (int i = 0; i < MATRIX_SIZE; i += blockSize) {
//        for (int j = 0; j < MATRIX_SIZE; j += blockSize) {
//            for (int k = 0; k < MATRIX_SIZE; k += blockSize) {
//                for (int ii = i; ii < min(i + blockSize, MATRIX_SIZE); ++ii) {
//                    for (int jj = j; jj < min(j + blockSize, MATRIX_SIZE); ++jj) {
//                        for (int kk = k; kk < min(k + blockSize, MATRIX_SIZE); ++kk) {
//                            C[ii][jj] += A[ii][kk] * B[kk][jj];
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
//
//void multiplyMatricesSSE2(int** A, int** B, int** C, int blockSize) {
//    for (int i = 0; i < MATRIX_SIZE; i += blockSize) {
//        for (int j = 0; j < MATRIX_SIZE; j += blockSize) {
//            for (int k = 0; k < MATRIX_SIZE; k += blockSize) {
//                for (int ii = i; ii < std::min(i + blockSize, MATRIX_SIZE); ++ii) {
//                    for (int jj = j; jj < std::min(j + blockSize, MATRIX_SIZE); ++jj) {
//                        // инициализация векторного регистра с для накопления результатов
//                        __m128i c = _mm_setzero_si128();
//                        int kk;
//
//                        // векторизованная часть для умножения блоков
//                        for (kk = k; kk <= std::min(k + blockSize, MATRIX_SIZE) - 4; kk += 4) {
//                            // загружаем 4 послед. эл-та из А, создаем вектор
//                            __m128i aVec = _mm_loadu_si128((__m128i*) & A[ii][kk]);
//                            // загружаем 4 отдельных элемента из B
//                            __m128i bVec = _mm_set_epi32(B[kk + 3][jj], B[kk + 2][jj], B[kk + 1][jj], B[kk][jj]);
//
//                            // умножаем и аккумулируем 
//                            // _mm_mullo_epi32 - покомпонентное умножение элементов векторов
//                            // _mm_add_epi32 - добавляет результаты умножения к текущему значению регистра
//                            c = _mm_add_epi32(c, _mm_mullo_epi32(aVec, bVec));
//                        }
//                        // результат сохр обратно в массив
//                        int temp[4];
//                        _mm_storeu_si128((__m128i*)temp, c);
//                        // суммируем результаты и записываем в C
//                        C[ii][jj] += temp[0] + temp[1] + temp[2] + temp[3];
//
//                        // обрабатываем оставшиеся элементы обычным скалярным умножением (если их меньше 4)
//                        for (; kk < std::min(k + blockSize, MATRIX_SIZE); ++kk) {
//                            C[ii][jj] += A[ii][kk] * B[kk][jj];
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
//
//
//
//
//void multiplyMatricesOpenMP(int** A, int** B, int** C, int blockSize) {
//#pragma omp parallel // создает команду потоков, где каждый поток будет выполнять свою часть работы
//    {
//        // pragma omp for управляет распределением итераций циклов между потоками
//               // collapse(3) объединяет три вложенных цикла в один единый для эффективного распределения итераций между потоками
//               // schedule(dynamic, 1) использует динамическое распределение итераций с шагом 1 
//               // (потоки динамически получают по одной итерации для обработки, что может помочь лучше сбалансировать нагрузку, если какие-то блоки требуют больше времени для выполнения)
//               // nowait - не ждать потокам завершения всех других потоков после завершения своей работы в цикле
//#pragma omp for collapse(3) schedule(dynamic, 1) nowait
//        for (int i = 0; i < MATRIX_SIZE; i += blockSize) {
//            for (int j = 0; j < MATRIX_SIZE; j += blockSize) {
//                for (int k = 0; k < MATRIX_SIZE; k += blockSize) {
//                    for (int ii = i; ii < std::min(i + blockSize, MATRIX_SIZE); ++ii) {
//                        for (int jj = j; jj < std::min(j + blockSize, MATRIX_SIZE); jj += 4) {
//                            // инициализация аккумулятора для суммы
//                            __m128i c0 = _mm_setzero_si128();
//                            for (int kk = k; kk < std::min(k + blockSize, MATRIX_SIZE); ++kk) {
//                                // загружается один элемент матрицы и распространяется на все элементы 128-битного регистра
//                                __m128i a = _mm_set1_epi32(A[ii][kk]);
//                                // загружается 4 последовательных элемента из столбца матрицы B в регистр
//                                __m128i b = _mm_loadu_si128((__m128i*) & B[kk][jj]);
//                                // умножение и аккумуляция
//                                c0 = _mm_add_epi32(c0, _mm_mullo_epi32(a, b));
//                            }
//                            // критическая секция для защиты записи - чтобы избежать одновременной записи разными потоками
//#pragma omp critical        
//                            {
//                                // загружает текущие значения из матрицы
//                                __m128i tempC = _mm_loadu_si128((__m128i*) & C[ii][jj]);
//                                // добавление к ним результатов накопленного умножения c0.
//                                tempC = _mm_add_epi32(tempC, c0);
//                                // запись обратно в матрицу
//                                _mm_storeu_si128((__m128i*) & C[ii][jj], tempC);
//                            }
//                        }
//                    }
//                }
//            }
//        }
//    }
//}
//
//bool compareMatrices(int** A, int** B) {
//    for (int i = 0; i < MATRIX_SIZE; ++i) {
//        for (int j = 0; j < MATRIX_SIZE; ++j) {
//            if (A[i][j] != B[i][j]) {
//                return false;
//            }
//        }
//    }
//    return true;
//}
//
//void cleanUp(int** matrix) {
//    for (int i = 0; i < MATRIX_SIZE; ++i) {
//        delete[] matrix[i];
//    }
//    delete[] matrix;
//}
//
//int main() {
//    omp_set_num_threads(6); // оптимальное количество потоков в зависимости от системы
//
//    int** A = new int* [MATRIX_SIZE];
//    int** B = new int* [MATRIX_SIZE];
//    int** standardRes = new int* [MATRIX_SIZE];
//    int** blockedResL3 = new int* [MATRIX_SIZE];
//    int** blockedResL2 = new int* [MATRIX_SIZE];
//    int** blockedResL1 = new int* [MATRIX_SIZE];
//
//    int** sse2ResL3 = new int* [MATRIX_SIZE];
//    int** sse2ResL2 = new int* [MATRIX_SIZE];
//    int** sse2ResL1 = new int* [MATRIX_SIZE];
//
//    int** openMPResL3 = new int* [MATRIX_SIZE];
//    int** openMPResL2 = new int* [MATRIX_SIZE];
//    int** openMPResL1 = new int* [MATRIX_SIZE];
//
//    for (int i = 0; i < MATRIX_SIZE; ++i) {
//        A[i] = new int[MATRIX_SIZE];
//        B[i] = new int[MATRIX_SIZE];
//        standardRes[i] = new int[MATRIX_SIZE]();
//        blockedResL3[i] = new int[MATRIX_SIZE]();
//        blockedResL2[i] = new int[MATRIX_SIZE]();
//        blockedResL1[i] = new int[MATRIX_SIZE]();
//
//
//        sse2ResL3[i] = new int[MATRIX_SIZE]();
//        sse2ResL2[i] = new int[MATRIX_SIZE]();
//        sse2ResL1[i] = new int[MATRIX_SIZE]();
//
//        openMPResL3[i] = new int[MATRIX_SIZE]();
//        openMPResL2[i] = new int[MATRIX_SIZE]();
//        openMPResL1[i] = new int[MATRIX_SIZE]();
//    }
//
//    fillMatrix(A);
//    fillMatrix(B);
//
//
//    cout << "              Block algorithm time:\n";
//    auto start = chrono::high_resolution_clock::now();
//    multiplyMatricesBlocked(A, B, blockedResL3, BLOCK_SIZE_L3);
//    auto end = chrono::high_resolution_clock::now();
//    cout << "L3: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesBlocked(A, B, blockedResL2, BLOCK_SIZE_L2);
//    end = chrono::high_resolution_clock::now();
//    cout << "L2: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesBlocked(A, B, blockedResL1, BLOCK_SIZE_L1);
//    end = chrono::high_resolution_clock::now();
//    cout << "L1: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n\n";
//
//
//    cout << "              SSE2 time:\n";
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesSSE2(A, B, sse2ResL3, BLOCK_SIZE_L3);
//    end = chrono::high_resolution_clock::now();
//    cout << "L3: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesSSE2(A, B, sse2ResL2, BLOCK_SIZE_L2);
//    end = chrono::high_resolution_clock::now();
//    cout << "L2: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesSSE2(A, B, sse2ResL1, BLOCK_SIZE_L1);
//    end = chrono::high_resolution_clock::now();
//    cout << "L1: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n\n";
//
//
//    cout << "              OpenMP time: \n";
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesOpenMP(A, B, openMPResL3, BLOCK_SIZE_L3);
//    end = chrono::high_resolution_clock::now();
//    cout << "L3: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesOpenMP(A, B, openMPResL2, BLOCK_SIZE_L2);
//    end = chrono::high_resolution_clock::now();
//    cout << "L2: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    start = chrono::high_resolution_clock::now();
//    multiplyMatricesOpenMP(A, B, openMPResL1, BLOCK_SIZE_L1);
//    end = chrono::high_resolution_clock::now();
//    cout << "L1: " << chrono::duration<double>(end - start).count() * 1000 << " ms\n";
//
//    compareMatrices(blockedResL3, blockedResL2) && compareMatrices(blockedResL3, blockedResL1) &&
//        compareMatrices(blockedResL3, sse2ResL3) && compareMatrices(blockedResL3, sse2ResL2) &&
//        compareMatrices(blockedResL3, sse2ResL1) && compareMatrices(blockedResL3, openMPResL3)
//        && compareMatrices(blockedResL3, openMPResL2) && compareMatrices(blockedResL3, openMPResL1)
//        ? cout << "Matrices are equal." << endl
//        : cout << "Matrices are NOT equal." << endl;
//
//    cleanUp(A);
//    cleanUp(B);
//    cleanUp(standardRes);
//    cleanUp(blockedResL3);
//    cleanUp(blockedResL2);
//    cleanUp(blockedResL1);
//    cleanUp(sse2ResL3);
//    cleanUp(sse2ResL2);
//    cleanUp(sse2ResL1);
//
//    return 0;
//}