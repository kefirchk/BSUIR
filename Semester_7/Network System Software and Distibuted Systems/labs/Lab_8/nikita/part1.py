from mpi4py import MPI
import numpy as np
from argparse import ArgumentParser
import time
import matrix
from get_proc import get_by_group


ARRAY_DIM = 20
ARRAY_SIZE = ARRAY_DIM * ARRAY_DIM

comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

a = np.random.randint(0, 10, size=(ARRAY_DIM, ARRAY_DIM))
b = np.random.randint(0, 10, size=(ARRAY_DIM, ARRAY_DIM))
c = np.zeros((ARRAY_DIM, ARRAY_DIM), dtype=np.int64)

comm.Bcast(a, root=0)
comm.Bcast(b, root=0)

parser = ArgumentParser(description="groups")
parser.add_argument("-g","--groups", type=int, required=True, help="groups count")
args = parser.parse_args()

if comm.rank == 0:
    groups = get_by_group(size,  args.groups)
else:
    groups = list()

groups = comm.bcast(groups, root=0)

dist =  {}

for gid, ranks in enumerate(groups):
    sgroup = MPI.Group.Incl(comm.Get_group(), ranks)
    dist.update({rank: (gid, sgroup) for rank in ranks})


gid, sgroup = dist[comm.rank]
scomm = comm.Create(sgroup)

start  = time.time()

indexes = np.array_split(range(ARRAY_DIM * ARRAY_DIM), scomm.size)
indexes = scomm.scatter(indexes)
c_elements = matrix.mul_matrix_partial(a,b,indexes[0], indexes[-1] + 1, ARRAY_DIM)
ans = scomm.gather(c_elements)
if scomm.rank == 0:
    i = 0
    for elements in ans:
        matrix.copy_matrix_slice(c, elements, i, i + len(elements), ARRAY_DIM)
        i += len(elements)
scomm.barrier()
end = time.time()
times = scomm.allgather(end-start)

print(f"Group {gid}, Global rank {rank}, Rank in group {scomm.rank}, Group Size: {scomm.size}, time: {max(times)}")
comm.barrier()

if scomm.rank == 0:
    total_result = np.dot(a, b)
    print(np.array_equal(total_result, c))



