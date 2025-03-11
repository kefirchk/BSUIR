#include "Header.h"            //подключение библиотеки

int *poisk1(int n, person *man)  //функция поиска людей, у которых больше всего и меньше всего белорусских рублей
{
	static int ms1[4] = {};
	int kmax = 0, kmin = 0;    //kmax, kmin - индексы искомых структур 
	int flag1 = 0, flag2 = 0;  //flag1, flag2 - флажки (если такие люди не одни)
	for (int i = 0; i < n; i++)
	{
		if (man[kmax].money[3].BYN == man[i].money[3].BYN && kmax != i) flag1++;  //если нашелся человек, который также является пока что самым богатым по белорусским рублям
		if (man[kmax].money[3].BYN < man[i].money[3].BYN) kmax = i; //если нашелся человек с наибольшим количеством белорусских монет
		if (man[kmin].money[3].BYN == man[i].money[3].BYN && kmin != i) flag2++; //если нашелся человек, который также является пока что самым бедным по белорусским рублям
		if (man[kmin].money[3].BYN > man[i].money[3].BYN) kmin = i;  //если нашелся человек с наименьшим количеством белорусских рублей
	}
	ms1[0] = kmax; //вносим все найденные данные в массив
	ms1[1] = kmin;
	ms1[2] = flag1;
	ms1[3] = flag2;
	
	//через дополнительную структуру
	for (int i = 0, j = kmax; i<2 ; i++)
	{
		if (i > 0) j = kmin;
		man[0].result[i].age = man[j].age;
		man[0].result[i].BYN = man[j].money[3].BYN;
		strcpy_s(man[0].result[i].name, n2 * sizeof(char), man[j].name);
		strcpy_s(man[0].result[i].surname, n2 * sizeof(char), man[j].surname);
	}
	return ms1;    //возвращаем указатель на массив индексов
}