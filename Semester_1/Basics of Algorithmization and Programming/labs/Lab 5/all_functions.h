#include <windows.h>                                   //подключение библиотек
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>

void del_dynamic(float** matrix, int* array);
void output(int* result);
int* input_size(char choice, int* array);              //функция ввода порядка матрицы
float** memory_for_matrix(int* array, float** matrix); //функция выделения памяти под массив
float** input_matrix(int* array, float **matrix);      //функция ввода элементов массива
float* algo_with_output(int* array, float **matrix, float* result);     //функция основного алгоритма для решения задачи с выводом результата на экран
void additional_offer(char choice);                    //функция выбора, которая решает продолжить ли выполнение программы         