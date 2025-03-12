from mpi4py import MPI
import numpy as np
import time

from matrix import Matrix
from config import ARRAY_SIZE, ARRAY_DIM
from utils import create_groups


if __name__ == '__main__':
    comm = MPI.COMM_WORLD
    rank = comm.Get_rank()
    process_count = comm.Get_size()

    a, b, c = Matrix.build_matrices()

    processes, groups = create_groups(comm, process_count)

    # Получаем группу и идентификатор группы для текущего процесса
    gid, sgroup = processes[comm.rank]
    scomm = comm.Create(sgroup)

    reference_matrix = Matrix.get_etalon_matrix(comm, a, b)

    start = time.time()

    # Распределение индексов для каждого процесса в группе
    indexes = np.array_split(range(ARRAY_SIZE), scomm.size)
    indexes = scomm.scatter(indexes)

    # Выполняем частичное умножение матрицы
    c_elements = Matrix.mul_matrix_partial(a, b, indexes[0], indexes[-1] + 1, ARRAY_DIM)

    # Собираем результаты от всех процессов в группе
    ans = scomm.gather(c_elements)

    # Если текущий процесс - корневой в своей группе, объединяем частичные результаты
    if scomm.rank == 0:
        i = 0
        for elements in ans:
            Matrix.copy_matrix_slice(c, elements, i, i + len(elements), ARRAY_DIM)
            i += len(elements)

    # Барьер для синхронизации
    scomm.barrier()
    end = time.time()

    # Собираем время выполнения каждого процесса
    times = scomm.allgather(end - start)

    # Выводим информацию о процессе
    print(f"Group {gid}, Global rank {rank}, Rank in group {scomm.rank}, Group Size: {scomm.size}, time: {max(times)}")

    Matrix.compare_matrices(c, reference_matrix, gid, scomm)

    comm.barrier()

    # Если текущий процесс - корневой в своей группе, выводим результат умножения
    if scomm.rank == 0:
        print(c)

