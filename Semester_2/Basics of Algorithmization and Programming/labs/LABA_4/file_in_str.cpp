#include "Header.h"   //подключение библиотеки

int file_in_str(person* &man, char* name, FILE *f, char fileOpen) //функция переписи информации из файла в массив строк
{
	errno_t ff;
	if(fileOpen == '0') ff = fopen_s(&f, name, "rt"); //открытие файла для чтения
	else ff = fopen_s(&f, name, "rb");
	if (!checkFileOpen(ff)) return 0;                   //проверка на открытие файла
	int size = 0;                //количество строк в файле
	int len = _filelength(_fileno(f));
	size = len / sizeof(person);
	if (size)
	{
		man = memory_struct(man, size); //выделение памяти под структуры
		if (fileOpen == '1')
			binary_file_in_str(size, f, man); //вызов функции переписи информации из бинарного файла в структур
		else
			text_file_in_str(size, f, man); //вызов функции переписи информации из текстового файла в структуры
	}
	else puts("Файл пуст");
	fclose(f);    //закрыть файл
	return size;  //вернуть размер массива структур
}

void binary_file_in_str(int size, FILE *f, person *&man) //функция переписи информации из бинарного файла в структуры
{
	for (int i = 0; i < size; i++)
	{
		fread(man + i, sizeof(person), 1, f); //читаем очередную структуру
		fscanf_s(f, "\n");
	}
}

void text_file_in_str(int size, FILE *f, person *&man) //функция переписи информации из текстового файла в структуры
{
	for (int i = 0; i < size; i++)
	{
		fread(man[i].name, n2, 1, f);    //читаем имя
		fread(man[i].surname, n2, 1, f); //читаем фамилию
		fscanf_s(f, "%d%lf%lf%lf%lf\n",  //читаем возсраст и валюты из файла
			&man[i].age, &man[i].money[0].dollar, &man[i].money[1].euro, &man[i].money[2].RUB, &man[i].money[3].BYN);
	}
}