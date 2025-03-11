#include "Functions.h"

//======================================������������========================================
CountingMachine::CountingMachine()                           //����������� ��� ����������
{
	strcpy_s(brand, 1, "");
	weight = 0;
}
CountingMachine::CountingMachine(char* name, int w)          //����������� � �����������
{
	strcpy_s(brand, strlen(name) + 1, name);
	this->weight = w;
}

CountingMachine::CountingMachine(const CountingMachine& CM)  //����������� �����������
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	this->weight = CM.weight;
}

CountingMachine::CountingMachine(CountingMachine&& CM)       //����������� �����������
	: weight(CM.weight)
{
	strcpy_s(brand, strlen(CM.brand) + 1, CM.brand);
	strcpy_s(CM.brand, 1, "");
	CM.weight = 0;
}

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

CountingMachine& CountingMachine::operator=(CountingMachine&& CM)       //�������� ������������ �����������
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
	out << "|" << setw(19) << left << CM.brand << "|" << setw(9) << left << CM.weight << "|";
	return out;
}
istream& operator>>(istream& in, CountingMachine& CM)        //�������� >> ��� �����
{
	rewind(stdin);
	cout << "������� �������� �������������:" << endl;
	char *str = get_str(in);
	strcpy_s(CM.brand, strlen(str) + 1, str);
	rewind(stdin);
	cout << "������� ���(�):" << endl;
	CM.weight = get_int(1, SHRT_MAX);
	rewind(stdin);
	return in;
}
//==========================================================================================

void CountingMachine::beginOfTable()
{
	cout << " ";
	for (int i = 0; i < 29; i++)
		cout << "_";
}

void CountingMachine::outputHat()  //����� ����� ������� ��������� ������
{
	cout << endl << setw(20) << left << "|�������������" << setw(10) << left << "|���, �" << "|";
}

void CountingMachine::endOfHat()
{
	cout << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void CountingMachine::endOfTable() //����� ����� ������� ��������� ������
{
	cout << endl << "|";
	for (int i = 0; i < 28; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}