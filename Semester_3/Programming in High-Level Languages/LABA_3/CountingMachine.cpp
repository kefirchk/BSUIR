#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
CountingMachine::CountingMachine()                           //конструктор без параметров
{
	weight = 0;
}

CountingMachine::CountingMachine(char* name, int w)          //конструктор с параметрами
{
	strcpy_s(brand, strlen(name) + 1, name);
	this->weight = w;
}

CountingMachine::CountingMachine(const CountingMachine &CM)  //конструктор копирования
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	this->weight = CM.weight;
}

CountingMachine::CountingMachine(CountingMachine && CM)      //конструктор перемещения
	: weight(CM.weight)
{   weight = 0;  }

CountingMachine::~CountingMachine()                          //деструктор
{}

CountingMachine& CountingMachine::operator=(const CountingMachine& CM)   //оператор присваивания
{
	if (this != &CM)
	{
		strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
		weight = CM.weight;
	}
	return *this;
}

CountingMachine& CountingMachine::operator=(CountingMachine && CM)       //оператор присваивания перемещения
{
	if (this != &CM)
	{
		strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
		weight = CM.weight;
		CM.weight = 0;
	}
	return *this;
}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void CountingMachine::setBrand(char* name)    //метод задания названия марки
{
	strcpy_s(brand, strlen(name) + 1, name);
}
void CountingMachine::setWeight(int w)        //метод задания веса
{
	this->weight = w;
}
char* CountingMachine::getBrand()             //метод получения названия марки
{
	return this->brand;
}
int CountingMachine::getWeight()              //метод получения веса
{
	return this->weight;
}
//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const CountingMachine& CM) //оператор << для вывода
{
	out << "|" << setw(19) << left << CM.brand << "|" << setw(9) << left << CM.weight << "|" << endl;
	return out;
}
istream& operator>>(istream& in, CountingMachine& CM)        //оператор >> для ввода
{
	cout << "Введите название производителя:" << endl;
	in.getline(CM.brand, 80);
	rewind(stdin);
	cout << "Введите вес(г):" << endl;
	in >> CM.weight;
	rewind(stdin);
	return in;
}
//==========================================================================================

void CountingMachine::outputHat()
{
	cout << " ";
	for (int i = 0; i < 29; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г" << "|" << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void CountingMachine::endOfTable()
{
	for (int i = 0; i < 28; i++)
	{
		if (i == 0 || i == 19) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}