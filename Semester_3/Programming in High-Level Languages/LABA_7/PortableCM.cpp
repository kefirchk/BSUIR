#include "Functions.h"

//======================================������������========================================
PortableCM::PortableCM()                                   //����������� ��� ����������
{
	batteryCapacity = 0;
}

PortableCM::PortableCM(char* nameBrand, int w, int batCap) //����������� � �����������
{
	this->batteryCapacity = batCap;
}

PortableCM::PortableCM(const PortableCM& PCM)              //����������� �����������
{
	strcpy_s(brand, strlen(PCM.brand) + 1, PCM.brand);
	this->weight = PCM.weight;
	this->batteryCapacity = PCM.batteryCapacity;
}

PortableCM::PortableCM(PortableCM&& PCM)                  //����������� �����������
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

PortableCM& PortableCM::operator=(PortableCM&& PCM)       //�������� ������������ �����������
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
	out << dynamic_cast<const CountingMachine&>(PCM);
	out << setw(25) << left << PCM.batteryCapacity << "|";
	return out;
}
istream& operator>>(istream& in, PortableCM& PCM)        //�������� >> ��� �����
{
	in >> dynamic_cast<CountingMachine&>(PCM);
	rewind(stdin);
	cout << "������� ������� ������������(mAh):" << endl;
	PCM.batteryCapacity = get_int(2000, 100000);
	rewind(stdin);
	return in;
}

ofstream& operator<<(ofstream& fout, const PortableCM& PCM) //�������� << ��� ������
{
	fout << dynamic_cast<const CountingMachine&>(PCM);
	fout << setw(25) << left << PCM.batteryCapacity;//<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, PortableCM& PCM)        //�������� >> ��� �����
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

void PortableCM::outputHat()     //����� ��� ������ ����� ������� ���������
{
	CountingMachine::outputHat();
	cout << setw(16) << left << "������� ������������, mAh" << "|";
}

void PortableCM::endOfHat()
{
	CountingMachine::endOfHat();
	for (int i = 0; i < 25; i++)
		cout << "_";
	cout << "|";
}

void PortableCM::endOfTable()     //����� ��� ������ ����� ������� ���������
{
	CountingMachine::endOfTable();
	for (int i = 0; i < 25; i++)
		cout << "_";
	cout << "|";
}
