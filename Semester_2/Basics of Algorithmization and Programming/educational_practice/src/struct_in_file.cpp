#include "Header.h"                        //подключение библиотеки

void struct_in_file(char* name, FILE *&f, info* pointer) //фукнция записи структуры в текстовый файл
{
	errno_t ff = fopen_s(&f, name, "a+t"); //открытие файла для записи информации
	if (ff)                                //проверка на открытие файла
	{
		printf("%c[%d;%dm\nФайл не может быть открыт!%c[%dm\n", 27, 1, 31, 27, 0);
		return;
	}
	while (pointer)                        //цикл по записыванию информации в файл
	{
		fprintf(f, "%-15s%-15s", pointer->name, pointer->surname); //запись имени и фамилии
		fprintf(f, "%-10d%-10d%-10d%-10d%-10d\n", //запись числовой информации в файл
			pointer->PIN, pointer->cash[0].dollar, 
			pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
		pointer = pointer->next;           //переход к следующей структуре очереди
	}
	fclose(f);                             //закрытие файла
}