#include "Header.h" //подключение библиотеки

void show_file(FILE *f, char* name) //функция просмотра файла
{
	char c;         //временная переменная
	errno_t ff;
	ff = fopen_s(&f, name, "rt");   //открытие файла для чтения
	if (ff) { puts("Файл не может быть открыт"); return; }
	printf("\n");   //перевод на нову строку
	while (1)
	{
		fscanf_s(f, "%c", &c); //считывание очередного символа в файле
		if (feof(f)) { fclose(f); return; } //если конец файла
		printf("%c", c);       //вывод символа на экран
	}
	fclose(f);      //закрытие файла
}