#include "Header.h"   //подключение библиотеки
#include <io.h>

int file_in_str(info* &tail, info* &head, char* name, FILE *f) //функция переписи информации из файла в очередь
{
	errno_t ff = fopen_s(&f, name, "r+t"); //открытие файла для чтения
	if (ff)                                //проверка на открытие файла
	{
		printf("%c[%d;%dmФайл не может быть открыт!%c[%dm\n", 27, 1, 31, 27, 0);
		return 0;
	}
	int size = 0, length = _filelength(_fileno(f));   //количество строк в файле и длина файла 
	size = length / sizeof(info);                     //вычисление колтичества структур в файле
	if (size)                                         //файл не пустой
	{
		for (int i = 0; i < size && !feof(f); i++)    //цикл по переписи информации из файла
		{
			info* pointer = (info*)calloc(1, sizeof(info)); //выделение памяти
			if (!pointer)                                   //если память не выделена
			{
				printf("%c[%d;%dmПамять не выделена!%c[%dm\n\n", 27, 1, 31, 27, 0);
				exit(1);
			}
			char c = 0;                               //временная переменная для хранения символа
			for (int i = 0; i < len; i++)             //цикл по переписи имени
			{
				fscanf_s(f, "%c", &c);                //считывание символа
				if (c != ' ' && c != '\0')            //запись символа в строку
					pointer->name[i] = c;
			}
			for (int i = 0; i < len; i++)             //цикл по переписи фамилии
			{
				fscanf_s(f, "%c", &c);                //считывание символа
				if (c != ' ' && c != '\0')            //запись символа в строку
					pointer->surname[i] = c;
			}
			fscanf_s(f, "%d%d%d%d%d\n",               //читаем из файла остальную информацию
				&pointer->PIN, &pointer->cash[0].dollar, 
				&pointer->cash[1].euro, &pointer->cash[2].RUB, &pointer->cash[3].BYN);
			if (!tail || !head) tail = head = pointer;//если очередь не создана
			else
			{
				pointer->next = tail;                 //добавление элемента в очередь 
				tail = pointer;                       //корректировка хвоста
			}
		}
	}
	else puts("Файл пуст");
	fclose(f);                                        //закрытие файла
	return size;                                      //вернуть количество структур
}