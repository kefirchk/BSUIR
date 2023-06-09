#include "Header.h" //подключение библиотеки
//#define dol 3.28;   //курс доллара на 13.03.2022 22:53
//#define eur 3.58;   //курс евро на 13.03.2022 22:54
//#define rus 0.034;  //курс российского рубл€ на 13.03.2022 22:54

long float perevod(person *man, int i) //функци€ перевода валют в белорусские рубли с возвращением общей суммы всех денег
{
	static long float dol, eur, rus;
	if (!dol || !eur || !rus)
	{
		puts("¬ведите курс доллара:");
		input_float(dol);
		puts("¬ведите курс евро:");
		input_float(eur);
		puts("¬ведите курс российских рублей:");
		input_float(rus);
		return 0;
	}
	long float sum = man[i].money[3].BYN;       //начальна€ сумма всех денег
	for (int j = 0; j < man[i].data[0].count; j++)
	{
		switch (man[i].data[1].mv[j])     
		{
		case 1: sum += man[i].money[0].dollar*dol; break; //перевод долларов
		case 2: sum += man[i].money[1].euro*eur; break;   //перевод евро
		case 3: sum += man[i].money[2].RUB*rus; break;    //перевод российских рублей
		case 4: break;
		default: puts("ќшибка!\n"); break;
		} 
	}
	return sum; //вернуть сумму всех денег
}