from mpi4py import MPI
import numpy as np
import sys
from argparse import ArgumentParser
import time
from io import StringIO
import pickle
import matrix
from get_proc import get_by_group
import os

parser = ArgumentParser()
parser.add_argument("-g", "--groups", type=int, required=True, help="groups count")

args = parser.parse_args()

aname = "a.m"
bname = "b.m"

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

# Обычные функции для работы с файлами
def read_file(filename):
    with open(filename, 'rb') as f:
        return pickle.load(f)

def write_file(filename, data):
    with open(filename, 'w') as f:
        f.write(data)

# Загрузка данных из файлов
a = read_file(aname)
b = read_file(bname)

num_rows, num_columns = a.shape

c = np.zeros((num_rows, num_columns), dtype=np.int64)

if comm.rank == 0:
    groups = get_by_group(size, args.groups)
else:
    groups = list()

groups = comm.bcast(groups, root=0)
dist = {}

for gid, ranks in enumerate(groups):
    sgroup = MPI.Group.Incl(comm.Get_group(), ranks)
    dist.update({rank: (gid, sgroup) for rank in ranks})

gid, sgroup = dist[comm.rank]
scomm = comm.Create(sgroup)

cname = f"out/group-{gid}.matrix"  # Единый файл для всей матрицы

os.makedirs("out", exist_ok=True)

# Начало вычислений
start = time.time()

indexes = np.array_split(range(num_columns * num_rows), scomm.size)
indexes = scomm.scatter(indexes)

# Часть вычислений для группы
c_elements = matrix.mul_matrix_partial(a, b, indexes[0], indexes[-1] + 1, num_columns)

# Собираем результаты от всех процессов
ans = scomm.gather(c_elements)

# Объединение результатов для группы на ранге 0
if scomm.rank == 0:
    i = 0
    for elements in ans:
        matrix.copy_matrix_slice(c, elements, i, i + len(elements), num_columns)
        i += len(elements)

scomm.barrier()

end = time.time()

times = scomm.allgather(end - start)

print("Global rank: %s, Group: %s, Rank in group: %s, Group Size: %s, time: %s" %
      (comm.rank, gid, scomm.rank, scomm.size, max(times)))

# Записываем результат в файл только на процессе с рангом 0
if scomm.rank == 0:
    # Преобразуем матрицу в строку для записи
    computations = StringIO()
    for row in c:
        computations.write(" ".join(f"{np.int64(val):>5}" for val in row) + "\n")

    # Запись в файл
    write_file(cname, computations.getvalue())

# Проверка результата на процессе с рангом 0
if scomm.rank == 0:
    total_result = np.dot(a, b)
    print(np.array_equal(total_result, c))

