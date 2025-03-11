#include <stdio.h>                                      //подключение библиотек
#include <stdlib.h>
#include "functions.h"

int *memory(int n, int i, int max, int j, int ans)      //функция выделения памяти под массив
{
    int *array;                                         //объявление массива
    array = (int *) malloc(n * sizeof(int));       //выделение памяти
    if (NULL==array)                                    //условие, если память не выделена
    {
        printf("Нет свободной памяти!");         //вывод текста
        free(array);                                    //освобождение массива
        return NULL;                                    //возвращает значение NULL
    }
    func2(i, n, array, max, j, ans);                    //вызов функции ввода элементов массива
    return array;                                       //возвращает массив
}