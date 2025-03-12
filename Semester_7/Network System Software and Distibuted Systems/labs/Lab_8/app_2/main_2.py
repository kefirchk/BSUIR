from mpi4py import MPI
import numpy as np
import time
from io import StringIO

from mpi_file import MPIFile
from matrix import Matrix
from utils import create_groups


if __name__ == "__main__":
    comm = MPI.COMM_WORLD
    group = comm.Get_group()
    process_count = comm.Get_size()

    a, b, c = Matrix.build_matrices_from_file(comm)
    num_rows, num_columns = a.shape

    processes, groups = create_groups(comm, process_count)
    gid, sgroup = processes[comm.rank]
    scomm = comm.Create(sgroup)

    MATRIX_C_NAME = f"results/group_{gid}_matrix_C"

    if comm.rank == 0:
        try:
            MPI.File.Delete(MATRIX_C_NAME)
        except MPI.Exception:
            pass

    with MPIFile(scomm, MATRIX_C_NAME, MPI.MODE_WRONLY + MPI.MODE_CREATE) as cfile:
        start = time.time()

        indexes = np.array_split(range(num_columns * num_rows), scomm.size)
        indexes = scomm.scatter(indexes)

        c_elements = Matrix.mul_matrix_partial(a,b,indexes[0], indexes[-1] + 1, num_columns)

        computations = StringIO()

        index = indexes[0]
        for element in c_elements:
            if index and (index % num_columns) == 0:
                computations.write("\n")
            computations.write(f"{element} ")
            index += 1

        cfile.Write_ordered(computations.getvalue().encode('utf-8'))
        ans = scomm.gather(c_elements)

        # Объединяем результаты по группам
        if scomm.rank == 0:
            i = 0
            for elements in ans:
                Matrix.copy_matrix_slice(c, elements, i, i + len(elements), num_columns)
                i += len(elements)
        scomm.barrier()

        end = time.time()

    times = scomm.allgather(end-start)
    print(f"Global rank: {comm.rank}, Group: {gid}, Rank in group: {scomm.rank}, Group Size: {scomm.size}, time: {max(times)}")

