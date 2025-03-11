#include "Functions.h"

//======================================������������========================================
Monoblock::Monoblock()                                   //����������� ��� ����������
{
	weight = 0;
}

Monoblock::Monoblock(char* nameBrand, int w, char* nameLocation, char* nameMouse, char* nameKeyboard)  //����������� � �����������
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
	this->weight = w;
}

Monoblock::Monoblock(const Monoblock &MonoB)            //����������� �����������
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	this->weight = MonoB.weight;
}

Monoblock::Monoblock(Monoblock && MonoB)                //����������� �����������
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	this->weight = MonoB.weight;
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	MonoB.weight = 0;
}

Monoblock& Monoblock::operator=(const Monoblock& MonoB)   //�������� ������������
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

Monoblock& Monoblock::operator=(Monoblock && MonoB)       //�������� ������������ �����������
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

Monoblock::~Monoblock()                                  //����������
{}
//==========================================================================================

//=======================================������=============================================
void Monoblock::setMouse(char* nameMouse)        //����� ������� �������� �����
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
}
void Monoblock::setKeyboard(char* nameKeyboard)  //����� ������� �������� ����������
{
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}
char* Monoblock::getMouse()                      //����� ��������� �������� �����
{
	return this->mouse;
}
char* Monoblock::getKeyboard()                   //����� ��������� �������� ����������
{
	return this->keyboard;
}

//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const Monoblock& MonoB) //�������� << ��� ������
{
	out << "|" << setw(19) << left << MonoB.brand << "|"
		<< setw(9) << left << MonoB.weight << "|"
		<< setw(19) << left << MonoB.location << "|" 
		<< setw(19) << left << MonoB.mouse << "|" 
		<< setw(19) << left << MonoB.keyboard << "|" << endl;
	return out;
}
istream& operator>>(istream& in, Monoblock& MonoB)        //�������� >> ��� �����
{
	StationaryCM SCM;
	cin >> SCM;
	rewind(stdin);
	cout << "������� �������� ������������ ����:" << endl;
	in.getline(MonoB.mouse, 80);
	rewind(stdin);
	cout << "������� �������� ����������:" << endl;
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
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
		<< setw(20) << left << "|��������������" << setw(20) << left << "|������������ ����"
		<< setw(20) << left << "|����������" << "|" << endl << "|";
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