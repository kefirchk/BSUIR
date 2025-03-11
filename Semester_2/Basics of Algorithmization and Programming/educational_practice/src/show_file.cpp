#include "Header.h" //подключение библиотеки
#include <io.h>

void show_file(FILE *f, char* name, info* head, info* tail) //функция просмотра файла
{
	errno_t ff = fopen_s(&f, name, "r+t");   //открытие текствого файла для чтения
	if (ff)                                  //ошибка открытия файла
	{
		printf("%c[%d;%dm\nФайл не может быть открыт!%c[%dm\n", 27, 1, 31, 27, 0); 
		return; 
	}
	int length = _filelength(_fileno(f)), size = length / sizeof(info);   //длина файла и количество структур соответственно 
	rewind(f);                               //сбрасываем УТПФ
	if (size)
	{
		int k = 0;                           //счетчик
		printf(" ");
		while (k++ < 86) printf("_");        //рисовка верхней границы таблицы
		printf("\n|Имя\t\t|Фамилия        |ПИН-код   |Доллары   |Евро      |Рос. рубли|Бел. рубли|\n|"); //вывод "шапки"
		k = 81;
		while (k-- > 1)                      //подрисовка верхней границы таблицы
		{
			if (k == 10 || k == 20 || k == 30 || k == 40 || k == 50 || k == 65) printf("|");
			printf("_");
		}
		info* pointer = NULL;                //указатель на структуру
		for (;!feof(f);)
		{
			if (!(pointer = (info*)calloc(1, sizeof(info)))) //выделение памяти под структуру
			{
				printf("%c[%d;%dm\nПамять не выделена!%c[%dm\n", 27, 1, 31, 27, 0);
				exit(1);
			}
			fgets(pointer->name, len+1, f);  //считывание имени
			fgets(pointer->surname, len+1, f); //считывание фамилии
			fscanf_s(f, "%d%d%d%d%d\n", &pointer->PIN, &pointer->cash[0].dollar,  //считывание числовых данных 
				&pointer->cash[1].euro, &pointer->cash[2].RUB, &pointer->cash[3].BYN);
			printf("|\n|%-15s|%-15s|%-10d|%-10d|%-10d|%-10d|%-10d",               //вывод считанной информации
				pointer->name, pointer->surname, pointer->PIN, pointer->cash[0].dollar, 
				pointer->cash[1].euro, pointer->cash[2].RUB, pointer->cash[3].BYN);
			free(pointer);
		}
		printf("|\n|");
		while (k++ < 80) 		             //рисовка нижней границы таблицы
		{
			if (k == 16 || k == 31 || k == 41 || k == 51 || k == 61 || k == 71) printf("|");
			printf("_");
		}
		puts("|");
	}
	else puts("Файл пуст");
	fclose(f);                               //закрытие файла
}