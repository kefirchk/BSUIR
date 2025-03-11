#include "Header.h" //подключение библиотеки

person* input_n_and_mem(int &n, person* man) //функция ввода количества людей и выделения памяти под массив структур
{
	int i, f = 0; char symbol; //промежуточные переменные для проверки и ввода
	while (1)
	{
		do
		{
			if (f++) puts("Ошибка!");
			rewind(stdin);                                //чистка буфера
			printf("Введите количество людей: ");
			i = scanf_s("%d%c", &n, &symbol);             //ввод значения
		} while (n < 0 || !i || i < 1 || symbol != '\n'); //проверка количества людей и правильность ввода

		//выделение памяти под массив структур
		man = (person*)calloc(n, sizeof(person));
		if (man == NULL)
		{
			puts("Ошибка! Память не выделена\n");
			exit(1);
		}
		else break;
	}
	return man;
}