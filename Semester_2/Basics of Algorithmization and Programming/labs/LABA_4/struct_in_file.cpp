#include "Header.h"   //подключение библиотеки

int checkFileOpen(errno_t ff); //функция проверки файла на открытие

void struct_in_binary_file(char* name, FILE *f, person* man, char choice, int n) //функция записи структуры в бинарный файл
{
	errno_t ff;
	if (choice == '3') ff = fopen_s(&f, name, "w+b"); //открытие файла для записи информации
	if (choice == '1') ff = fopen_s(&f, name, "a+b"); //открытие файла для дозаписи новой информации в файл
	if (!checkFileOpen(ff)) return;                  //проверка на открытие файла
	for (int i = 0; i < n; i++)                      //цикл по записыванию информации в файл
	{
		fwrite(man + i, sizeof(person), 1, f);       //запись очередной структуры в файл
		fprintf(f, "\n");
	}
	fclose(f);
}

void struct_in_text_file(char* name, FILE *f, person* man, char choice, int n) //фукнция записи структуры в текстовый файл
{
	errno_t ff;
	if (choice == '3') ff = fopen_s(&f, name, "w+t"); //открытие файла для записи информации
	if (choice == '1') ff = fopen_s(&f, name, "a+t"); //открытие файла для дозаписи новой информации в файл
	if (!checkFileOpen(ff)) return;                  //проверка на открытие файла
	for (int i = 0; i < n; i++)                      //цикл по записыванию информации в файл
	{
		fwrite(man[i].name, n2, 1, f);    //запись в файл имени
		fwrite(man[i].surname, n2, 1, f); //запись в файл фамилии
		fprintf(f, "%-10d%-15.2lf%-15.2lf%-15.2lf%-15.2lf\n", //запись возраста и валют в файл
			man[i].age, man[i].money[0].dollar, man[i].money[1].euro, man[i].money[2].RUB, man[i].money[3].BYN);
	}
	fclose(f);
}

int checkFileOpen(errno_t ff) //функция проверки файла на открытие
{
	if (ff)
	{
		puts("Файл не может быть открыт");
		return 0;
	}
	return 1;
}