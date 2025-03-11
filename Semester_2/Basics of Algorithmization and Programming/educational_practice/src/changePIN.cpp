#include "Header.h" //подключение библиотеки

void changePIN(info* head, info* tail, char* fileName, FILE* f) //функции смены пин-кода
{
	info* pointer; //указатель дл€ прохода по очереди
	file_in_str(tail, head, fileName, f); //вызов функции записи информации из файла в очередь
	if (pointer = input_PIN(tail))        //вызов функции входа в учетную запись
	{
		printf("%c[%d;%dm¬ведите новый PIN-код%c[%dm\n", 27, 1, 33, 27, 0);
		pointer->PIN = input_int();       //вызов функции ввода нового пин-кода
		replace_file(tail, fileName, f);  //вызов функции замены файла
		printf("%c[%d;%dmPIN-код успешно изменен!%c[%dm\n", 27, 1, 32, 27, 0);
	}
	return;
}