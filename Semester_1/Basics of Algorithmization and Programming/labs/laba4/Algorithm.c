#include <stdio.h>                                             //подключение библиотек
#include "functions.h"

void algo(int n, int** matrix)                                //функция алгоритма решения задачи
{
    int flag=0;                                                //объявление переменных
    float sumDio=0;
    float sumDown=0;
    float sumUp=0;
    for(int i=0; i<n; i++)                                   //цикл по поиску строк, начинающихся с отрицательных чисел
    {
        if(matrix[i][0]<0)                                   //проход по строкам
        {
            if(i>0)
                for(int k=1; k<=i;k++)
                    sumDown = sumDown + matrix[i][i-k];     //вычисление суммы элементов ниже главное диогонали
            for(int k=1; k<n-i; k++)
                sumUp = sumUp + matrix[i][i+k];             //вычисление суммы элементов выше главное диогонали
            sumDio = sumDio +  matrix[i][i];                //вычисление суммы элементов главной диогонали
        }
        if(matrix[i][0]>=0) flag++;
    }
    if(flag==n)
    {
        printf("\nСтрок, начинающихся с отрицательного элемента, нет.\n");    //вывод текста, если выполняется условие
        return;                                                                      //завершение программы
    }
    if(flag != n) outputOfResult(sumDio, sumDown, sumUp);                            //продолжение программы при выполнении условия
}

