#include "Header.h" //подключение библиотеки

int del_person(FILE *&f, person *&man, char* nameFile, char fileOpen)  //функция удаления человека из файла
{
	char *str, name[n2] = {}, surname[n2] = {}; //временные массивы символов для записи искомого человека в файле
	puts("Введите имя человека:");
	str = input_str(-1, man, 2); //вызов функции ввода имени
	strcpy_s(name, n2, str);     //копирование введенной информации в name
	puts("\nВведите фамилию человека:");
	str = input_str(-1, man, 2); //вызов функции ввода фамилии
	strcpy_s(surname, n2, str);  //копирование введенной информации в surname
	int n = file_in_str(man, nameFile, f, fileOpen); //вызов функции записи информации из файла в структуры
	if (n)
	{
		int flag = 0; //флажок, который значит, что мы нашли искомого человека для удаления при значении 1
		for (int i = 0; i < n; i++)
		{
			if (!strcmp(name, man[i].name) && !strcmp(surname, man[i].surname)) //сравнение имен и фамилий
			{
				for (int j = i+1; j < n; j++) //цикл по переписи массива структур
				{
					*(man + j - 1) = *(man + j);
				}
				n--;      //уменьшаем количество людей в файле
				flag = 1; //нашелся удаляемый человек 
				break;    //прервать цикл
			}
		}
		if (flag)         //если мы нашли человека
		{
			char fileCopyName[n2] = "file_copy"; //временное имя нового файла
			if (fileOpen == '0') struct_in_text_file(fileCopyName, f, man, '3', n);
			else struct_in_binary_file(fileCopyName, f, man, '3', n);
			free(man);                           //освободить память от массива структур типа person
			if (remove(nameFile)) { puts("Ошибка удаления старого файла"); exit(1); } //удаление старого файла
			if (rename(fileCopyName, nameFile)) 
			{ puts("Ошибка переименования файла"); exit(1); } //переименование нового файла
			puts("Информация удалена");
		}
		else puts("Такого человека в файле не найдено");
	} 
	else puts("Файл пуст");
	return 0;
}