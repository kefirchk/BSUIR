import numpy as np
import matplotlib.pyplot as plt


def dwt53(y, level):
    if len(y) == 1:
        return y

    L = y[0::2] # L=c
    H = y[1::2] # H=d
    l = len(L)

    # Через формулы:
    # a = H[0:l-1] - (0.5*(L[0:l-1]+L[1:l]))        # np.floor(0.5*(L[0:l-1]+L[1:l])) 
    # b = H[l-1] - L[l-1] 
    # H = np.concatenate((a, b), axis=None)   

    # a = L[0] + (0.5*H[0] + 0.5)                   # np.floor(0.5*H[0] + 0.5)
    # b = L[1:l] + (0.25*(H[1:l] + H[0:l-1]) + 0.5) # np.floor(0.25*(H[1:l] + H[0:l-1]) + 0.5)
    # L = np.concatenate((a, b), axis=None)

    for i in range(len(H)):
        H[i] -= L[i] / 2
        if i < len(H) - 1:
            H[i] -= L[i + 1] / 2

    for i in range(len(L)):
        L[i] += H[i] / 4
        if i != 0:
            L[i] += H[i - 1] / 4 

    L = dwt53(L, level)
    
    wavelet_coeffs = np.concatenate((L, H))
    print('\nКол-во: '+ str(len(L + H)))
    print(f'L-коэффициент: {L[0]}')#wavelet_coeffs[0]}')
    print(f'H-коэффициенты: {H}')#{wavelet_coeffs[1:]}')

    return wavelet_coeffs


def idwt53(wavelet_coeffs, level):
    count = pow(2, level)
    if count == 2 * len(wavelet_coeffs):
        return wavelet_coeffs
    
    L = wavelet_coeffs[0:count // 2]
    H = wavelet_coeffs[count // 2:count]

    l = len(L)

    # a = L[0] - (0.5*H[0] + 0.5)                   # np.floor(0.5*H[0] + 0.5)
    # b = L[1:l] - (0.25*(H[1:l] + H[0:l-1]) + 0.5) # np.floor(0.25*(H[1:l] + H[0:l-1]) + 0.5)
    # L = np.concatenate((a, b), axis=None)

    # a = H[0:l-1] + (0.5*(L[0:l-1]+L[1:l]))        # np.floor(0.5*(L[0:l-1]+L[1:l]))
    # b = H[l-1] + L[l-1] 
    # H = np.concatenate((a, b), axis=None)

    for i in range(len(L)):
        L[i] -= H[i] / 4
        if i != 0:
            L[i] -= H[i - 1] / 4

    for i in range(len(H)):
        H[i] += L[i] / 2
        if i < len(H) - 1:
            H[i] += L[i + 1] / 2
     
    #y = np.column_stack((L, H)).ravel()
    y = np.zeros(count, dtype=wavelet_coeffs.dtype)
    y[::2] = L
    y[1::2] = H

    wavelet_coeffs[:count] = y
    
    level += 1

    return idwt53(wavelet_coeffs, level)


# low_pass_filter = [-1/8, 2/8, 6/8, 2/8, -1/8]
# high_pass_filter = [-1/2, 1, -1/2]

# Подготовка исходного сигнала
N = 64
x = np.linspace(0, 2*np.pi, N)
y = np.sin(x) + np.cos(4 * x)
print(f"Исходный сигнал:\n{y}")

wavelet_coeffs = dwt53(y, 3)
y2 = idwt53(wavelet_coeffs, 1)
print(f"\nВостановленный сигнал:\n{y2}")
