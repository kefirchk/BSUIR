#include <iostream>    //����������� ���������� ������ �����-������
using namespace std;   //������������� ������������ ��� std

char proceed()         //������� ����������� ������ ���������   
{
	char c;            //��������� ����������
	while (1) {
		cout << "\n���������� ���������� ���������?(y/n)";
		cin >> c;
		if (c == 'y' || c == 'n') return c;
		else cout << "������!";
	}
}


//char*& operator+(const char* s1, const char* s2);  //�������� + (const char[] + const char[])
