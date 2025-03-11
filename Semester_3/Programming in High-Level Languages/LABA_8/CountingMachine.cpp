#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
CountingMachine::CountingMachine()                           //конструктор без параметров
{
	strcpy_s(brand, 1, "");
	weight = 0;
}
CountingMachine::CountingMachine(char* name, int w)          //конструктор с параметрами
{
	strcpy_s(brand, strlen(name) + 1, name);
	this->weight = w;
}

CountingMachine::CountingMachine(const CountingMachine& CM)  //конструктор копирования
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	this->weight = CM.weight;
}

CountingMachine::CountingMachine(CountingMachine&& CM)       //конструктор перемещения
	: weight(CM.weight)
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	strcpy_s(CM.brand, 1, "");
	CM.weight = 0;
}

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

CountingMachine& CountingMachine::operator=(CountingMachine&& CM)       //оператор присваивания перемещения
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
void CountingMachine::setBrand(const char* name)    //метод задания названия марки
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
	out << "|" << setw(19) << left << CM.brand << "|" << setw(9) << left << CM.weight << "|";
	return out;
}
istream& operator>>(istream& in, CountingMachine& CM)        //оператор >> для ввода
{
	rewind(stdin);
	cout << "Введите название производителя:" << endl;
	char *str = get_str(in);
	strcpy_s(CM.brand, strlen(str) + 1, str);
	rewind(stdin);
	cout << "Введите вес(г):" << endl;
	CM.weight = get_int(1, SHRT_MAX);
	rewind(stdin);
	return in;
}

ifstream& operator>>(ifstream& fin, CountingMachine& CM)
{
	fin.getline(CM.brand, 80, '|');
	char* s = CM.brand;
	delete_spaces(s);
	//fin >> CM.brand >> CM.weight;
	fin >> CM.weight;
	skip_spaces(fin);
	return fin;
}

ofstream& operator<<(ofstream& fout, const CountingMachine& CM)
{
	fout << setw(19) << left << CM.brand << '|'
		<< setw(9) << left << CM.weight; //<< "|";
	return fout;
}

fstream& operator>>(fstream& fin, CountingMachine& CM)
{
	fin.read(reinterpret_cast<char*>(&CM), sizeof(CountingMachine));
	return fin;
}

fstream& operator<<(fstream& fout, const CountingMachine& CM)
{
	fout.write(reinterpret_cast<const char*>(&CM), sizeof(CountingMachine));
	return fout;
}
//==========================================================================================

void CountingMachine::beginOfTable()
{
	cout << " ";
	for (int i = 0; i < 29; i++)
		cout << "_";
}

void CountingMachine::outputHat()  //вывод шапки таблицы элементов дерева
{
	cout << endl << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г" << "|";
}

void CountingMachine::endOfHat()
{
	cout << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void CountingMachine::endOfTable() //вывод конца таблицы элементов дерева
{
	cout << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}