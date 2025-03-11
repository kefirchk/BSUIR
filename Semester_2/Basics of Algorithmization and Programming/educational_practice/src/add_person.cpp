#include "Header.h" //подключение библиотеки

void add_person(info** tail, info** head, char* fileName, FILE* f) //функция добавления человека в очередь и файл
{
	while (1)
	{
		info* pointer = (info*)calloc(1, sizeof(info)); //указатель для прохода по очереди 
		if (!pointer)
		{
			printf("%c[%d;%dmПамять не выделена!%c[%dm\n", 27, 1, 31, 27, 0);
			return;
		}
		printf("%c[%d;%dm\nВведите имя:%c[%dm\n", 27, 1, 33, 27, 0);
        strcpy_s(pointer->name, input_str());                             //ввод имени
		printf("%c[%d;%dm\nВведите фамилию:%c[%dm\n", 27, 1, 33, 27, 0);
		strcpy_s(pointer->surname, input_str());                          //ввод фамилии
		pointer->cash[0].dollar = pointer->cash[1].euro = pointer->cash[2].RUB = pointer->cash[3].BYN = 0; //обнуление всех валют
		pointer->PIN = 1234;                                              //начальный пин-код
		//pointer->PIN = rand() % 9000 + 1000;
		printf("%c[%d;%dm\nВаш PIN-код: %c[%dm%c[%d;%dm%d%c[%dm", 27, 1, 33, 27, 0, 27, 1, 32, pointer->PIN, 27, 0);
		if (!*tail || !*head) *tail = *head = pointer; //если очередь не создана
		else
		{
			pointer->next = *tail;      //добавление элемента в хвост очереди
			*tail = pointer;            //корректировка хвоста
		}
		printf("%c[%d;%dm\nПродолжить?(y\\n)%c[%dm\n", 27, 1, 33, 27, 0);
		if (!offer())                   //предложение о продолжении добавления людей
		{
			struct_in_file(fileName, f, *tail); //вызов фукнции записи структуры в текстовый файл
			return;
		}
	}
}