#include "all_functions.h"

void del_dynamic(float** matrix, int* array) 
{
	for (int i = 0; i < array[0]; i++) free(matrix[i]);//чистка памяти от указателей под строку
	free(matrix);                                      //освобождение памяти от указателя на массив указателей  
	free(array);                                       //освобождение памяти от массива значений размеров матрицы
}