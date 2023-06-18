#include <stdio.h>
#include "windows.h"
int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int n; //сумма сдачи
    int k; // кол-во номиналов
    printf("Введите кол-во номиналов: \n");
    scanf("%d", &k);
    int count = 0;
    int arr[2][k];//номинал и количство монет
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < k; j++)
        {
            arr[i][j] = 0;
        }
    }
    printf("Введите номиналы: \n");
    for (int i=0; i<k; i++)
    {
        scanf("%d",&arr[0][i]);
        arr[1][i]=0;
    }
    printf("Введите сумму сдачи\n");
    scanf("%d",&n);
    for(int i=k-1;i>=0;i--)
    {
        arr[1][i]=n/arr[0][i];//вычисление количества монет i-го номинала
        n=n-arr[1][i]*arr[0][i];//вычисление остатка сдачи
        count=count+arr[1][i];//вычисление общего кол-ва монет
        if (n==0) break;
    }
    printf("Вывод резульатов: \n");
    for (int i=0; i<2; i++)
    {
        printf("\n");
        for (int j=0; j<k; j++)
            printf("%4d",arr[i][j]);
    }
    printf("\n");
    printf("Общее количество монет: %d \n",count);
}


