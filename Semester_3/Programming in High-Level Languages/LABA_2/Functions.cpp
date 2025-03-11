#include <iostream>    //подключение библиотеки потока ввода-вывода
using namespace std;   //использование пространства имён std

char proceed()         //функция продолжения работы программы   
{
	char c;            //временная переменная
	while (1) {
		cout << "\nПродолжить выполнение программы?(y/n)";
		cin >> c;
		if (c == 'y' || c == 'n') return c;
		else cout << "Ошибка!";
	}
}


//char*& operator+(const char* s1, const char* s2);  //оператор + (const char[] + const char[])
