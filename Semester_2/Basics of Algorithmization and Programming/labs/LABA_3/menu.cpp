#include "Header.h" //подключение библиотеки

int menu(char **&str, FILE *&f, char* name)  //функция выбора режима работы программы
{
	int size = n1;               //количество строк в тексте
	char c;                      //временная переменная
	memory_for_text(str, size);  //вызов функции выделения памяти
	while (1)
	{
	    puts("\nВыберете режим работы:\n"
		"\n1 - добавить в файл информацию"
		"\n2 - просмотреть файл"
		"\n3 - переписать файл"
		"\n4 - удалить файл"
		"\n5 - получить n наиболее часто встречающихся слов и число их появлений"
		"\n6 - работать с другим файлом"
		"\n7 - выход");
		switch (c = _getch())
		{
		case '1': str = input_text(name, str, f, 1); break;      //вызов функции добавления в файл информации
		case '2': show_file(f, name); continue;                  //вызов функции просмотра файла
		case '3': str = input_text(name, str, f, 3); break;      //вызов фукнции перезаписи файла
		case '4': if (remove(name)) {
			      puts("Нельзя удалить файл");
			      exit(1); }
		          else puts("\nФайл удален"); continue;          //удаление файла
		case '5': size = file_in_str(name, str, f); break;       //вызов функции переписи информации из файла в массив строк
		case '6': name = input_word(1); continue;                //вызов функции ввода названия файла
		case '7': exit(0);                                       //выход из программы
		default: puts("Ошибка выбора операции. Повторите ввод"); continue;
		}
		if (c == '1' || c == '3' || c == '5') realloc_text(str, size); //вызов функции перераспределения памяти для строк в введенном тексте
		break;
	}
	return size;
}




//вычисление длины файла в байтах
//int descriptor = _fileno(f);		// дескриптор файла
//long length = _filelength(descriptor);	// длина файла	
//printf("\nДлина файла = %d\n", length);