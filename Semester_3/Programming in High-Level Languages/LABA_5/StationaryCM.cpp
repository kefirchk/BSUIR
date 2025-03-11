#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
StationaryCM::StationaryCM()            //конструктор без параметров
{
	strcpy_s(this->location, 1, "");
}

StationaryCM::StationaryCM(char* nameBrand, int w, char* nameLocation)  //конструктор с параметрами
{
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
}

StationaryCM::StationaryCM(const StationaryCM& SCM)            //конструктор копирования
{
	strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
	strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	this->weight = SCM.weight;
}

StationaryCM::StationaryCM(StationaryCM&& SCM)                //конструктор перемещения
{
	this->weight = SCM.weight;
	strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
	strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	SCM.weight = 0;
}

StationaryCM& StationaryCM::operator=(const StationaryCM& SCM) //оператор присваивания
{
	if (this != &SCM)
	{
		strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
		weight = SCM.weight;
		strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	}
	return *this;
}

StationaryCM& StationaryCM::operator=(StationaryCM&& SCM)     //оператор присваивания перемещения
{
	if (this != &SCM)
	{
		strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
		weight = SCM.weight;
		SCM.weight = 0;
		strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	}
	return *this;
}

StationaryCM::~StationaryCM()                                  //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void StationaryCM::setLocation(char* nameLocation)    //метод задания местоположения
{
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
}
char* StationaryCM::getLocation()                     //метод получения местоположения
{
	return this->location;
}

//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const StationaryCM& SCM) //оператор << для вывода
{
	out << dynamic_cast<const CountingMachine&>(SCM);
	out << setw(19) << left << SCM.location << "|";
	return out;
}
istream& operator>>(istream& in, StationaryCM& SCM)        //оператор >> для ввода
{
	in >> dynamic_cast<CountingMachine&>(SCM);
	rewind(stdin);
	cout << "Введите местоположение:" << endl;
	char* str = get_str(in);
	strcpy_s(SCM.location, strlen(str) + 1, str);
	rewind(stdin);
	return in;
}
//==========================================================================================

void StationaryCM::beginOfTable()
{
	CountingMachine::beginOfTable();
	for (int i = 0; i < 20; i++)
		cout << "_";
}

void StationaryCM::outputHat()        //метод вывод шапки таблицы элементов
{
	CountingMachine::outputHat();
	cout << setw(19) << left << "Местоположение" << "|";
}

void StationaryCM::endOfHat()
{
	CountingMachine::endOfHat();
	for (int i = 0; i < 19; i++)
		cout << "_";
	cout << "|";
}

void StationaryCM::endOfTable()       //метод вывода конца таблицы элементов
{
	CountingMachine::endOfTable();
	for (int i = 0; i < 19; i++)
		cout << "_";
	cout << "|";
}