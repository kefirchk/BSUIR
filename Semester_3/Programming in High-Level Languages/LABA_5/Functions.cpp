#include "Functions.h"
#include "Exception.h"
#include "Interface.cpp"
#define LANGUAGE 0  //1 - русский, 0 - английский язык

int get_int(int min, int max)
{
	Interface<char> temp;
	int value;            //временная переменная под целое число
	temp.setColor(8);     //серый
	cout << "(целое число в дипазоне ["<< min << ", " << max << "])" << endl;
	temp.setColor(7);     //белый
	rewind(stdin);        //очистка буфера ввода
	do
	{
		try
		{
			//rewind(stdin);     //очистка буфера ввода
			cin >> value;      //ввод значения
			if (!cin || cin.peek() != '\n')
				throw InputException(1, "Ошибка ввода!", "Введено не целое число.\nВводите только целые числа");
			 if (value > max || value < min)
				throw InputException(2, "Ошибка ввода!", "Выход за границы диапазона.\nВводите только числа в указанном диапазоне");
			else if (cin.peek() != '\n')
				throw InputException(3, "Ошибка ввода!", "Переполнение буфера ввода.\nПовторите ввод без лишних символов после числа");
			 return value;
		}
		catch (InputException obj)
		{
			rewind(stdin);     //очистка буфера ввода
			obj.what();        //вывод текста об ошибке
			cin.clear();       //очистить флаг ошибки
		}
	} while (1);
}

char get_char(char first, char second)
{
	char value;                //временная переменная для ввода
	rewind(stdin);             //очистка буфера ввода
	do
	{
		try
		{
			//rewind(stdin);     //очистка буфера ввода
			cin >> value;      //ввода символа
			if (value != first && value != second)   //проверка на корректность ввода символа
				throw InputException(4, "Ошибка ввода!", "Выход за границы диапазона.\nВводите только указанные символы");
			if (cin.peek() != '\n')
				throw InputException(3, "Ошибка ввода!", "Переполнение буфера ввода.\nВведите только один символ");
			return value;
		}
		catch (InputException obj)
		{
			rewind(stdin);     //очистка буфера ввода
			obj.what();        //вывод текста об ошибке
			cin.clear();       //очистить флаг ошибки
		}
	} while (1);
}

char* get_str(istream& in)
{
	Interface<char> temp;
	int value;            //временная переменная под целое число
	temp.setColor(8);     //серый
	char *str = new char[80];
	if (LANGUAGE == 1) cout << "(на русском языке)" << endl;
	else if (LANGUAGE == 0) cout << "(на английском языке)" << endl;
	temp.setColor(7);     //белый
	rewind(stdin);        //очистка буфера ввода
	do
	{
		try
		{
			//rewind(stdin);          //очистка буфера
			in.getline(str, 80);
			if (!in.good())
				throw InputException(3, "Ошибка ввода!", "Переполнение буфера ввода.\nВводите строку по длине < 80");
			else if (!strlen(str))
				throw InputException(6, "Ошибка ввода!", "Строка не введена.\nВведите строку");
			if (LANGUAGE == 0)      //должен быть английский текст
			{
				for (int i = 0; i < strlen(str); i++)
				{
					if ((str[i] >= 'А' && str[i] <= 'Я') || (str[i] >= 'а' && str[i] <= 'я'))
						throw InputException(7, "Ошибка ввода!", "Введены русские буквы.\nВведите строку, используя только английские буквы");
				}
				return str;
			}
			else if (LANGUAGE == 1) //должен быть русский текст
			{
				for (int i = 0; i < strlen(str); i++)
				{
					if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
						throw InputException(8, "Ошибка ввода!", "Введены английские буквы.\nВведите строку, используя только русские буквы");
				}
				return str;
			}
		}
		catch (InputException obj)
		{
			rewind(stdin);     //очистка буфера ввода
			obj.what();        //вывод текста об ошибке
			cin.clear();       //очистить флаг ошибки
		}
	} while (1);
}