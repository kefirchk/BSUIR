from mpi4py import MPI
import numpy as np
import time
from io import StringIO
import os

from matrix import Matrix
from utils import create_groups


def write_file(filename, data):
    """Функция для записи данных в файл."""
    with open(filename, 'w') as f:
        f.write(data)


if __name__ == "__main__":
    comm = MPI.COMM_WORLD
    group = comm.Get_group()
    process_count = comm.Get_size()

    # Инициализация матриц
    a, b, c = Matrix.build_matrices_from_file(comm)
    num_rows, num_columns = a.shape

    # Создание групп процессов
    processes, groups = create_groups(comm, process_count)
    gid, sgroup = processes[comm.rank]
    scomm = comm.Create(sgroup)

    # Общий файл для матрицы C
    MATRIX_C_NAME = f"results/group_{gid}_matrix_C"

    if comm.rank == 0:
        try:
            # Удаляем файл, если он уже существует
            os.remove(MATRIX_C_NAME)
        except OSError:
            pass

    start = time.time()

    # Разбиение индексов между процессами
    indexes = np.array_split(range(num_columns * num_rows), scomm.size)
    indexes = scomm.scatter(indexes)

    # Вычисление части матрицы
    c_elements = Matrix.mul_matrix_partial(a, b, indexes[0], indexes[-1] + 1, num_columns)

    # Сбор результатов
    ans = scomm.gather(c_elements)

    # На ранге 0 объединяем все результаты
    if scomm.rank == 0:
        i = 0
        for elements in ans:
            Matrix.copy_matrix_slice(c, elements, i, i + len(elements), num_columns)
            i += len(elements)

    scomm.barrier()

    end = time.time()

    times = scomm.allgather(end - start)

    print(f"Global rank: {comm.rank}, Group: {gid}, Rank in group: {scomm.rank}, Group Size: {scomm.size}, time: {max(times)}")

    # Записываем полный результат в файл на ранге 0
    if scomm.rank == 0:
        # Преобразование матрицы в строку для записи
        computations = StringIO()
        for row in c:
            computations.write(" ".join(f"{np.int64(val):>5}" for val in row) + "\n")

        # Запись данных в файл
        write_file(MATRIX_C_NAME, computations.getvalue())

    # Проверка корректности результатов на ранге 0
    if scomm.rank == 0:
        print(a)
        print("------------------------------------------------------------------")
        print(b)
        total_result = np.dot(a, b)
        print(np.array_equal(total_result, c))
    

