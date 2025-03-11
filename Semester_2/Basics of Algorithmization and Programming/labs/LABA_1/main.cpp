#include "Header.h"            //подключение библиотеки

//Лабораторная работа №1 "Структуры"

/*3. Сведения об ученике состоят из его имени, фамилии и
названия класса(год обучения и буква), в котором он учится:
а) выяснить, имеются ли в школе однофамильцы;
б) выяснить, имеются ли однофамильцы в каких-либо параллельных классах.*/

#include <cstdio>

int main()
{
	SetConsoleCP(1251);        //русификация консоли
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	int n1, n2, size1, size2;                //n - количество учеников, size1, size2 - размеры массивов ms1 и ms2
	pupil *info1 = NULL;                     //указатель на массив структур всех учеников
	pcopy *info2 = NULL;                     //указатель на массив структур одноклассников
	int *ms1 = NULL, *ms2 = NULL;            //указатели на массивы индексов (однофамильцы и однофамильцы в параллельных классах соответственно)
	do {
		info1 = input_n_and_mem(n1, info1);      //вызов функции ввода количества учеников и выделения памяти под массив структур
		give_memory(n1, info1, info2, ms1, ms2); //вызов функции выделения памяти на указатели на строки для имен и фамилий
		info1 = input_info(n1, info1);           //вызов функции ввода информации о учениках
		output_table(n1, info1);                 //вызов функции вывода введенной информации о учениках
		size1 = exercise_a(n1, info1, ms1);      //вызов функции поиска однофамильцев 
		realloc_ms1(ms1, size1);                 //обращение к функции перераспределения памяти для массива индексов
		hat_for_ex1(info1, size1, ms1);          //вызов функции вывода результата поиска однофамильцев
		size2 = exercise_b(info1, size1, ms1, ms2);//вызов функции поиска однофамильцев в параллельных классах и вывода результата на экран
		realloc_ms2(ms2, size2);                 //вызов функции перераспределения памяти для массива однофамильцев в параллельных классах
		hat_for_ex2(info1, size2, ms2);          //обращение к функции вывода результата поиска однофамильцев по параллельным классам
		n2 = poisk(n1, info2, info1);            //вызов функции поиска одноклассников
		output_poisk(n2, info2);                 //вызов функции вывода результата функции поиска одноклассников
		//изменял под работу с файлом... не изменил)
		FILE *f = NULL;
		errno_t ff = fopen_s(&f, "data", "wb+"); //открытие файла для записи информации
		if (ff)
		{
			puts("Файл не может быть открыт");
			return 0;
		}
		for (int i = 0; i < n1; i++)
		{
			fwrite(info1[i].imya, len*sizeof(char), 1, f);
			fwrite(info1[i].familia, len * sizeof(char), 1, f);
			fprintf(f, "%d", info1[i].clas);
			fwrite(&info1[i].letter, sizeof(char), 1, f);
			fprintf(f, "\n");
		}
		fclose(f);         //закрыть файл
		free(info1);
		
		fopen_s(&f, "data", "rb+");
		//info1 = (pupil*)calloc(n1, sizeof(pupil));

		//fread(info1, sizeof(pupil), n1, f);
		for (int i = 0; i < n1; i++)
		{
			int j = 0;
			fscanf_s(f, "%d", j);
			if (feof(f)) break;
			j = 0;
			//fgets(info1[i].imya, len, f);
			fread(info1[i].imya, len, 1, f);
			if (feof(f)) break;
			//while (info1[i].imya[j++] != '\0') fscanf_s(f, "%c", &info1[i].imya[j]);
			printf("%-20s", info1[i].imya);
			//while (info1[i].imya[j++] != '\0') fscanf_s(f, "%c", &info1[i].familia);
			//fgets(info1[i].familia, 2*len, f);
			fread(info1[i].familia, len, 1, f);
			printf("%-20s", info1[i].familia);
			fscanf_s(f, "%d", &info1[i].clas);
			printf("%d\n", info1[i].clas);
			fscanf_s(f, "%c", &info1[i].letter);
			printf("%c\n", info1[i].letter);
			if (feof(f)) break;
		}
		fclose(f);         //закрыть файл
		free_memory(info1, info2, ms1, ms2);//освобождение памяти от указателя на массив структур и от указателей на строки
	} while (offer());                           //цикл на продолжение выполнения программы
	return 0;
}