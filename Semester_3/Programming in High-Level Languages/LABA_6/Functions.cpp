#include "Functions.h"
#include "Exception.h"
#include "Interface.cpp"
#define LANGUAGE 0  //1 - �������, 0 - ���������� ����

int get_int(int min, int max)
{
	Interface<char> temp;
	int value;            //��������� ���������� ��� ����� �����
	temp.setColor(8);     //�����
	cout << "(����� ����� � �������� [" << min << ", " << max << "])" << endl;
	temp.setColor(7);     //�����
	do
	{
		try
		{
			rewind(stdin);     //������� ������ �����
			cin >> value;      //���� ��������
			if (!cin)
				throw InputException(1, "������ �����!", "������� �� ����� �����.\n������� ������ ����� �����");
			else if (value > max || value < min)
				throw InputException(2, "������ �����!", "����� �� ������� ���������.\n������� ������ ����� � ��������� ���������");
			else if (cin.peek() != '\n')
				throw InputException(3, "������ �����!", "������������ ������ �����.\n��������� ���� ��� ������ �������� ����� �����");
			return value;
		}
		catch (InputException obj)
		{
			obj.what();        //����� ������ �� ������
			cin.clear();       //�������� ���� ������
		}
	} while (1);
}

char get_char(char first, char second)
{
	char value;                //��������� ���������� ��� �����
	do
	{
		try
		{
			rewind(stdin);     //������� ������ �����
			cin >> value;      //����� �������
			if (value != first && value != second)   //�������� �� ������������ ����� �������
				throw InputException(4, "������ �����!", "����� �� ������� ���������.\n������� ������ ��������� �������");
			if (cin.peek() != '\n')
				throw InputException(3, "������ �����!", "������������ ������ �����.\n������� ������ ���� ������");
			return value;
		}
		catch (InputException obj)
		{
			obj.what();        //����� ������ �� ������
			cin.clear();       //�������� ���� ������
		}
	} while (1);
}

char* get_str(istream& in)
{
	Interface<char> temp;
	temp.setColor(8);     //�����
	char* str = new char[80];
	if (LANGUAGE == 1) cout << "(�� ������� �����)" << endl;
	else if (LANGUAGE == 0) cout << "(�� ���������� �����)" << endl;
	temp.setColor(7);     //�����
	do
	{
		try
		{
			rewind(stdin);          //������� ������
			in.getline(str, 80);
			if (!in.good())
				throw InputException(3, "������ �����!", "������������ ������ �����.\n������� ������ �� ����� < 80");
			else if (!strlen(str))
				throw InputException(6, "������ �����!", "������ �� �������.\n������� ������");
			if (LANGUAGE == 0)      //������ ���� ���������� �����
			{
				for (size_t i = 0; i < strlen(str); i++)
				{
					if ((str[i] >= '�' && str[i] <= '�') || (str[i] >= '�' && str[i] <= '�'))
						throw InputException(7, "������ �����!", "������� ������� �����.\n������� ������, ��������� ������ ���������� �����");
				}
				return str;
			}
			else if (LANGUAGE == 1) //������ ���� ������� �����
			{
				for (size_t i = 0; i < strlen(str); i++)
				{
					if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
						throw InputException(8, "������ �����!", "������� ���������� �����.\n������� ������, ��������� ������ ������� �����");
				}
				return str;
			}
		}
		catch (InputException obj)
		{
			obj.what();        //����� ������ �� ������
			cin.clear();       //�������� ���� ������
		}
	} while (1);
}

void skip_spaces(ifstream& fin)
{
	char s;
	while (!fin.eof())
	{
		fin >> s;
		if (s != ' ')
			break;
	}
	fin.seekg(-1, ios::cur);
}
