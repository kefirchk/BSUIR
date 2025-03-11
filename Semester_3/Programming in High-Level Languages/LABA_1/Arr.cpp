#include "Arr.h"                  //����������� ���������� ������ Arr
#include "functions.h"            //����������� ���������� ��������������� �������

Arr::Arr() {                      //����������� �� ���������
	n = 0;                        //������ �������
	ms = nullptr;                 //��������� �� ������ ����� �����
}
Arr::Arr(int n) {                 //����������� � �����������
	ms = new int[n];              //��������� ������ ��� ������
	this->n = n;                  //��������� ������� �������
}
Arr::Arr(Arr const &m) {          //����������� �����������
	n = m.n;                      //����������� ������� �������
	ms = new int[n];              //��������� ������ ��� ������
	for (int i = 0; i < n; i++)   //����������� ��������� �������
		ms[i] = m.ms[i]; 
}
Arr& Arr::operator=(Arr const& m) //�������� ������������
{
	if (this != &m)
	{
		delete[] ms;              //������� ������ �� �������
		n = m.n;                  //������������ ������� �������
		ms = new int[n];          //�������� ������ �������
		for (int i = 0; i < n; i++) //�������� ��������� � ����� ������
			ms[i] = m.ms[i];
	}
	return *this;
}

Arr::~Arr() { delete[] ms; }    //����������

Arr Arr:: operator+(const Arr &m)
{
	Arr result(n + m.n);        //�������� �������(�������) ����������
	int real_length = 0;        //�������� ����� ������� ����������
	for (int i = 0; i < n; i++) //���� �� ������� �������
	{
		if (real_length && result.repeatCheck(real_length, ms[i]))
			continue;           //���� ����� ������� ��� �������, �� ���������� ���        
		result.ms[real_length++] = ms[i];   //������������ ��������
	}
	for (int i = 0; i < m.n; i++)//���� �� ������� �������
	{
		if (real_length && result.repeatCheck(real_length, m.ms[i])) 
			continue;           //���� ����� ������� ��� �������, �� ���������� ���        
		result.ms[real_length++] = m.ms[i]; //������������ ��������
	}
	result.n = real_length;     //������������� ������� �������
	//Arr goodmemres = result;    //�������� ������� � ����������� �������� ���������� ������
	//return goodmemres;          //������� ������� ������ �����������
	return result;
}

int Arr::repeatCheck(int real_length, int elem) //����� ��� �������� �� ���������� ���������
{
	for (int j = 0; j < real_length; j++)
	{
		if (ms[j] == elem)  //�������� �� ���������� ���������
			return 1;       //������� ����, ��� ����� ������� ��� ���� � �������� �������
	}
	return 0;               //������� �� ��� ������ � �������
}

void Arr::input() {                        //����� ����� ��������� �������
	for (int i = 0; i < n; i++)            //���� ��� ����� ��������� �������
		ms[i] = rightInput();              //����� ������� ����� ����� � ���������
}
void Arr::output() {                       //����� ������ �������
	for (int i = 0; i < n; i++)            //���� �� ������ ������� �� �����
		cout << ms[i] << " ";              //����� ���������� ��������
}

Arr Arr:: unite(Arr m)          //����� ����������� ��������
{
	Arr result(n + m.n);        //�������� �������(�������) ����������
	int real_length = 0;        //�������� ����� ������� ����������
	for (int i = 0; i < n; i++) //���� �� ������� �������
	{
		if (real_length && result.repeatCheck(real_length, ms[i]))
			continue;           //���� ����� ������� ��� �������, �� ���������� ���        
		result.ms[real_length++] = ms[i];   //������������ ��������
	}
	for (int i = 0; i < m.n; i++)//���� �� ������� �������
	{
		if (real_length && result.repeatCheck(real_length, m.ms[i]))
			continue;           //���� ����� ������� ��� �������, �� ���������� ���        
		result.ms[real_length++] = m.ms[i]; //������������ ��������
	}
	result.n = real_length;     //������������� ������� �������
	Arr goodmemres = result;    //�������� ������� � ����������� �������� ���������� ������
	return goodmemres;          //������� ������� ������ �����������
}

Arr Arr::operator&(const Arr& m)
{
	int maxlen;                //������, �� ������� ����� �������� ������
	if (n > m.n) maxlen = n;
	else maxlen = m.n;
	Arr result(maxlen);        //�������� �������(�������) ����������
	int real_length = 0;        //�������� ����� ������� ����������
	for (int i = 0; i < n; i++) //���� �� ������� �������
	{
		for (int j = 0; j < m.n; j++)
		{
			if (ms[i] == m.ms[j])
			{
				if (real_length && result.repeatCheck(real_length, ms[i]))
					continue;           //���� ����� ������� ��� �������, �� ���������� ���       
				result.ms[real_length++] = ms[i];   //������������ ��������		
			}
		}
	}
	result.n = real_length;     //������������� ������� �������
	Arr goodmemres = result;    //�������� ������� � ����������� �������� ���������� ������
	return goodmemres;          //������� ������� ������ �����������
}

//ostream& operator<<(ostream& out, const Arr& obj)
//{
//	out << obj.ms;
//	return out;
//}