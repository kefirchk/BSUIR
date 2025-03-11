#include <stdio.h>                            //подключение библиотек
#include <windows.h>

void additional_offer(char choice)            //функция для решения об продолжении выполнения программы 
{
	char symbol;
	printf("\nХотите продолжить?(y\\n)");     //приглашение на ввод
	for (;;) {                                
		rewind(stdin);                        //чистка буфера
		scanf_s("%c", &choice);               //ввод y или n(выбор для продолжения или нет)
		scanf_s("%c", &symbol);               //ввод переменной symbol для совершения проверки 
		if (symbol == '\n' && (choice == 'y' || choice == 'n'))   //условие выхода из цикла
		{
			system("cls");                    //очистка экрана
			break;                            //выход из цикла
		}
		else {
			printf("Ошибка!\n");              //текст об ошибке
			printf("Хотите продолжить?(y\\n)");
		}
	}
	if (choice == 'n') exit(0);               //условие выхода из цикла
}