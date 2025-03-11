#pragma once
#include <iostream>
using namespace std;

class Arr {   //����� "������"
public:
	Arr();                             //����������� �� ���������
	explicit Arr(int n);               //����������� � �����������
	~Arr();                            //����������
	Arr(Arr const &m);                 //����������� �����������
	Arr& operator=(Arr const& m);      //�������� ������������
	Arr operator+(const Arr &m);       //�������� ����������� ��������

	Arr unite(Arr m);                  //����� ����������� ��������
	Arr operator&(const Arr& m);
	void input();                      //����� ����� ��������� �������
	void output();                     //����� ������ �������
	int repeatCheck(int rl, int elem); //����� ��� �������� �� ���������� ���������

	//friend ostream& operator<<(ostream& out, const Arr& obj);

private:
	int *ms;  //��������� �� ������
	int n;    //������ �������
};