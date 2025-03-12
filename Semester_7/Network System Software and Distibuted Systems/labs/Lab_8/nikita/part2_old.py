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
parser.add_argument("-g","--groups", type=int, required=True, help="groups count")

args = parser.parse_args()

aname = "/home/alexei/a.m"
bname = "/home/alexei/b.m"

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

afile = MPI.File.Open(comm, aname, amode=MPI.MODE_RDONLY)
bfile = MPI.File.Open(comm, bname, amode=MPI.MODE_RDONLY)

abuf = bytearray(afile.Get_size())
bbuf = bytearray(bfile.Get_size())

afile.Read_all(abuf)
bfile.Read_all(bbuf)

a = pickle.loads(abuf)
b = pickle.loads(bbuf)


afile.Close()
bfile.Close()

num_rows, num_columns = a.shape

c = np.zeros((num_rows, num_columns), dtype=np.int64)

if comm.rank == 0:
    groups = get_by_group(size,  args.groups)
else:
    groups = list()

groups = comm.bcast(groups, root=0)
dist = {}

for gid, ranks in enumerate(groups):
    sgroup = MPI.Group.Incl(comm.Get_group(), ranks)
    dist.update({rank: (gid, sgroup) for rank in ranks})

gid, sgroup = dist[comm.rank]
scomm = comm.Create(sgroup)



cname = f"out/group-{gid}.matrix"

os.makedirs("out", exist_ok=True)

try:
    MPI.File.Delete(cname)
except MPI.Exception:
    pass

cfile = MPI.File.Open(scomm, cname, MPI.MODE_WRONLY | MPI.MODE_CREATE)

start = time.time()

indexes = np.array_split(range(num_columns * num_rows), scomm.size)
indexes = scomm.scatter(indexes)

c_elements = matrix.mul_matrix_partial(a,b,indexes[0], indexes[-1] + 1, num_columns)

computations = StringIO()

index = indexes[0]

for element in c_elements:
    if (index) and ((index % num_columns) == 0):
        computations.write("\n")
    computations.write(f"{np.int64(element):>5} ")
    index += 1

s = computations.getvalue().encode()
cfile.Write_ordered(s)
ans = scomm.gather(c_elements)


if scomm.rank == 0:
    i = 0
    for elements in ans:
        matrix.copy_matrix_slice(c, elements, i, i + len(elements), num_columns)
        i += len(elements)


scomm.barrier()

end = time.time()

cfile.Close()

times = scomm.allgather(end-start)

print("Global rank: %s, Group: %s, Rank in group: %s, Group Size: %s, time: %s" %
            (comm.rank, gid, scomm.rank, scomm.size, max(times)))

if scomm.rank == 0:
    total_result = np.dot(a, b)
    print(np.array_equal(total_result, c))
