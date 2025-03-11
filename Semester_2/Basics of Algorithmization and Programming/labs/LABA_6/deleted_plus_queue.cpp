#include "Header.h"                                 //подключение библиотеки

void deleted_plus_queue(people** headHuman, people** tailHuman, people* person)  //функция добавления человека в список выселенных людей
{
	if (person)                                     //если человек действительно был удален
	{
		if (!*tailHuman && !*headHuman)             //если очередь была пуста
		{
			*tailHuman = *headHuman = person;       //расстановка главных указателей на хвост и голову
		}
		else
		{
			person->next_person = *tailHuman;       //вставка элемента в конец очереди
			(*tailHuman)->previous_person = person; //установка связей между элементами
			(*tailHuman) = person;                  //корректировка хвоста
		}
	}
}