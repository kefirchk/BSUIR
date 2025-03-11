# Вариант №6
# y = sin(x) + cos(4x)
# БПФ с прореживанием по частоте
# N = 16

import numpy as np
import matplotlib.pyplot as plt
import math

N = 16
WINDOW_SIZE = [16, 10]


def func(x):
    return np.sin(x) + np.cos(4*x)



def ABS(fft):
    return [math.sqrt(element.real ** 2 + element.imag ** 2) for element in fft]



def FFT(x):
    N = len(x)
    if N <= 1:
        return x
    even = FFT(x[0::2])
    odd = FFT(x[1::2])
    T = [np.exp(-2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
    return [even[k] + T[k] for k in range(N // 2)] + \
           [even[k] - T[k] for k in range(N // 2)]



def iFFT(x):
    N = len(x)
    if N <= 1:
        return x
    even = iFFT(x[0::2])
    odd = iFFT(x[1::2])
    T = [np.exp(2j * np.pi * k / N) * odd[k] for k in range(N // 2)]
    return [even[k] + T[k] for k in range(N // 2)] + \
           [even[k] - T[k] for k in range(N // 2)]



def main():
    # Создаем окно для графиков
    figure = plt.figure('Лабораторная работа №1: Преобразование Фурье', figsize=WINDOW_SIZE)
    figure.suptitle('Лабораторная работа №1\nПреобразование Фурье')
    
    # Делаем место под 10 графиков
    axis = figure.subplots(2, 4)

    # Создаем массив значений x от 0 до 2*pi
    origin_x = np.linspace(0, 2*np.pi, 100)
    x = np.linspace(0, 2*np.pi, N)

    # Вычисляем значения функции y = sin(x) + cos(4x)
    origin_y = func(origin_x)
    y = func(x)

    # ---------- Original signal ----------
    plot = plt.figure("Лабораторная работа №1: Исходный сигнал")
    plot.suptitle('График функции y = sin(x) + cos(4x)')
    plt.plot(origin_x, origin_y)

    # ---------- LIBRARY CALCULATING ----------
    fft_lib = np.fft.fft(y)
    ifft_lib = np.fft.ifft(fft_lib)

    axis[0, 0].set_title('FFT Re (numpy)')
    axis[0, 0].stem(range(N), np.real(fft_lib))

    axis[0, 1].set_title('FFT Im (numpy)')
    axis[0, 1].stem(range(N), np.imag(fft_lib))

    axis[0, 2].set_title('FFT MAG (numpy)')
    axis[0, 2].stem(range(N), np.abs(fft_lib))
    
    axis[0, 3].set_title('Inverse FFT (numpy)')
    axis[0, 3].plot(range(N), ifft_lib)

    # ---------- MANUAL CALCULATING ----------    
    fft_manual = FFT(y)
    ifft_manual = [elem / N for elem in iFFT(fft_manual)]

    axis[1, 0].set_title('FFT Re (manual)')
    axis[1, 0].stem(range(N), np.real(fft_manual))

    axis[1, 1].set_title('FFT Im (manual)')
    axis[1, 1].stem(range(N), np.imag(fft_manual))

    axis[1, 2].set_title('FFT MAG (manual)')
    axis[1, 2].stem(range(N), ABS(fft_manual))

    axis[1, 3].set_title('Inverse FFT (manual)')
    axis[1, 3].plot(range(N), ifft_manual)

    plt.show()



if __name__=="__main__":
    main()