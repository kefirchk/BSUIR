#include "Functions.h"

//======================================������������========================================
StationaryCM::StationaryCM()                                   //����������� ��� ����������
{
	weight = 0;
}

StationaryCM::StationaryCM(char* nameBrand, int w, char* nameLocation)  //����������� � �����������
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	strcpy_s(location, strlen(nameLocation) + 1, nameLocation);
	this->weight = w;
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
	out << "|" << setw(19) << left << SCM.brand << "|" 
		<< setw(9) << left << SCM.weight << "|"
		<< setw(19) << left << SCM.location << "|" << endl;
	return out;
}
istream& operator>>(istream& in, StationaryCM& SCM)        //�������� >> ��� �����
{
	CountingMachine CM;
	cin >> CM;
	rewind(stdin);
	cout << "������� ��������������:" << endl;
	in.getline(SCM.location, 80);
	rewind(stdin);
	strcpy_s(SCM.brand, strlen(CM.getBrand()) + 1, CM.getBrand());
	SCM.weight = CM.getWeight();
	rewind(stdin);
	return in;
}
//==========================================================================================

void StationaryCM::outputHat()
{
	cout << " ";
	for (int i = 0; i < 49; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
		<< setw(20) << left << "|��������������" << "|" << endl << "|";
	for (int i = 0; i < 47; i++)
	{
		if (i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void StationaryCM::endOfTable()
{
	for (int i = 0; i < 47; i++)
	{
		if (i == 0 || i == 19 || i == 28) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}