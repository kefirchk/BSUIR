#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
    int i, m, n, min;
    SetConsoleOutputCP(CP_UTF8);
    printf("Введите m и n: ");
    scanf("%d%d",&m,&n);
    if(m<n)min=m;
    else min=n;
    for (i=2;i<=min/2;i++)
    {
        if (m % i == 0 && n % i == 0) {
            printf("\n Числа %d и %d не взаимно простые.", n, m);
            printf("Общий делитель: %d.\n", i);
            return 0;
        }
    }
    if(m % min == 0 && n% min == 0)
    {
        printf("\n Числа %d и %d не взаимно простые. ", n, m);
        printf("Общий делитель: %d.\n",i);
    }
    else
        printf("\n Числа %d и %d - взаимно простые.", n, m);
    return 0;
}