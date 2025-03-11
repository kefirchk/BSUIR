# Лабораторная работа №3 "Проектирование цифровых фильтров"
# Вариант №6 (Режекторный оконный фильтр. Окно Блэкмана)
# Исходный сигнал: y = sin(x) + cos(4x)

import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import firwin, lfilter, freqz
from scipy import signal
import functions as funs
from functions import N, M, WINDOW_APP_SIZE

########################################## ВЫЧИСЛЕНИЯ ##################################################

# Создание исходной функции
x = np.linspace(0, 2*np.pi, N)
y = funs.y(x)

freqs = np.fft.fftfreq(len(y)) * N

# Создание окна Блэкмана
np_blackman_window = np.blackman(M)
own_blackman_window = funs.get_blackman_window(M)

# Реализация режекторного КИХ-фильтра с окном Блэкмана
numtaps = N
fs = 10          # частота дискретизации
cutoff_freq = 1  # частота пропускания
reject_filter_coeffs = firwin(numtaps, cutoff_freq, fs=fs, window="blackman")

# Применение фильтра к исходной функции
filtered_y = lfilter(reject_filter_coeffs, 1.0, y)

# Получение АЧХ режекторного фильтра
freq_response = (np.fft.fft(reject_filter_coeffs))


# Создание и добавление шума
noise = np.cos(30*x)
noisy_y = y + noise

# Применение фильтра к зашумленной функции
filtered_noisy_y = lfilter(reject_filter_coeffs, 1.0, noisy_y)

######################################## ПОСТРОЕНИЕ ГРАФИКОВ ###########################################

plt.figure('Лабораторная работа №3. Проектирование цифровых фильтров', figsize=WINDOW_APP_SIZE)    

plt.subplot(3, 2, 1)
plt.plot(freqs[:N//2], np.absolute(np.fft.fft(y)[:N//2]))
plt.title('Исходная функция y = sin(x) + cos(4x)')
plt.grid()

plt.subplot(3, 2, 2)
plt.stem(own_blackman_window)
plt.title('Окно Блэкмана')
plt.grid()

plt.subplot(3, 2, 3)
plt.plot(np.abs(freq_response))
plt.title('АЧХ режекторного фильтра')
plt.xlabel('Частота')
plt.ylabel('Амплитуда')
plt.grid()

plt.subplot(3, 2, 4)
plt.plot(freqs[:N//2], np.absolute(np.fft.fft(noise))[:N//2])
plt.title('Шум')
plt.grid()

plt.subplot(3, 2, 5)
plt.plot(freqs[:N//2], np.absolute(np.fft.fft(noisy_y))[:N//2])
plt.title('Исходная функция с шумом')
plt.grid()

plt.subplot(3, 2, 6)
ans = funs.reject_blackman_window_filter(Y=y, M=M, N=N)
plt.plot(freqs[:N//2], np.absolute(np.fft.fft(ans))[:N//2])
plt.title('Исходная функция с шумом после фильтра')
plt.grid()

plt.tight_layout()
plt.show()
