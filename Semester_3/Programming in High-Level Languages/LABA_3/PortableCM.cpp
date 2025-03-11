#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
PortableCM::PortableCM()                                   //конструктор без параметров
{
	weight = batteryCapacity = 0;
}

PortableCM::PortableCM(char* nameBrand, int w, int batCap)  //конструктор с параметрами
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	this->weight = w;
	this->batteryCapacity = batCap;
}

PortableCM::PortableCM(const PortableCM &PCM)            //конструктор копирования
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
}

PortableCM::PortableCM(PortableCM && PCM)                //конструктор перемещения
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

PortableCM& PortableCM::operator=(PortableCM && PCM)       //оператор присваивания перемещения
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
	out << "|" << setw(19) << left << PCM.brand << "|"
		<< setw(9) << left << PCM.weight << "|"
		<< setw(25) << left << PCM.batteryCapacity << "|" << endl;
	return out;
}
istream& operator>>(istream& in, PortableCM& PCM)        //оператор >> для ввода
{
	CountingMachine CM;
	cin >> CM;
	rewind(stdin);
	strcpy_s(PCM.brand, strlen(CM.getBrand()) + 1, CM.getBrand());
	PCM.weight = CM.getWeight();
	cout << "Введите емкость аккумулятора(mAh):" << endl;
	cin >> PCM.batteryCapacity;
	rewind(stdin);
	return in;
}
//==========================================================================================

void PortableCM::outputHat()
{
	cout << " ";
	for (int i = 0; i < 55; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г"
		<< setw(17) << left << "|Емкость аккумулятора, mAh" << "|" << endl << "|";
	for (int i = 0; i < 53; i++)
	{
		if (i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void PortableCM::endOfTable()
{
	for (int i = 0; i < 53; i++)
	{
		if (i == 0 || i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}