/*Лабораторная работа №2. 
Перегрузка функций. Разработка собственного класса string

Перегруженные операторы: =, +=, +, ==, !=, >, >=, <, <=, [], (), >>, <<
*/

#include "Functions.h"
#include "String.h"

int main()
{
	setlocale(LC_ALL, "Russian");           //руссификация консоли
	String obj1, obj2, res;
	cout << "Введите первую строку: ";
	cin >> obj1;
	cout << "Введите вторую строку: ";
	cin >> obj2;
	//do
	//{
		if (obj1 > obj2)
		{
			res = "stroka1 " + --(obj2++) + ' ' + obj2[0] + " stroka2 " + obj1(0, obj1.StrLen() - 1);
		}
		else if (obj1 < obj2)
		{
			obj2 += obj1 + ' ' + obj1[0] + ' ' + obj2(0, obj2.StrLen() - 1);
		}
		else if (obj1 == obj2)
		{
			res = obj1 += obj2;
		}
		cout << endl << "Результат: " << res << endl;
	//} while (proceed() == 'y');
	return 0;
}