import sys

import numpy as np
from mpi4py import MPI

# from mpi_file import MPIFile
from config import ARRAY_SIZE, ARRAY_DIM, MATRIX_B_NAME, MATRIX_A_NAME


class Matrix:
    @staticmethod
    def build_matrices():
        a = np.arange(ARRAY_SIZE).reshape(ARRAY_DIM, ARRAY_DIM)
        b = np.arange(ARRAY_SIZE, 2 * ARRAY_SIZE).reshape(ARRAY_DIM, ARRAY_DIM)
        c = np.zeros((ARRAY_DIM, ARRAY_DIM), dtype=np.int32)
        return a, b, c

    @staticmethod
    def build_matrices_from_file(comm):
        """Функция для чтения матриц из файлов"""
        rank = comm.Get_rank()

        # Чтение файлов с матрицами на всех процессах
        if rank == 0:
            # Открытие и чтение файлов с помощью стандартных функций Python
            with open(MATRIX_A_NAME, 'r') as afile:
                abuf = afile.read()

            with open(MATRIX_B_NAME, 'r') as bfile:
                bbuf = bfile.read()

            # Преобразование строк в матрицы с помощью numpy
            a = np.loadtxt(abuf.splitlines(), dtype=int)
            b = np.loadtxt(bbuf.splitlines(), dtype=int)

            # Проверка размеров матриц
            num_rows, num_columns = a.shape
            if (num_columns, num_rows) != b.shape:
                print("matrix shapes don't match")
                sys.exit(1)

            # Создание пустой матрицы для результата
            c = np.zeros((num_rows, num_columns), dtype=np.int32)
        else:
            a = None
            b = None
            c = None

        # Широковещательная передача матриц всем процессам
        a = comm.bcast(a, root=0)
        b = comm.bcast(b, root=0)
        c = comm.bcast(c, root=0)

        return a, b, c

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
