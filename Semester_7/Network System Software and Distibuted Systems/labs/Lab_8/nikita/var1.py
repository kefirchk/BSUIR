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

comm.Bcast(a, root=0)
comm.Bcast(b, root=0)


comm.Barrier()


start, stop = matrix.get_rank_indexes(rank,size, ARRAY_DIM)
c_elements = matrix.mul_matrix_partial(a, b,start, stop, ARRAY_DIM)
matrix.copy_matrix_slice(c, c_elements, start, stop, ARRAY_DIM)
if rank == 0:
    # main process
    status = MPI.Status()
    for i in range(size-1):
        c_elements = comm.recv(source=MPI.ANY_SOURCE,tag=10, status=status)
        source = status.Get_source()
        start, stop = matrix.get_rank_indexes(source, size, ARRAY_DIM)
        matrix.copy_matrix_slice(c, c_elements, start, stop, ARRAY_DIM)

    end_time = time.perf_counter()
    print(end_time - start_time)
    print(np.array_equal(c, np.dot(a,b)))

else:
    comm.send(c_elements, dest=0,tag=10)


comm.Barrier()
MPI.Finalize()
