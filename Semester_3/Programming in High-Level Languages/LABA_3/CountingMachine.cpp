#include "Functions.h"

//======================================������������========================================
CountingMachine::CountingMachine()                           //����������� ��� ����������
{
	weight = 0;
}

CountingMachine::CountingMachine(char* name, int w)          //����������� � �����������
{
	strcpy_s(brand, strlen(name) + 1, name);
	this->weight = w;
}

CountingMachine::CountingMachine(const CountingMachine &CM)  //����������� �����������
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	this->weight = CM.weight;
}

CountingMachine::CountingMachine(CountingMachine && CM)      //����������� �����������
	: weight(CM.weight)
{   weight = 0;  }

CountingMachine::~CountingMachine()                          //����������
{}

CountingMachine& CountingMachine::operator=(const CountingMachine& CM)   //�������� ������������
{
	if (this != &CM)
	{
		strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
		weight = CM.weight;
	}
	return *this;
}

CountingMachine& CountingMachine::operator=(CountingMachine && CM)       //�������� ������������ �����������
{
	if (this != &CM)
	{
		strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
		weight = CM.weight;
		CM.weight = 0;
	}
	return *this;
}
//==========================================================================================

//=======================================������=============================================
void CountingMachine::setBrand(char* name)    //����� ������� �������� �����
{
	strcpy_s(brand, strlen(name) + 1, name);
}
void CountingMachine::setWeight(int w)        //����� ������� ����
{
	this->weight = w;
}
char* CountingMachine::getBrand()             //����� ��������� �������� �����
{
	return this->brand;
}
int CountingMachine::getWeight()              //����� ��������� ����
{
	return this->weight;
}
//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const CountingMachine& CM) //�������� << ��� ������
{
	out << "|" << setw(19) << left << CM.brand << "|" << setw(9) << left << CM.weight << "|" << endl;
	return out;
}
istream& operator>>(istream& in, CountingMachine& CM)        //�������� >> ��� �����
{
	cout << "������� �������� �������������:" << endl;
	in.getline(CM.brand, 80);
	rewind(stdin);
	cout << "������� ���(�):" << endl;
	in >> CM.weight;
	rewind(stdin);
	return in;
}
//==========================================================================================

void CountingMachine::outputHat()
{
	cout << " ";
	for (int i = 0; i < 29; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �" << "|" << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void CountingMachine::endOfTable()
{
	for (int i = 0; i < 28; i++)
	{
		if (i == 0 || i == 19) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}