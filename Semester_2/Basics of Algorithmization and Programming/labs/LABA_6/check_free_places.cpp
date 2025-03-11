#include "Header.h"                                                //подключение библиотеки

int check_free_places(floor* tailFloor, int* ms)                   //функция проверки общежития на наличие свободных мест
{
	floor* pointerFloor = tailFloor;                               //указатель по этажам
	int freePlaces = 0, i = 1;                                     //общее кол-во свободных мест и счетчик по этажам
	while (pointerFloor || i <= ms[0])                             //цикл для прохода по этажам
	{
		if (pointerFloor && i == pointerFloor->numberOfFloor)      //этаж идет по порядку и соответсвуюет счетчику
		{
			freePlaces += pointerFloor->freePlaces;                //считаем кол-во свободных мест
			pointerFloor = pointerFloor->next_floor;               //переходим к следующему этажу
		}
		else freePlaces += ms[1] * ms[2];                          //этаж не был до этого создан, учитываем, что он свободен
		i++;                                                       //увеличение счетчика
	}
	printf("\nВсего доступно %d свободных мест\n", freePlaces);    //вывод общего кол-ва свободных мест
	if (freePlaces)                                                //если есть свободные места, то вывод их по этажам
	{
		int k = 0;                                                 //счетчик
		
		printf(" ");
		while (k++ < 26) printf("_");                              //рисовка верхней границы таблицы
		printf("\n|Этаж|Кол-во свободных мест|\n|");               //вывод "шапки"
		while (--k > 1)                                            //подрисовка верхней границы таблицы
		{
			if (k == 22) printf("|");
			printf("_");
		}
		i = 1;
		pointerFloor = tailFloor;                                  //устанавливаем указатель на первый этаж (хвост)
		while (pointerFloor || i <= ms[0])
		{
			freePlaces = 0;                                        //обнуление кол-ва мест
			if (pointerFloor && i == pointerFloor->numberOfFloor)  //если этаж соответствует счетчику
			{
				freePlaces += pointerFloor->freePlaces;            //считаем кол-во мест
				pointerFloor = pointerFloor->next_floor;           //переход к следующему этажу
			}
			else freePlaces += ms[1] * ms[2];                      //этаж не был создан до этого, учитываем, что он полностью свободен
			printf("|\n|%-4d|          %-11d", i, freePlaces);     //вывод информации
			i++;                                                   //увеличение счетчика
		}
		printf("|\n|");
		while (k++ < 26)                                           //рисовка нижней границы таблицы
		{
			if (k == 6) printf("|");
			printf("_");
		} puts("|");
	}
	return freePlaces;                                             //вернуть кол-во свободных мест
}