#include <stdio.h>                                            //подключение библиотек
#include <stdlib.h>

float** giveMemory(int n, float** matrix)                     //функция выделения памяти
{
	if (!(matrix = (float**)malloc(n * sizeof(float*))))      //выделение памяти + проверка на выделение памяти
	{
		printf("Нет свободной памяти!");                      //вывод на экран текста
		exit(0);                                              //принудительное завершение программы, если память не выделена
	}
	int i;
	for (i = 0; i < n; i++)                                   //цикл для выделения памяти под массив
	{                                               
		*(matrix + i) = (float*)malloc(n * n * sizeof(float));
		if (NULL == (*(matrix + i)))                          //проверка на выделение памяти
		{
			printf("Нет свободной памяти!");                  //вывод текста на экран
			exit(0);                                          //возвращает значение NULL
		}
	}
	return matrix;                                            //возвращает значение
}