#include "Header.h" //подключение библиотеки

void show_file(char choice, FILE *f, char* name, person* man) //функция просмотра файла
{
	char c;         //временная переменная
	int size = 0;   //число, на которое выделять память для структур
	errno_t ff;
	if (choice == '1') ff = fopen_s(&f, name, "rb"); //открытие бинарного файла для чтения
	else ff = fopen_s(&f, name, "rt");   //открытие текствого файла для чтения
	if (ff) { puts("\nФайл не может быть открыт"); return; }
	while (1)       //цикл по подсчету записанных стркутур в файле
	{
		fscanf_s(f, "%c", &c); //считывание очередного символа в файле
		if (feof(f)) break; //если конец файла
		if(c == '\n') size++;
	}
	rewind(f);      //сбрасываем УТПФ
	if (size) 
	{
		man = memory_struct(man, size); //выделение памяти под структуры
		int k = 0;
		//рисовка верхней границы таблицы
		printf(" ");
		while (k++ < 110) printf("_");
		//вывод "шапки"
		printf("\n|Имя\t\t     ");
		printf("Фамилия   ");
		printf("          Возраст");
		printf("   Доллары");
		printf("        Евро");
		printf("           Рос. рубли");
		printf("     Бел. рубли     |\n");
		//подрисовка верхней границы таблицы
		printf("|");
		while (k-- > 1) printf("_");
		printf("|");
		for (int i = 0; i < size; i++)
		{
			if (choice == '1')
			{
				fread(man + i, sizeof(person), 1, f); //читаем сразу всю структуру
				fscanf_s(f, "\n");
			}
			printf("\n|%-20s", man[i].name);     //выводим имя
			printf("%-20s", man[i].surname);     //выводим фамилию
			printf("%-10d%-15.2lf%-15.2lf%-15.2lf%-15.2lf|", man[i].age, man[i].money[0].dollar, man[i].money[1].euro, man[i].money[2].RUB, man[i].money[3].BYN);
		}
		//рисовка нижней границы таблицы
		printf("\n|");
		while (k++ < 110) printf("_");
		puts("|");
		free(man);
	}
	else puts("Файл пуст");
	fclose(f);      //закрытие файла
}



//else
//			{
//			fread(man[i].name, n2, 1, f);    //читаем имя
//			fread(man[i].surname, n2, 1, f); //читаем фамилию
//			fscanf_s(f, "%d%lf%lf%lf%lf\n", &man[i].age, &man[i].money[0].dollar, &man[i].money[1].euro, &man[i].money[2].RUB, &man[i].money[3].BYN);
//			}