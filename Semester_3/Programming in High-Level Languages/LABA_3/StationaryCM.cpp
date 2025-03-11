#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
StationaryCM::StationaryCM()                                   //конструктор без параметров
{
	weight = 0;
}

StationaryCM::StationaryCM(char* nameBrand, int w, char* nameLocation)  //конструктор с параметрами
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
	this->weight = w;
}

StationaryCM::StationaryCM(const StationaryCM &SCM)            //конструктор копирования
{
	strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
	strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	this->weight = SCM.weight;
}

StationaryCM::StationaryCM(StationaryCM && SCM)                //конструктор перемещения
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

StationaryCM& StationaryCM::operator=(StationaryCM && SCM)     //оператор присваивания перемещения
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
	out << "|" << setw(19) << left << SCM.brand << "|" 
		<< setw(9) << left << SCM.weight << "|"
		<< setw(19) << left << SCM.location << "|" << endl;
	return out;
}
istream& operator>>(istream& in, StationaryCM& SCM)        //оператор >> для ввода
{
	CountingMachine CM;
	cin >> CM;
	rewind(stdin);
	cout << "Введите местоположение:" << endl;
	in.getline(SCM.location, 80);
	rewind(stdin);
	strcpy_s(SCM.brand, strlen(CM.getBrand()) + 1, CM.getBrand());
	SCM.weight = CM.getWeight();
	rewind(stdin);
	return in;
}
//==========================================================================================

void StationaryCM::outputHat()
{
	cout << " ";
	for (int i = 0; i < 49; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г"
		<< setw(20) << left << "|Местоположение" << "|" << endl << "|";
	for (int i = 0; i < 47; i++)
	{
		if (i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void StationaryCM::endOfTable()
{
	for (int i = 0; i < 47; i++)
	{
		if (i == 0 || i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}