#include "Header.h" //подключение библиотеки

int input_int(int choice)       //функция ввода количества людей или количества валют человека
{
	int k, n, f = 0; char symbol; //промежуточные переменные для проверки и ввода
	do
	{
		if (f++) puts("Ошибка!");
		rewind(stdin);                              //чистка буфера
		if (!choice) printf("Введите количество людей: ");
		k = scanf_s("%d%c", &n, &symbol);           //ввод значения
		if (choice == 0 && k && n > 0 && symbol == '\n') break;
		if (choice == 1 && k && n >= 0 && n <= 4 && symbol == '\n') break;
		if (choice == 2 && k && n < 120 && n > 0 && symbol == '\n') break;
	} while (1);                //ввод количества людей и проверка на корректность ввода
	return n;                   //вернуть количество людей или количество валют
}