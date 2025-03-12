from mpi4py import MPI


class MPIFile:
    def __init__(self, comm, filename, amode):
        self.file = MPI.File.Open(comm, filename, amode)

    def __enter__(self):
        return self.file

    def __exit__(self, exc_type, exc_val, exc_tb):
        self.file.Close()
