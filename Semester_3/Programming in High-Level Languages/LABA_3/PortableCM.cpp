#include "Functions.h"

//======================================������������========================================
PortableCM::PortableCM()                                   //����������� ��� ����������
{
	weight = batteryCapacity = 0;
}

PortableCM::PortableCM(char* nameBrand, int w, int batCap)  //����������� � �����������
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	this->weight = w;
	this->batteryCapacity = batCap;
}

PortableCM::PortableCM(const PortableCM &PCM)            //����������� �����������
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
}

PortableCM::PortableCM(PortableCM && PCM)                //����������� �����������
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
	PCM.weight = PCM.batteryCapacity = 0;
}

PortableCM& PortableCM::operator=(const PortableCM& PCM)   //�������� ������������
{
	if (this != &PCM)
	{
		strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
		weight = PCM.weight;
		batteryCapacity = PCM.batteryCapacity;
	}
	return *this;
}

PortableCM& PortableCM::operator=(PortableCM && PCM)       //�������� ������������ �����������
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

PortableCM::~PortableCM()                                  //����������
{}
//==========================================================================================

//=======================================������=============================================
void PortableCM::setBatteryCapacity(int batCap)    //����� ������� ������� ������������
{
	this->batteryCapacity = batCap;
}
int PortableCM::getBatteryCapacity()               //����� ��������� ������� ������������
{
	return this->batteryCapacity;
}

//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const PortableCM& PCM) //�������� << ��� ������
{
	out << "|" << setw(19) << left << PCM.brand << "|"
		<< setw(9) << left << PCM.weight << "|"
		<< setw(25) << left << PCM.batteryCapacity << "|" << endl;
	return out;
}
istream& operator>>(istream& in, PortableCM& PCM)        //�������� >> ��� �����
{
	CountingMachine CM;
	cin >> CM;
	rewind(stdin);
	strcpy_s(PCM.brand, strlen(CM.getBrand()) + 1, CM.getBrand());
	PCM.weight = CM.getWeight();
	cout << "������� ������� ������������(mAh):" << endl;
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
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
		<< setw(17) << left << "|������� ������������, mAh" << "|" << endl << "|";
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