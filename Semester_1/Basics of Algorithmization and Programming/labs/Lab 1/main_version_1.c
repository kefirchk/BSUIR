//Задание 1(№5). Дано натуральное число n. Как наименьшим количеством монет можно выплатить n копеек? Предполагается,
// что в данном количестве имеются монеты в 1,2,5,10,20 и 50 копеек.

#include <stdio.h>  //Подключение библиотек
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8); //Русификация консоли
    int n, i, x, sum; //Объявление переменных
    //n-денежняя сумма, i-счётчик, x-кол-во номиналов, sum-общее кол-во монет, которое нужно взять

    printf("Введите денежнюю сумму n:\n");       //Приглашение
    for (;;)                    //цикл для ввода элементов массива и проверки
    {
        rewind(stdin);                                      //очистка буффера
        int k = scanf("%d",&n);                           //ввод натурального элемента массива
        if (k == 1 && n > 0) break;                              //проверка на правильность ввода
        else printf("Ошибка! Повторите ввод:\n");
    }
    printf("Введите количество номиналов: \n");  //Приглашение
    for (;;)                    //цикл для ввода элементов массива и проверки
    {
        rewind(stdin);                                      //очистка буффера
        int k = scanf("%d",&x);                           //ввод натурального элемента массива
        if (k == 1 && x > 0) break;                              //проверка на правильность ввода
        else printf("Ошибка! Повторите ввод:\n");
    }
    int A[x], B[x], C[x];                                //Объявляние переменных

    //A[x]-массив номиналов, B[x]-массив остатков, C[x]-массив количества монет

    printf("Введите номиналы монет: \n");         //Приглашение
    for (i = 0; i < x; i++)                            //Ввод номиналов монет
    {
        for (;;)                    //цикл для ввода элементов массива и проверки
        {
            rewind(stdin);                                      //очистка буффера
            int k = scanf("%d", &A[i]);                           //ввод натурального элемента массива
            if (k == 1 && A[i] > 0) break;                              //проверка на правильность ввода
            else printf("Ошибка! Повторите ввод:\n");
        }
        if (i > 0) {
            for (int t = 1; t <= i; t++)                      //Проверка на ввод одинаковых номиналов для разных монет
            {
                if (A[i] == A[i - t]) {
                    printf("Ошибка! Вы ввели один и тот же номинал в качестве двух монет.\nПопробуйте ещё раз\n");
                    i--;
                }
            }
        }
    }
    for (i = 0; i < x; i++)                      //Сортировка элементов матрицы(номиналов монет)
    {
        for (int j = 0; j < x - 1; j++)
        {
            if (A[j] < A[j + 1])                //Расстановка элементов матрицы по убыванию
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
    }
    B[0] = n;
    for (i = 0; i < x; i++)
    {
        int j=i-1;                            //Объявление промежуточной переменной
        if(i>0)
        {
            B[i]=B[j]%A[j];
        }
        int q = B[i] % A[i];                  //Вычисление остатка от деления
        C[i] = (B[i] - q)/A[i];               //Вычисление кол-ва монет определённого номинала
        printf("Потребуется %d монет номиналом '%d' коп.\n",C[i],A[i]);    //Вывод искомых значений
    }
    sum=0;
    i=0;
    while (i<x)
    {
        sum += C[i];   //Вычисление необходимого кол-ва монет
        i++;
    }
    int check = 0;     //Объявление промежуточной переменной
    for (i = 0; i < x; i++)
    {
        check = check + (C[i]*A[i]);             //Проверка на то, хватит ли введенных номиналов для выплаты суммы n
    }
    if(check != n)
    {
        printf("Ошибка! Не хватает подходящих номаналов для полного погашения введенной денежной суммы в %d копеек.\n", n);
        return -4;
    }
    printf("Общее количествово монет, необходимое для выплаты установленной денежной суммы = %d\n", sum);   //Вывод общего кол-ва монет
    return 0;      //Завершение программы
}

//----------------------------------------------------------------------------------------------------------------------

//#include <stdio.h>  //подключение библиотек
//#include <windows.h>
//int main()
//{
//    SetConsoleOutputCP(CP_UTF8); //русификация консоли
//    int n, k50, k20, k10, k5, k2, k1, q1, q2, q3, q4, q5, q6, vse; //объявление переменных
//    printf("Введите денежнюю сумму n:\n");
//    if(!scanf("%d", &n) || n < 1)   // or instead scanf("%d", &n);
//    {
//        printf("ERROR\n");          // при вводе символа или числа < 1 выводится текст "ERROR"
//        return -1;
//    }
//    q1 = n % 50;             //нахождение остатка от деления n на 50
//    k50 = (n - q1) / 50;     //нахождение кол-ва монет номиналом "50 копеек".
//    q2 = q1 % 20;            //нахождение остатка от деления q1 на 50
//    k20 = (q1 - q2) / 20;    //нахождение кол-ва монет номиналом "20 копеек".
//    q3 = q2 % 10;            //нахождение остатка от деления q2 на 50
//    k10 = (q2 - q3) / 10;    //нахождение кол-ва монет номиналом "10 копеек".
//    q4 = q3 % 5;             //нахождение остатка от деления q3 на 50
//    k5 = (q3 - q4) / 5;      //нахождение кол-ва монет номиналом "5 копеек".
//    q5 = q4 % 2;             //нахождение остатка от деления q4 на 50
//    k2 = (q4 - q5) / 2;      //нахождение кол-ва монет номиналом "2 копейки".
//    q6 = q5 % 1;             //нахождение остатка от деления q5 на 50
//    k1 = (q5 - q6);          //нахождение кол-ва монет номиналом "1 копейка".
//    vse = k50 + k20 + k10 + k5 + k2 + k1; //нахождение общего кол-ва монет.
//    printf("Потребуется %d, %d, %d, %d, %d, %d монет номиналом '50', '20', '10', '5', '2' и '1' копейка соответственно.\n",
//               k50, k20, k10, k5, k2, k1);
//    printf("Минимально нужно взять %d монет, чтобы выплатить денежнюю сумму в %d копеек.", vse, n);
//    return 0; //функция возвращает значение 0
//}
