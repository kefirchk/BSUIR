#include "Header.h" //подключение библиотеки

int menu(person *&man, FILE *&f, char* name)  //функция выбора режима работы программы
{
	char c, howOpen; //временные переменные
	int n = 0;       //количество людей
	while (1) {
		puts("Выберете тип файла:"
			 "\n0 - текстовый "
			 "\n1 - бинарный");
		howOpen = _getch();
		if (howOpen == '0' || howOpen == '1') break;
	}
	while (1)
	{
		puts("\nВыберете режим работы:\n"
			"\n1 - добавить в файл информацию"
			"\n2 - просмотреть файл"
			"\n3 - переписать файл"
			"\n4 - удалить файл"
			"\n5 - получить информацию о самых бедных и самых богатых людях"
			"\n6 - работать с другим файлом"
			"\n7 - ввести другой курс валют"
			"\n8 - удалить информацию о человеке"
			"\n9 - выход");
		switch (c = _getch()) {
		case '1': case '3':
		{
			n = input_int(0);             //вызов функции ввода количества людей
			man = memory_struct(man, n);  //вызов функции выделения памяти под массив структур типа person
			man = input_info(n, man);     //вызов функции ввода информации о людях
			if (c == '1') 
				if(howOpen == '0') struct_in_text_file(name, f, man, '1', n); //добавить в файл информацию
				else struct_in_binary_file(name, f, man, '1', n);
			if (c == '3') 
				if(howOpen == '0') struct_in_text_file(name, f, man, '3', n); //переписать файл
				else struct_in_binary_file(name, f, man, '3', n);
			break;
		}
		case '2': show_file(howOpen, f, name, man); continue;    //вызов функции просмотра файла
		case '5': n = file_in_str(man, name, f, howOpen); break; //вызов функции переписи информации из файла в массив строк
		case '4':
		{
			if (remove(name)) { puts("Нельзя удалить файл"); exit(1); } //удаление файла
			else puts("\nФайл удален"); continue;
		}
		case '6': name = input_str(0, man, 2); continue;    //вызов функции ввода названия файла
		case '7': perevod(man, -1); continue;
		case '8': del_person(f, man, name, howOpen);        //вызов функции удаления информации о человеке в файле
			      continue;
		case '9': exit(0);                                  //выход из программы
		default: puts("Ошибка выбора операции. Повторите ввод"); continue;
		}
		break;
	}
	return n;
}



//вычисление длины файла в байтах
//int descriptor = _fileno(f);		// дескриптор файла
//long length = _filelength(descriptor);	// длина файла	
//printf("\nДлина файла = %d\n", length);