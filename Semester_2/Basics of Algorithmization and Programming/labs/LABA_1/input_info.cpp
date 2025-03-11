#include "Header.h" //подключение библиотеки

pupil* input_info(int n, pupil* info1) //функция ввода информации о учениках
{
	int с;                            //временная переменная
	for (int i = 0; i < n; i++)       //цикл по структурам
	{
		rewind(stdin);                //чистка буфера

		//имя
		printf("\nВведите имя ученика: ");
		info1 = input(i, info1, 1);     //вызов функции ввода имени

		//фамилия
		printf("\nВведите фамилию ученика: ");
		info1 = input(i, info1, 0);     //вызов функции ввода фамилии

		//класс
		do {
			rewind(stdin);            //чистка буфера
			printf("\nВведите класс учащегося(<12): ");
			с = scanf_s("%d%c", &info1[i].clas, &info1[i].letter);  //ввод данных
		} while (с<2 || info1[i].clas > 11 || info1[i].clas < 1);    //ввод цифры и буквы класса
	}
	return info1;
}