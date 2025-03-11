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
void StationaryCM::setLocation(const char* nameLocation)    //метод задания местоположения
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

ofstream& operator<<(ofstream& fout, const StationaryCM& SCM) //оператор << для вывода
{
	fout << dynamic_cast<const CountingMachine&>(SCM);
	fout << setw(19) << left << SCM.location << '|'; //<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, StationaryCM& SCM)        //оператор >> для ввода
{
	fin >> dynamic_cast<CountingMachine&>(SCM);
	//fin >> SCM.location;
	fin.getline(SCM.location, 80, '|');
	char* s = SCM.location;
	delete_spaces(s);
	return fin;
}

fstream& operator>>(fstream& fin, StationaryCM& SCM)
{
	fin.read(reinterpret_cast<char*>(&SCM), sizeof(StationaryCM));
	return fin;
}

fstream& operator<<(fstream& fout, const StationaryCM& SCM)
{
	fout.write(reinterpret_cast<const char*>(&SCM), sizeof(StationaryCM));
	return fout;
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