#include "Header.h" //подключение библиотеки

pupil* input_n_and_mem(int &n, pupil *info) //функция ввода количества учеников и выделения памяти под массив структур
{
	int i; char c;
	while (1)
	{
		do {
			rewind(stdin);            //чистка буфера
			printf("Введите количество учеников: ");
			i = scanf_s("%d%c", &n, &c);    //ввод значения
		} while (i<2 || i < 1 || c!='\n');          //ввод количества учеников и проверка на правильность ввода

		//выделение памяти под массив структур
		info = (pupil*)calloc(n, sizeof(pupil));
		if (info == NULL)
		{
			puts("Ошибка! Память не выделена\n");
			exit(1);
		}
		else break;
	}
	return info;
}