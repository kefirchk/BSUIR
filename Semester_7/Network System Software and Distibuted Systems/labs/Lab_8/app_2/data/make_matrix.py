from argparse import ArgumentParser
import numpy as np

# Парсинг аргументов командной строки
parser = ArgumentParser()
parser.add_argument("-r", "--rows", type=int, required=True,
        help="specify rows count")
parser.add_argument("-c", "--columns", type=int, required=True,
        help="specify columns count")
args = parser.parse_args()

rows = args.rows
cols = args.columns

# Генерация матриц A и B
# a = np.arange(rows * cols).reshape(rows, cols)
# b = np.arange(rows * cols).reshape(rows, cols)

a = np.random.randint(0, 101, size=(rows, cols))
b = np.random.randint(0, 101, size=(rows, cols))

# Сохранение матриц в текстовые файлы
np.savetxt("matrix_A.txt", a, fmt='%d', delimiter=' ')
np.savetxt("matrix_B.txt", b, fmt='%d', delimiter=' ')

print("Matrices A and B have been saved as text files.")
