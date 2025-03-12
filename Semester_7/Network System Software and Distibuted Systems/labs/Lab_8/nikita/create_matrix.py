from argparse import ArgumentParser
import numpy as np
import pickle


parser = ArgumentParser()
parser.add_argument("-d", "--dim", type=int, required=True,
        help="dim of matrix")

args = parser.parse_args()
dim = args.dim


a = np.random.randint(0, 10, size=(dim * dim), dtype=np.int64).reshape(dim, dim)
b = np.random.randint(0, 10, size=(dim * dim), dtype=np.int64).reshape(dim, dim)

with open("a.m", "wb+") as file:
    pickle.dump(a, file)

with open("b.m", "wb+") as file:
    pickle.dump(b, file)