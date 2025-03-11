#include "Header.h"                 //подключение библиотеки

int exercise_b(pupil *info1, int size, int *ms1, int *ms2) //функция поиска однофамильцев в параллельных классах
{
	int flag = 0, flag1 = 0, flag2 = 0;  //flag, flag1, flag2 - флажки
	int k = 0; //счетчик для массива индексов
	for (int i = 0; i < size; i++)      //цикл по i (i-я фамилия сравнивается с другими j-ми)
	{
		for (int j = 0; j < size; j++)  //цикл по j (берется j-я фамилия для сравнения с i-й)
		{
			if (!strcmp(info1[ms1[i]].familia, info1[ms1[j]].familia) && info1[ms1[i]].letter != info1[ms1[j]].letter && info1[ms1[i]].clas == info1[ms1[j]].clas)     //если 0, то значит фамилии совпадают
			{
				if (!flag1)          //если 0, то значит фамилия печатуется в первый раз
				{
					//if (!flag2) printf("\nОднофамильцы в параллельных классах:");
					ms2[k++] = i;
					//printf("\n%s %s (%d классы) - ", info[ms1[i]].imya, info[ms1[i]].familia, info[ms1[i]].clas);
					flag2 = 1;       //нашлась хотя бы одна пара одинаковых фамилий
				}
				//if (flag2 && flag1) printf(", "); //поставить запятую
				//if (j != i) printf("%s %s", info[ms1[j]].imya, info[ms1[j]].familia);
				if (j != i) ms2[k++] = j;
				flag1 = 1;           //сравниваемая фамилия уже напечатана
			}
		}
		flag1 = 0;                   //возвращаем к начальному значению, чтобы выполнить новую итерацию
	}
	if (!flag2) puts("\nОдинаковых фамилий в параллельных классах не найдено");
	printf("\n");
	return k;
}