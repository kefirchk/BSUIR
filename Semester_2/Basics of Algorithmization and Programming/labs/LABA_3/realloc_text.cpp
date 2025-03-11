#include "Header.h" //подключение библиотеки

char **realloc_text(char **&str, int size) //функция перераспределения памяти под строки
{
	int lenght; //размер строк
	for (int i = 0; i < size; i++)
	{
		lenght = strlen(str[i]); //вычисление размера очередной строки
		str[i] = (char*)realloc(str[i], (lenght + 1)*sizeof(char)); //перераспределение памяти под хранение строк
		if (!str[i])   //если не удалось перераспределить память
		{
			while (--i >= 0) free(str[i]); //освобождение памяти от строк, под которые выделена память
			free(str); //освобождение памяти от указателя на указатели на строки
			puts("Segmentation error!\n");
			return 0;
		}
		str[i][lenght] = '\0';
	}
	return str;        //вернуть указатель на указатели на строки
}