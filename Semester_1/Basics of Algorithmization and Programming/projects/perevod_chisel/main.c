#include <stdio.h>
#include <windows.h>

int main()
{
    int k1=10, k2=11, t, z, i, ss;
    char znak ='+'; //для знака результата
    double num; //число в десятичной системе счисления
    char ms[20];//массив(обнуляется при описании)
    SetConsoleOutputCP(CP_UTF8);
    printf("\nВведите исходное число (между целой и др. частью - ,):");
    scanf("%lf", &num);
    num<0 ? znak='-', num*=-1 : num;//получение знака числа
    printf("\nВведите основание новой с/с:");
    scanf("%d", &ss);
    printf("\nВведите точность для дробной части числа: ");
    scanf("%d",&t);
    z = num;//выделение целой части числа
    num -=z;//выделение дробной части числа
    while(z>=ss)//перевод целой части числа
    {
        i=z%ss;//получаем остаток от деления на основание
        z/=ss;//выделяем целую часть от деления
        ms[k1--]=i>9 ? i - 10 + 'A': i +'0';//формирование символа цифры
    }
    ms[k1--]=z>9 ? z-10+'A': z + '0';
    ms[k1]=znak;
    ms[k2++]='.';//выставление десятичной точки
    while(num !=0 && k2 -11 <= t)//перевод дробной части числа
    {
        num*=ss;
        i=num;// в i записывается целая часть от dr
        ms[k2++]=i>9? i-10 + 'A': i + '0';//i заносится в массив
        num-=i;//отбрасываем целую часть
    }
    printf("\nВаше число : ");
    for(i=k1;i<k2;i++)
        printf("%c",ms[i]);//вывод числа на экран
    return 0;//функция возвращает значение 0(завершение программы)
}