#include "Header.h" //подключение библиотеки

int length(FILE *f, char *name) //функция подсчета длины файла
{
	char c;
	puts("Вывести длину файла?(y\\n)");
	switch (c = _getch()) //ввод ДА(y) или НЕТ(n)
	{
	case 'y': break;      //если y
	case 'n': return 0;   //если n
	default: puts("Ошибка! Повторите ввод:");
	}
    errno_t ff = fopen_s(&f, name, "rt");  //открытие файла
	if (ff)
	{
		puts("Файл не может быть открыт");
		return 0;
	}
    //char cc;
    int ds = _fileno(f);		     //дескриптор файла
    long len = _filelength(ds);	     //длина файла
    printf("\nДлина: %d\n", len);
    //fseek(f, 0, 2);                //перемещение УТПФ в конец файла
    //int kk = ftell(f);             //получить позицию УТПФ в файле
    //printf("\nПозиция: %d\n", kk);
    fclose(f);                       //закрыть файл
	return len;                      //вернуть длину файла
}