# Вариант №3
# y = cos(2x); z = sin(5x)
# N = 8

import numpy as np
import matplotlib.pyplot as plt
import math

N = 8
WINDOW_SIZE = [16, 10]

def func_y(x):
    return np.cos(2*x)

def func_z(x):
    return np.sin(5*x)

def calc_line_conv(y, z, N):
    s = [0] * (2 * N - 1)      # результирующая функция
    for n in range(2 * N - 1):
        sum = 0
        for m in range(N):
            if n - m < 0:
                break
            if n - m > (N-1):
                continue
            sum += y[m] * z[n - m]
        s[n] = sum
    return s

def calc_cycl_conv(y, z, N):
    s = [0] * N                # результирующая функция
    for n in range(N):
        sum = 0
        for m in range(N):
            sum += y[m] * z[(n - m) % N]
        s[n] = sum
    return s

def calc_correlation(y, z, N):
    ans = [0] * N
    for i in range(N):
        for j in range(N):
            if i + j >= N:
                continue
            ans[i] += y[j] * z[i + j]
    return ans


def main():
    # Создаем окно для графиков
    figure = plt.figure('Лабораторная работа №2: Операции свертки и корреляции', figsize=WINDOW_SIZE)
    figure.suptitle('Лабораторная работа №2\nОперации свертки и корреляции')
    
    # Выделяем место под 8 графиков
    axis = figure.subplots(2, 4)

    # Вычисляем значения функций y=cos(2x), z=sin(5x)
    x = np.linspace(0, 2 * np.pi, 100)
    y = func_y(x)
    z = func_z(x)

    # ---------- ORIGINAL SIGNALS ----------
    axis[0, 0].set_title("Исходный график y=cos(2x)")
    axis[0, 0].plot(x, y)
    axis[1, 0].set_title("Исходный график z=sin(5x)")
    axis[1, 0].plot(x, z)

    # ---------- LINEAR CONVOLUTION (MANUAL) ----------
    axis[0, 1].set_title('Линейная свертка (ручная)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    linear_convolution_manual = calc_line_conv(y, z, N)
    axis[0, 1].stem(range(N + N - 1), linear_convolution_manual)

    # ---------- CYCLICAL CONVOLUTION (MANUAL) ----------
    axis[1, 1].set_title('Циклическая свертка (ручная)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    cyclical_convolution_manual = calc_cycl_conv(y, z, N)
    axis[1, 1].stem(range(N), cyclical_convolution_manual)

    # ---------- CONVOLUTION (LIB) ----------
    axis[0, 2].set_title('Cвертка функций (библиотечная)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    lib_convolution = np.convolve(y, z)
    axis[0, 2].stem(range(N + N - 1), lib_convolution)

    # ---------- CONVOLUTION (FFT) ----------
    axis[1, 2].set_title('Cвертка функций (БПФ)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    Y = np.fft.fft(y)
    Z = np.fft.fft(z)
    fft_convolution = np.fft.ifft(Y * Z)
    axis[1, 2].stem(range(N), fft_convolution)

    # ---------- CORRELATION (MANUAL) ----------
    axis[0, 3].set_title('Корреляция функций (ручная)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    correlation_manual = calc_correlation(y, z, N)
    correlation_manual = [x / N for x in correlation_manual]
    axis[0, 3].stem(range(N), correlation_manual)

    # ---------- CORRELATION (LIB) ----------
    axis[1, 3].set_title('Корреляция функций (библиотечная)')
    x = np.linspace(0, 2 * np.pi, N)
    y = func_y(x)
    z = func_z(x)
    correlation_lib = np.correlate(y, z, mode='full')[:N][::-1]
    correlation_lib = [x / N for x in correlation_lib]
    axis[1, 3].stem(range(N), correlation_lib)

    plt.show()


if __name__=="__main__":
    main()