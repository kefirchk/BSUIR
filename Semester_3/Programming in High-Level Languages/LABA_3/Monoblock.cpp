#include "Functions.h"

//======================================КОНСТРУКТОРЫ========================================
Monoblock::Monoblock()                                   //конструктор без параметров
{
	weight = 0;
}

Monoblock::Monoblock(char* nameBrand, int w, char* nameLocation, char* nameMouse, char* nameKeyboard)  //конструктор с параметрами
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
	this->weight = w;
}

Monoblock::Monoblock(const Monoblock &MonoB)            //конструктор копирования
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	this->weight = MonoB.weight;
}

Monoblock::Monoblock(Monoblock && MonoB)                //конструктор перемещения
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	this->weight = MonoB.weight;
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	MonoB.weight = 0;
}

Monoblock& Monoblock::operator=(const Monoblock& MonoB)   //оператор присваивания
{
	if (this != &MonoB)
	{
		strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
		weight = MonoB.weight;
		strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
		strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
		strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	}
	return *this;
}

Monoblock& Monoblock::operator=(Monoblock && MonoB)       //оператор присваивания перемещения
{
	if (this != &MonoB)
	{
		strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
		weight = MonoB.weight;
		MonoB.weight = 0;
		strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
		strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
		strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	}
	return *this;
}

Monoblock::~Monoblock()                                  //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void Monoblock::setMouse(char* nameMouse)        //метод задания названия мышки
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
}
void Monoblock::setKeyboard(char* nameKeyboard)  //метод задания названия клавиатуры
{
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}
char* Monoblock::getMouse()                      //метод получения названия мышки
{
	return this->mouse;
}
char* Monoblock::getKeyboard()                   //метод получения названия клавиатуры
{
	return this->keyboard;
}

//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const Monoblock& MonoB) //оператор << для вывода
{
	out << "|" << setw(19) << left << MonoB.brand << "|"
		<< setw(9) << left << MonoB.weight << "|"
		<< setw(19) << left << MonoB.location << "|" 
		<< setw(19) << left << MonoB.mouse << "|" 
		<< setw(19) << left << MonoB.keyboard << "|" << endl;
	return out;
}
istream& operator>>(istream& in, Monoblock& MonoB)        //оператор >> для ввода
{
	StationaryCM SCM;
	cin >> SCM;
	rewind(stdin);
	cout << "Введите название компьютерной мыши:" << endl;
	in.getline(MonoB.mouse, 80);
	rewind(stdin);
	cout << "Введите название клавиатуры:" << endl;
	in.getline(MonoB.keyboard, 80);
	rewind(stdin);
	strcpy_s(MonoB.brand, strlen(SCM.getBrand()) + 1, SCM.getBrand());
	strcpy_s(MonoB.location, strlen(SCM.getLocation()) + 1, SCM.getLocation());
	MonoB.weight = SCM.getWeight();
	rewind(stdin);
	return in;
}
//==========================================================================================

void Monoblock::outputHat()
{
	cout << " ";
	for (int i = 0; i < 89; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г"
		<< setw(20) << left << "|Местоположение" << setw(20) << left << "|Компьютерная мышь"
		<< setw(20) << left << "|Клавиатура" << "|" << endl << "|";
	for (int i = 0; i < 85; i++)
	{
		if (i == 19 || i == 28 || i == 47 || i == 66) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void Monoblock::endOfTable()
{
	for (int i = 0; i < 85; i++)
	{
		if (i == 0 || i == 19 || i == 28 || i == 47 || i == 66) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}