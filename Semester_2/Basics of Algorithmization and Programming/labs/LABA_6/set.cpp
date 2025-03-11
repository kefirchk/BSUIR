#include "Header.h"                                   //подключение библиотеки

void set(people** tailHuman, people** headHuman)      //функция постановки людей на очередь на заселение
{
	people* newHuman = NULL, *person = NULL, *pointerHuman = *tailHuman;  //указатели на ново-заселяемого человека, удаляемого человека, бегущий человек
	printf("\n");                                     //новая строка
	input_person_info(person);                        //вызов функции ввода информации о человеке
	newHuman = memory3();                             //вызов функции выделения памяти под человека

	if (!*tailHuman && !*headHuman)                   //очередь ещё не создана
	{
		*tailHuman = *headHuman = newHuman;           //установка указателей на хвост и голову
	    strcpy_s(newHuman->name, person->name);       //копирование информации о имени
		strcpy_s(newHuman->surname, person->surname); //копирование фамилии
		strcpy_s(newHuman->faculty, person->faculty); //копирование факультета
		newHuman->group = person->group;              //копирование номера группы
	}
	else                                              //очередь уже создана
	{
		newHuman->next_person = *tailHuman;           //вставка элемента в конец очереди
		(*tailHuman)->previous_person = newHuman;     //связка последних элементов
		(*tailHuman) = newHuman;                      //корректировка хвоста
		strcpy_s(newHuman->name, person->name);       //копирование введенных данных
		strcpy_s(newHuman->surname, person->surname);
		strcpy_s(newHuman->faculty, person->faculty);
		newHuman->group = person->group;
	}
	printf("%c[%d;%dm\nЧеловек добавлен в очередь на заселение!%c[%dm\n", 27, 1, 32, 27, 0);
}