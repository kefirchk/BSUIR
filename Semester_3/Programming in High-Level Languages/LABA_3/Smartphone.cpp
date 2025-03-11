#include "Functions.h"

//======================================������������========================================
Smartphone::Smartphone()                                   //����������� ��� ����������
{
	weight = batteryCapacity = �ameraResolution = 0;
}

Smartphone::Smartphone(char* nameBrand, int w, int batCap, char* screen, int camera)  //����������� � �����������
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	this->weight = w;
	this->batteryCapacity = batCap;
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
	this->�ameraResolution = camera;
}

Smartphone::Smartphone(const Smartphone &phone)            //����������� �����������
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->�ameraResolution = phone.�ameraResolution;
}

Smartphone::Smartphone(Smartphone && phone)                //����������� �����������
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->�ameraResolution = phone.�ameraResolution;
	phone.weight = phone.batteryCapacity = phone.�ameraResolution = 0;
}

Smartphone& Smartphone::operator=(const Smartphone& phone)   //�������� ������������
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		batteryCapacity = phone.batteryCapacity;
		�ameraResolution = phone.�ameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	}
	return *this;
}

Smartphone& Smartphone::operator=(Smartphone && phone)       //�������� ������������ �����������
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		phone.weight = 0;
		batteryCapacity = phone.batteryCapacity;
		�ameraResolution = phone.�ameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
		phone.batteryCapacity = 0;
		phone.�ameraResolution = 0;
	}
	return *this;
}

Smartphone::~Smartphone()                                  //����������
{}
//==========================================================================================

//=======================================������=============================================
void Smartphone::setTouchScreen(char* screen)              //����� ������� ���� ������
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
}
void Smartphone::setCameraResolution(int camera)           //����� ������� ���������� ������
{
	this->�ameraResolution = camera;
}
char* Smartphone::getTouchScreen()                  //����� ��������� ���� ������
{
	return this->touchScreen;
}
int Smartphone::getCameraResolution()               //����� ��������� ���������� ������
{
	return this->�ameraResolution;
}
//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const Smartphone& phone) //�������� << ��� ������
{
	out << "|" << setw(19) << left << phone.brand << "|"
		<< setw(9) << left << phone.weight << "|"
		<< setw(25) << left << phone.batteryCapacity << "|"
		<< setw(10) << left << phone.touchScreen << "|" 
		<< setw(21) << left << phone.�ameraResolution << "|" << endl;
	return out;
}
istream& operator>>(istream& in, Smartphone& phone)        //�������� >> ��� �����
{
	PortableCM PCM;
	cin >> PCM;
	rewind(stdin);
	strcpy_s(phone.brand, strlen(PCM.getBrand()) + 1, PCM.getBrand());
	phone.weight = PCM.getWeight();
	phone.batteryCapacity = PCM.getBatteryCapacity();
	cout << "������� ��� ������ ���������:" << endl;
	in.getline(phone.touchScreen, 80);
	rewind(stdin);
	cout << "������� ���������� ������ ���������(��):" << endl;
	cin >> phone.�ameraResolution;
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
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
		<< setw(17) << left << "|������� ������������, mAh" << setw(11) << left << "|��� ������"
		<< setw(22) << "|���������� ������, ��" << "|" << endl << "|";
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