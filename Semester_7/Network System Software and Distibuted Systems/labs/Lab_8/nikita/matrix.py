import numpy as np

def mul_matrix(a,b,c,dim):
    """multiply matrix"""
    for i in range(dim):
        for j in range(dim):
            sum = 0
            for k in range(dim):
                sum += a[i, k] * b[k,j]
            c[i,j] = sum


def mul_matrix_partial(a,b, start, stop, dim):
    '''Multiply elemetns two matrix
       Return list
    '''
    c =  []
    l = stop - start
    c = np.empty(l)
    c_index = 0
    for index in range(start, stop):
        i = index // dim
        j = index % dim
        sum = 0
        for k in range(dim):
            sum += a[i, k] * b[k,j]
        c[c_index] = sum
        c_index += 1
    return c


def copy_matrix_slice(a, elements, start, stop, dim):
    """Copy list to matrix"""
    index = 0
    for ind in range(start, stop):
        i = ind // dim
        j = ind % dim
        a[i,j] = elements[index]
        index += 1


def get_rank_indexes(rank, size, dim):
    total_size = dim * dim
    rows_per_process = total_size // size
    extra_rows = total_size % size

    start = rank * rows_per_process + min(rank, extra_rows)
    stop = start + rows_per_process + (1 if rank < extra_rows else 0)

    return start, stop