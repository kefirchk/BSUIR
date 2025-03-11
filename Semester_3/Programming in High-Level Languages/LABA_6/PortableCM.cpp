#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
PortableCM::PortableCM()                                   //конструктор без параметров
{
	batteryCapacity = 0;
}

PortableCM::PortableCM(char* nameBrand, int w, int batCap) //конструктор с параметрами
{
	this->batteryCapacity = batCap;
}

PortableCM::PortableCM(const PortableCM& PCM)              //конструктор копирования
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
}

PortableCM::PortableCM(PortableCM&& PCM)                  //конструктор перемещения
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
	PCM.weight = PCM.batteryCapacity = 0;
}

PortableCM& PortableCM::operator=(const PortableCM& PCM)   //оператор присваивания
{
	if (this != &PCM)
	{
		strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
		weight = PCM.weight;
		batteryCapacity = PCM.batteryCapacity;
	}
	return *this;
}

PortableCM& PortableCM::operator=(PortableCM&& PCM)       //оператор присваивания перемещения
{
	if (this != &PCM)
	{
		strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
		weight = PCM.weight;
		PCM.weight = 0;
		batteryCapacity = PCM.batteryCapacity;
		PCM.batteryCapacity = 0;
	}
	return *this;
}

PortableCM::~PortableCM()                                  //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void PortableCM::setBatteryCapacity(int batCap)    //метод задания емкости аккумулятора
{
	this->batteryCapacity = batCap;
}
int PortableCM::getBatteryCapacity()               //метод получения емкости аккумулятора
{
	return this->batteryCapacity;
}

//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const PortableCM& PCM) //оператор << для вывода
{
	out << dynamic_cast<const CountingMachine&>(PCM);
	out << setw(25) << left << PCM.batteryCapacity << "|";
	return out;
}
istream& operator>>(istream& in, PortableCM& PCM)        //оператор >> для ввода
{
	in >> dynamic_cast<CountingMachine&>(PCM);
	rewind(stdin);
	cout << "Введите емкость аккумулятора(mAh):" << endl;
	PCM.batteryCapacity = get_int(2000, 100000);
	rewind(stdin);
	return in;
}

ofstream& operator<<(ofstream& fout, const PortableCM& PCM) //оператор << для вывода
{
	fout << dynamic_cast<const CountingMachine&>(PCM);
	fout << setw(25) << left << PCM.batteryCapacity;//<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, PortableCM& PCM)        //оператор >> для ввода
{
	fin >> dynamic_cast<CountingMachine&>(PCM);
	fin >> PCM.batteryCapacity;
	skip_spaces(fin);
	return fin;
}

fstream& operator>>(fstream& fin, PortableCM& PCM)
{
	fin.read(reinterpret_cast<char*>(&PCM), sizeof(PortableCM));
	return fin;
}

fstream& operator<<(fstream& fout, const PortableCM& PCM)
{
	fout.write(reinterpret_cast<const char*>(&PCM), sizeof(PortableCM));
	return fout;
}
//==========================================================================================

void PortableCM::beginOfTable()
{
	CountingMachine::beginOfTable();
	for (int i = 0; i < 26; i++)
		cout << "_";
}

void PortableCM::outputHat()     //метод для вывода шапки таблицы элементов
{
	CountingMachine::outputHat();
	cout << setw(16) << left << "Емкость аккумулятора, mAh" << "|";
}

void PortableCM::endOfHat()
{
	CountingMachine::endOfHat();
	for (int i = 0; i < 25; i++)
		cout << "_";
	cout << "|";
}

void PortableCM::endOfTable()     //метод для вывода конца таблицы элементов
{
	CountingMachine::endOfTable();
	for (int i = 0; i < 25; i++)
		cout << "_";
	cout << "|";
}
