#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
Smartphone::Smartphone()                                   //конструктор без параметров
{
	weight = batteryCapacity = сameraResolution = 0;
}

Smartphone::Smartphone(char* nameBrand, int w, int batCap, char* screen, int camera)  //конструктор с параметрами
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	this->weight = w;
	this->batteryCapacity = batCap;
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
	this->сameraResolution = camera;
}

Smartphone::Smartphone(const Smartphone &phone)            //конструктор копирования
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->сameraResolution = phone.сameraResolution;
}

Smartphone::Smartphone(Smartphone && phone)                //конструктор перемещения
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->сameraResolution = phone.сameraResolution;
	phone.weight = phone.batteryCapacity = phone.сameraResolution = 0;
}

Smartphone& Smartphone::operator=(const Smartphone& phone)   //оператор присваивания
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		batteryCapacity = phone.batteryCapacity;
		сameraResolution = phone.сameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	}
	return *this;
}

Smartphone& Smartphone::operator=(Smartphone && phone)       //оператор присваивания перемещения
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		phone.weight = 0;
		batteryCapacity = phone.batteryCapacity;
		сameraResolution = phone.сameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
		phone.batteryCapacity = 0;
		phone.сameraResolution = 0;
	}
	return *this;
}

Smartphone::~Smartphone()                                  //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void Smartphone::setTouchScreen(char* screen)              //метод задания типа экрана
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
}
void Smartphone::setCameraResolution(int camera)           //метод задания разрешения камеры
{
	this->сameraResolution = camera;
}
char* Smartphone::getTouchScreen()                  //метод получения типа экрана
{
	return this->touchScreen;
}
int Smartphone::getCameraResolution()               //метод получения разрешения камеры
{
	return this->сameraResolution;
}
//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const Smartphone& phone) //оператор << для вывода
{
	out << "|" << setw(19) << left << phone.brand << "|"
		<< setw(9) << left << phone.weight << "|"
		<< setw(25) << left << phone.batteryCapacity << "|"
		<< setw(10) << left << phone.touchScreen << "|" 
		<< setw(21) << left << phone.сameraResolution << "|" << endl;
	return out;
}
istream& operator>>(istream& in, Smartphone& phone)        //оператор >> для ввода
{
	PortableCM PCM;
	cin >> PCM;
	rewind(stdin);
	strcpy_s(phone.brand, strlen(PCM.getBrand()) + 1, PCM.getBrand());
	phone.weight = PCM.getWeight();
	phone.batteryCapacity = PCM.getBatteryCapacity();
	cout << "Введите тип экрана смартфона:" << endl;
	in.getline(phone.touchScreen, 80);
	rewind(stdin);
	cout << "Введите разрешение камеры смартфона(Мп):" << endl;
	cin >> phone.сameraResolution;
	rewind(stdin);
	return in;
}
//==========================================================================================

void Smartphone::outputHat()
{
	cout << " ";
	for (int i = 0; i < 88; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г"
		<< setw(17) << left << "|Емкость аккумулятора, mAh" << setw(11) << left << "|Тип экрана"
		<< setw(22) << "|Разрешение камеры, Мп" << "|" << endl << "|";
	for (int i = 0; i < 84; i++)
	{
		if (i == 19 || i == 28 || i == 53 || i == 63) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void Smartphone::endOfTable()
{
	for (int i = 0; i < 84; i++)
	{
		if (i == 0 || i == 19 || i == 28 || i == 53 || i == 63) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}