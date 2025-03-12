import numpy as np


def mul_matrix_partial(a, b, start, stop, dim):
    # Преобразуем матрицу b в транспонированную форму для эффективного умножения
    b_t = b.T
    # Вычисляем индексы строк и столбцов
    rows = np.arange(start, stop) // dim
    cols = np.arange(start, stop) % dim
    # Векторное умножение для всех необходимых пар строк и столбцов
    c = np.einsum('ij,ij->i', a[rows], b_t[cols])
    return c


def copy_matrix_slice(a, elements, start, stop, dim):
    index = 0
    for ind in range(start, stop):
        i = ind // dim
        j = ind % dim
        a[i,j] = elements[index]
        index += 1


def get_rank_indexes(rank, size, dim):
    total_size = dim * dim
    rows_per_process = total_size // size
    extra_rows = total_size % size

    start = rank * rows_per_process + min(rank, extra_rows)
    stop = start + rows_per_process + (1 if rank < extra_rows else 0)

    return start, stop
