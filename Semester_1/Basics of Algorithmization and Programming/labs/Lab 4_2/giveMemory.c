#include <stdio.h>                                       //подключение библиотек
#include <stdlib.h>
#include "functions.h"

int** giveMemory(int n)                                  //функция выделения памяти
{
    int **matrix=NULL;                                        //объявление указателя на массив
    if(!(matrix=(int**)malloc(n*sizeof(float*))))         //выделение памяти + проверка на выделение памяти
    {
        printf("Нет свободной памяти!");              //вывод на экран текста
        free(matrix);                                         //освобождение памяти
        return NULL;                                          //возвращает значение NULL
    }
    int i;
    for(i=0; i<n; i++)
    {                                          //цикл для выделения памяти под массив
        *(matrix+i)=(int*)malloc(n*sizeof(float));
        if(NULL==(*(matrix+i)))                                      //проверка на выделение памяти
        {
            printf("Нет свободной памяти!");                //вывод текста на экран
            for (i = 0; i < n; i++) free(matrix[i]);               //цикл для освобождения памяти
            free(matrix);                                          //освобождение памяти
            return NULL;                                           //возвращает значение NULL
        }
    }
    inputMatrixElements(n, matrix);                     //обращение к функции ввода элементов массива
    return matrix;                                       //завершение программы
}