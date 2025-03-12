import time

from mpi4py import MPI
import numpy as np
import matrix

start_time = time.perf_counter()

ARRAY_DIM = 600
ARRAY_SIZE = ARRAY_DIM * ARRAY_DIM
comm = MPI.COMM_WORLD
rank = comm.Get_rank()
size = comm.Get_size()

a = np.random.randint(0, 10, size=(ARRAY_DIM, ARRAY_DIM))
b = np.random.randint(0, 10, size=(ARRAY_DIM, ARRAY_DIM))
c = np.zeros((ARRAY_DIM, ARRAY_DIM), dtype=np.int64)

request_a = comm.Ibcast(a, root=0)
request_b = comm.Ibcast(b, root=0)

request_a.Wait()
request_b.Wait()

if rank == 0:

    c_parts = []
    reqs = []

    for i in range(size-1):
        c_elements = np.empty(ARRAY_SIZE, dtype=np.int64)
        req = comm.Irecv(c_elements ,source=i+1, tag=10)
        reqs.append(req)
        c_parts.append(c_elements)

    start, stop = matrix.get_rank_indexes(rank,size, ARRAY_DIM)
    c_elements = matrix.mul_matrix_partial(a, b, start, stop, ARRAY_DIM)
    matrix.copy_matrix_slice(c, c_elements, start, stop, ARRAY_DIM)
    MPI.Request.Waitall(reqs)
    for i in range(size-1):
        start, stop = matrix.get_rank_indexes(i+1, size, ARRAY_DIM)
        matrix.copy_matrix_slice(c, c_parts[i], start, stop, ARRAY_DIM)

    end_time = time.perf_counter()
    print(end_time - start_time)
    print(np.array_equal(c, np.dot(a, b)))

else:
    start, stop = matrix.get_rank_indexes(rank,size, ARRAY_DIM)
    c_elements = matrix.mul_matrix_partial(a, b, start, stop, ARRAY_DIM)
    c_elements = np.array(c_elements, dtype=np.int64)
    comm.Isend(c_elements, dest=0, tag=10)

MPI.Finalize()
