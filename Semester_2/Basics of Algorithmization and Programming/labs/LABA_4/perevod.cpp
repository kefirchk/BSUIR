#include "Header.h" //подключение библиотеки
//#define dol 3.28;   //курс доллара на 13.03.2022 22:53
//#define eur 3.58;   //курс евро на 13.03.2022 22:54
//#define rus 0.034;  //курс российского рубл€ на 13.03.2022 22:54

double perevod(person *man, int i) //функци€ перевода валют в белорусские рубли с возвращением общей суммы всех денег
{
	static double dol, eur, rus;
	if (i < 0) dol = eur = rus = 0;
	if (!dol || !eur || !rus)
	{
		printf("\n¬ведите курс доллара: ");
		input_float(dol);
		printf("¬ведите курс евро: ");
		input_float(eur);
		printf("¬ведите курс российских рублей: ");
		input_float(rus);
		return 0;
	}
	double sum = man[i].money[3].BYN;       //начальна€ сумма всех денег
	//for (int j = 0; j < 4; j++)                 //man[i].data[0].count
	//{
		switch (man[i].data[1].mv[0])
		{
		case 0: case 1: case 2: case 3: 
		sum = sum + man[i].money[0].dollar*dol + man[i].money[1].euro*eur + man[i].money[2].RUB*rus; break;
		//case 1: sum += man[i].money[0].dollar*dol; break; //перевод долларов
		//case 2: sum += man[i].money[1].euro*eur; break;   //перевод евро
		//case 3: sum += man[i].money[2].RUB*rus; break;    //перевод российских рублей
		case 4: break;
		default: puts("ќшибка!\n"); break;
		}
	//}
	return sum; //вернуть сумму всех денег
}