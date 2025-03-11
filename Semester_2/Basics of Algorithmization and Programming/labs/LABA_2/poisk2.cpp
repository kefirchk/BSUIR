#include "Header.h"     //подключение библиотеки

int *poisk2(int n, person *man) //функция поиска самого богатого и самого бедного человека
{
	static int ms2[4] = {};
	int kmax = 0, kmin = 0;   //индексы искомых структур
	int flag1 = 0, flag2 = 0; //flag1, flag2 - флажки (если такие люди не одни)
	for (int i = 0; i < n; i++)
	{
		if (perevod(man, kmax) == perevod(man, i) && kmax != i) flag1++; //если нашелся такой же результат
		if (perevod(man, kmax) < perevod(man, i)) kmax = i; //если нашелся человек богаче, запоминаем его индекс
		if (perevod(man, kmin) == perevod(man, i) && kmin != i) flag2++; //если нашелся такой же результат
		if (perevod(man, kmin) > perevod(man, i)) kmin = i; //если нашелся человек беднее, запоминаем его индекс
	}
	ms2[0] = kmax;      //вносим найденные значения в массив
	ms2[1] = kmin;
	ms2[2] = flag1;
	ms2[3] = flag2;

	//через дополнительную структуру
	for (int i = 2, j = kmax; i < 4; i++)
	{
		if (i > 2) j = kmin;
		man[0].result[i].age = man[j].age;
		man[0].result[i].BYN = man[j].money[3].BYN;
		strcpy_s(man[0].result[i].name, n2 * sizeof(char), man[j].name);
		strcpy_s(man[0].result[i].surname, n2 * sizeof(char), man[j].surname);
	}
	return ms2;         //возвращаем указатель на массив индексов
}