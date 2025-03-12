import numpy as np

from config import ARRAY_SIZE, ARRAY_DIM


class Matrix:
    @staticmethod
    def build_matrices():
        a = np.arange(ARRAY_SIZE).reshape(ARRAY_DIM, ARRAY_DIM)
        b = np.arange(ARRAY_SIZE, 2 * ARRAY_SIZE).reshape(ARRAY_DIM, ARRAY_DIM)
        c = np.zeros((ARRAY_DIM, ARRAY_DIM), dtype=np.int32)
        return a, b, c

    @staticmethod
    def compare_matrices(c, reference_matrix, gid, scomm):
        if scomm.rank == 0:
            matrices_equal = np.array_equal(c, reference_matrix)
            if matrices_equal:
                print(f"Group {gid}: Calculated matrix matches reference matrix.")
            else:
                print(f"Group {gid}: Calculated matrix does NOT match reference matrix.")

    @staticmethod
    def get_etalon_matrix(comm, a, b):
        # В процессе с рангом 0 вычисляем эталонную матрицу
        if comm.rank == 0:
            reference_matrix = np.dot(a, b)  # Эталонное умножение матриц
        else:
            reference_matrix = None

        # Распространяем эталонную матрицу по всем процессам
        reference_matrix = comm.bcast(reference_matrix, root=0)
        return reference_matrix

    @staticmethod
    def mul_matrix_partial(a, b, start, stop, dim):
        b_t = b.T
        rows = np.arange(start, stop) // dim
        cols = np.arange(start, stop) % dim
        c = np.einsum('ij,ij->i', a[rows], b_t[cols])
        return c

    @staticmethod
    def copy_matrix_slice(a, elements, start, stop, dim):
        index = 0
        for ind in range(start, stop):
            i = ind // dim
            j = ind % dim
            a[i,j] = elements[index]
            index += 1

    @staticmethod
    def get_rank_indexes(rank, size, dim):
        total_size = dim * dim
        rows_per_process = total_size // size
        extra_rows = total_size % size

        start = rank * rows_per_process + min(rank, extra_rows)
        stop = start + rows_per_process + (1 if rank < extra_rows else 0)

        return start, stop