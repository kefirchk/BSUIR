import numpy as np

PERIOD = 2 * np.pi
WINDOW_APP_SIZE = (12, 7.5)

N = 100  # кол-во отсчетов
M = 32    # кол-во точек окна

def y(x):
    return (np.sin(x) + np.cos(4*x))


def get_blackman_window(M):
    window = np.zeros(M)
    for n in range(M):
        window[n] = 0.42 - 0.5 * np.cos(2 * np.pi * n / (M-1)) + 0.08 * np.cos(4 * np.pi * n / (M-1))
    return window


def coagulate(y, h, M):
    result = np.array(y).copy()
    for i in range(M, np.size(y) // 2 + 1):
        result[i] = 0
        for j in range(M):
            result[i] = result[i] + y[i - j] * h[j]
            result[np.size(y) - i] = result[i]
    return result


def reject_blackman_window_filter(Y, M, N):
    Fp = 0.5 # частота пропускания
    fft_Y = np.fft.fft(Y)
    filter_arguments = []
    for i in range(N):
        temp = i - M / 2
        filter_arguments.append(1 - 2 * Fp * np.cos(PERIOD * temp * i / N) + Fp)
        filter_arguments[i] = filter_arguments[i]
    
    filter_arguments = filter_arguments * get_blackman_window(N)
    
    result_filter_arguments = [element / np.sum(filter_arguments) for element in filter_arguments]     #нормирование коэф.

    for i in range(N):
        result_filter_arguments[i] = -result_filter_arguments[i]

    result_filter_arguments[int(N / 2)] += 1
    coagulation = coagulate(fft_Y, result_filter_arguments, int(M))

    return np.fft.ifft(coagulation)