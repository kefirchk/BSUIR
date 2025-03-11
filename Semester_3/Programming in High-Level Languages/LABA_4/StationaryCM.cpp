#include "Functions.h"

//======================================������������========================================
StationaryCM::StationaryCM()            //����������� ��� ����������
{
	strcpy_s(this->location, 1, "");
}

StationaryCM::StationaryCM(char* nameBrand, int w, char* nameLocation)  //����������� � �����������
{
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
}

StationaryCM::StationaryCM(const StationaryCM &SCM)            //����������� �����������
{
	strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
	strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	this->weight = SCM.weight;
}

StationaryCM::StationaryCM(StationaryCM && SCM)                //����������� �����������
{
	this->weight = SCM.weight;
	strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
	strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	SCM.weight = 0;
}

StationaryCM& StationaryCM::operator=(const StationaryCM& SCM) //�������� ������������
{
	if (this != &SCM)
	{
		strcpy_s(brand, strlen(SCM.brand) + 1, SCM.brand);
		weight = SCM.weight;
		strcpy_s(location, strlen(SCM.location) + 1, SCM.location);
	}
	return *this;
}

StationaryCM& StationaryCM::operator=(StationaryCM && SCM)     //�������� ������������ �����������
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

StationaryCM::~StationaryCM()                                  //����������
{}
//==========================================================================================

//=======================================������=============================================
void StationaryCM::setLocation(char* nameLocation)    //����� ������� ��������������
{
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
}
char* StationaryCM::getLocation()                     //����� ��������� ��������������
{
	return this->location;
}

//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const StationaryCM& SCM) //�������� << ��� ������
{
	out << dynamic_cast<const CountingMachine&>(SCM);
	out << setw(19) << left << SCM.location << "|";
	return out;
}
istream& operator>>(istream& in, StationaryCM& SCM)        //�������� >> ��� �����
{
	in >> dynamic_cast<CountingMachine&>(SCM);
	rewind(stdin);
	cout << "������� ��������������:" << endl;
	in.getline(SCM.location, 80);
	rewind(stdin);
	return in;
}
//==========================================================================================

void StationaryCM::beginOfTable()
{
	CountingMachine::beginOfTable();
	for (int i = 0; i < 20; i++)
		cout << "_";
}

void StationaryCM::outputHat()        //����� ����� ����� ������� ���������
{
	CountingMachine::outputHat();
	cout << setw(19) << left << "��������������" << "|";
}

//void StationaryCM::outputHat()        //����� ����� ����� ������� ���������
//{
//	cout << " ";
//	for (int i = 0; i < 49; i++)
//		cout << "_";
//	cout << endl;
//	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
//		<< setw(20) << left << "|��������������" << "|" << endl << "|";
//	for (int i = 0; i < 47; i++)
//	{
//		if (i == 19 || i == 28) cout << "|";
//		cout << "_";
//	}
//	cout << "|";
//}

//void StationaryCM::endOfTable()       //����� ������ ����� ������� ���������
//{
//	cout << endl;
//	for (int i = 0; i < 47; i++)
//	{
//		if (i == 0 || i == 19 || i == 28) cout << "|";
//		cout << "_";
//	}
//	cout << "|" << endl << endl;
//}

void StationaryCM::endOfHat()
{
	CountingMachine::endOfHat();
	for (int i = 0; i < 19; i++)
		cout << "_";
	cout << "|";
}

void StationaryCM::endOfTable()       //����� ������ ����� ������� ���������
{
	CountingMachine::endOfTable();
	for (int i = 0; i < 19; i++)
		cout << "_";
	cout << "|";
}