#include "Matrix.h"

// Исходные данные:
// - кэш L3 = 6 Мб;
// - кэш L2 = 2 Мб;
// - кэш L1 = 320 Кб.

int main() {
    srand(time(0));

    Matrix m1(2048, 512), m2(512, 4096);
    vector<Matrix> res_matrices;

    Matrix m3 = m1.multiply_without_cache(m2, "without cache");
    
    cout << "=============== USING << BLOCKS >> ===============" << endl;
    res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 512, "with L3 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 128, "with L2 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_blocks(m2, 64, "with L1 cache"));

    cout << "=============== USING << TRANSPOSITION >> ===============" << endl;
    res_matrices.push_back(m1.multiply_with_cache_using_transposition(m2, 512, "with L3 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_transposition(m2, 128, "with L2 cache"));
    res_matrices.push_back(m1.multiply_with_cache_using_transposition(m2, 16, "with L1 cache"));

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



