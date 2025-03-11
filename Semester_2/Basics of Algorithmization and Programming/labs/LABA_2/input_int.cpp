#include "Header.h"        //подключение библиотеки

int input_int(int choice)  //функция ввода количества валют
{
	int value, k, f = 0;   //value - рабочая переменная, k - временная переменная, f - флажок
	char c;                //с - временная переменная для проверки корректности ввода
	do { 
		if (f++) puts("Ошибка!");
		rewind(stdin);     //очистка буфера
		k = scanf_s("%d%c", &value, &c);  //ввод символа
		if (choice && k > 1 && c == '\n' && value < 120 && value > 0) break; //проверка на ввод возраста
		if (!choice && k > 1 && c == '\n' && value > -1 && value < 5) break; //проверка на ввод количества валюты
	} while (1);
	return value;
}