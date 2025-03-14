﻿/*Лабораторная работа 1.
В классе реализовать функцию объединения массивов.
Память под массивы выделять динамически.
Использовать конструктор без параметров/с параметрами, 
конструктор копирования, деструктор.
*/

#include "Arr.h"        //подключение библиотеки с классом Arr
#include "functions.h"  //подключение библиотеки вспомогательных функций

int main()
{
	setlocale(LC_ALL, "Russian");           //руссификация консоли
	do
	{
		system("cls");                      //очистка консоли
		Arr *ms = new Arr[2];               //выделение памяти под массив, состоящий из объектов класса Arr
		for (int i = 0; i < 2; i++)         //цикл по вводу массивов
		{
			cout << "Введите размер "<< i+1 << "-го массива: ";
			ms[i] = Arr(rightInput());      //вызов функции ввода числа
			cout << "Введите элементы массива: ";
			ms[i].input();                  //вызов метода ввода элементов массива
			cout << endl;
		}
		Arr rms;                            //объект для хранения результата объединения
		rms = ms[0] + ms[1];                //объединяем массивы
		cout << "Объединение массивов: ";
		rms.output();                       //вызов метода вывода массива на экран
		Arr rms2;
		rms2 = ms[0] & ms[1]& ms[0] & ms[1]& ms[0] & ms[1];
		cout << "\nПересечение массивов: ";
		rms2.output();
		delete[] ms;                        //удаление массива объектов типа Arr
	} while (proceed() == 'y');
	return 0;
}


//int main()
//{
//	setlocale(LC_ALL, "Russian");           //руссификация консоли
//	do
//	{
//		int n_of_ms;                        //n_of_ms - количество массивов
//		system("cls");                      //очистка консоли
//		cout << "Введите количество массивов: ";
//		n_of_ms = rightInput();             //вызов функции ввода числа с проверкой
//		Arr *ms = new Arr[n_of_ms];         //выделение памяти под массив, состоящий из объектов класса Arr
//		for (int i = 0; i < n_of_ms; i++)   //цикл по вводу массивов
//		{
//			cout << "\nВведите размер " << i + 1 << "-го массива: ";
//			ms[i] = Arr(rightInput());      //вызов функции ввода числа с проверкой
//			cout << "Введите элементы массива: ";
//			ms[i].input();                  //вызов метода ввода элементов массива
//		}
//		Arr rms;                            //объект для хранения результата объединения
//		for (int i = 0; i < n_of_ms; i++)   //цикл по объединению массивов
//			rms = rms.unite(ms[i]);
//		cout << "\nОбъединение массивов: ";
//		rms.output();                       //вызов метода вывода массива на экран
//		delete[] ms;                        //удаление массива объектов типа Arr
//	} while (proceed() == 'y');
//	return 0;
//}




//cout << "\nКакие массивы вы хотите объединить?\n";
		//for (int i = 0; i < n_of_ms; i++)   //вывод всех введенных массивов
		//{
		//	cout << i + 1 << "-й: ";
		//	ms[i].output();                 //вывод очередного массива
		//	cout << "\n";
		//}
		//int n1 = rightInput();              //ввод номера первого массива
		//int n2 = rightInput();              //ввод номера второго массива
		//Arr rms = ms[n1-1].unite(ms[n2-1]); //вызов метода объединения массивов