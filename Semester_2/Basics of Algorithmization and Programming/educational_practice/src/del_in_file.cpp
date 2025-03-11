#include "Header.h"     //подключение библиотеки

int del_in_file(FILE *&f, info *&tail, info* &head, char* fileName)  //функция оперерирования по удалению человека из файла и очереди
{
	info* element = NULL;                     //указатель на удаляемый элемент
	if (file_in_str(tail, head, fileName, f)) //вызов функции записи информации из файла в структуры
	{
		if (element = input_PIN(tail))        //вызов функции входа в учетную запись
		{
			del_person(&tail, &head, element);    //вызов функции удаления человека из очереди
			replace_file(tail, fileName, f);      //вызов функции замены файла
		}
	}
	else printf("%c[%d;%dmФайл пуст%c[%dm\n", 27, 1, 32, 27, 0);
	return 0;
}

void del_person(info** tail, info** head, info* &element) //функции удаления человека из очереди
{
	info* pointer = *tail, *prev_pointer = *tail;         //указатель для обхода очереди, указатель на предыдущий элемент по отношению к pointer
	if (element)
	{
		if (!*tail || !*head)                             //очередь не создана
		{
			puts("База данных пуста!");
			return;
		}
		if (*tail && *tail == *head)                      //в очереди один элемент
		{
			free(*tail);                                  //освободить память
			*head = *tail = NULL;                         //зануление указателей
			return;
		}
		while (pointer && pointer != element)             //цикл по очереди, пока не нашли требуемый элемент
		{
			prev_pointer = pointer;                       //установка указателя prev-pointer на предыдущий элемент
			pointer = pointer->next;                      //установка указателя pointer на следующий элемент
		}
		if (pointer)                                      //если нашелся требуемый элемент
		{
			if (*tail == pointer) *tail = pointer->next;  //если удаляемый элемент - это хвост очереди
			if (*head == pointer) *head = prev_pointer;   //если удаляемый элемент - это голова очереди
			else
			{
				prev_pointer = pointer->next;             //обход элемента
				free(pointer);                            //удаление элемента
			}
		}
	}
	else return;
}