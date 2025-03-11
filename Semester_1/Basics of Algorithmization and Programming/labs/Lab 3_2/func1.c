#include <stdio.h>                                  //подключение библиотек
#include "functions.h"


int func1(int n, int i, int max, int j, int ans)    //функция ввода размера массива
{
    printf("Введите размер массива: \n");    //приглашение на ввод размера массива
    for(;;)
    {
        rewind(stdin);                         //чистка буфера
        int k = scanf("%d",&n);              //ввод размера массива
        if (k == 1 || k>1) break;                   //проверка на правильность ввода
        else printf("Ошибка! Попробуйте ещё раз:\n");
    }
    memory(n, i, max, j, ans);                      //вызов функции выделения памяти под массив
    return n;                                       //возвращает значение n
}

