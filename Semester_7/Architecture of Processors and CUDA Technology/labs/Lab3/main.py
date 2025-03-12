import random
import time
import numpy as np
import numpy as np
import pycuda.autoinit
import pycuda.driver as cuda
from pycuda.compiler import SourceModule

cuda_kernel = """
__global__ void transform_matrix(int *matrix, int *transformed_matrix, int M, int N)
{
    int col = blockIdx.x * blockDim.x + threadIdx.x;
    int row = blockIdx.y * blockDim.y + threadIdx.y;

    if (col < N && row < M / 4) {
        int base_idx = row * 4 * N + col;  // Индекс верхней строки 4x1 окна

        // Преобразование 4x1 в 2x2
        transformed_matrix[row * 2 * (N * 2) + col * 2] = matrix[base_idx];           // (0, 0)
        transformed_matrix[row * 2 * (N * 2) + col * 2 + 1] = matrix[base_idx + N];       // (0, 1)
        transformed_matrix[(row * 2 + 1) * (N * 2) + col * 2] = matrix[base_idx + 2 * N];   // (1, 0)
        transformed_matrix[(row * 2 + 1) * (N * 2) + col * 2 + 1] = matrix[base_idx + 3 * N]; // (1, 1)
    }
}
"""

def generate_matrix(M, N):
    return [[random.randint(10, 99) for _ in range(N)] for _ in range(M)]

def transform_matrix(matrix):
    M = len(matrix)
    N = len(matrix[0])

    if M % 4 != 0:
        raise ValueError("Rows amount % 4 must be equals 0")

    transformed_matrix = [[0] * (N * 2) for _ in range(M // 2)]

    for j in range(N):
        for i in range(0, M, 4):
            transformed_matrix[i // 2][j * 2] = matrix[i][j]
            transformed_matrix[i // 2][j * 2 + 1] = matrix[i + 1][j]
            transformed_matrix[i // 2 + 1][j * 2] = matrix[i + 2][j]
            transformed_matrix[i // 2 + 1][j * 2 + 1] = matrix[i + 3][j]

    return transformed_matrix





def transform_matrix_cuda(matrix):
    M = len(matrix)
    N = len(matrix[0])

    matrix_flat = np.array(matrix, dtype=np.int32).flatten()
    transformed_matrix = np.zeros((M // 2, N * 2), dtype=np.int32)

    mod = SourceModule(cuda_kernel)
    transform_matrix = mod.get_function("transform_matrix")
    matrix_gpu = cuda.mem_alloc(matrix_flat.nbytes)
    transformed_matrix_gpu = cuda.mem_alloc(transformed_matrix.nbytes)
    cuda.memcpy_htod(matrix_gpu, matrix_flat)

    start_event = cuda.Event()
    end_event = cuda.Event()
    start_event.record()

    block_size = (16, 16, 1)
    grid_size = (N // block_size[0] + 1, (M // 4) // block_size[1] + 1, 1)
    transform_matrix(matrix_gpu, transformed_matrix_gpu, np.int32(M), np.int32(N), block=block_size, grid=grid_size)

    cuda.Context.synchronize()

    end_event.record()
    end_event.synchronize()
    elapsed_time = start_event.time_till(end_event)

    cuda.memcpy_dtoh(transformed_matrix, transformed_matrix_gpu)
    matrix_gpu.free()
    transformed_matrix_gpu.free()
    transformed_matrix_list = transformed_matrix.tolist()

    return transformed_matrix_list, elapsed_time

def print_matrix(matrix):
    for row in matrix:
        print(row)

def print_submatrix(matrix, start_row, start_col, m, k):
    for i in range(start_row, start_row + m):
        if i < len(matrix):
            print(matrix[i][start_col:start_col + k])
    print()

if __name__ == '__main__':
    M, N = 10000, 10000
    start_time = time.perf_counter()
    matrix = generate_matrix(M, N)
    end_time = time.perf_counter()
    init_time = (end_time - start_time) * 1000
    print(f"Init time is             {init_time:.1f} ms")

    start_time = time.perf_counter()
    transformed_matrix = transform_matrix(matrix)
    end_time = time.perf_counter()
    execution_time = (end_time - start_time) * 1000
    print(f"Execution time is        {execution_time:.1f} ms")

    transformed_matrix_cuda, time = transform_matrix_cuda(matrix)
    print(f"Execution time (cuda) is {time:.1f} ms")

    if transformed_matrix == transformed_matrix_cuda:
        print(f'Matrices are EQUAL')
    else:
        print(f'Matrices are NOT equal')

    print_submatrix(transformed_matrix, 4000, 4000, 3, 5)
    print_submatrix(transformed_matrix_cuda, 4000, 4000, 3, 5)

    print_submatrix(matrix, 0, 0, 4, 1)
    print_submatrix(transformed_matrix, 0, 0, 2, 2)
    print_submatrix(transformed_matrix_cuda, 0, 0, 2, 2)
