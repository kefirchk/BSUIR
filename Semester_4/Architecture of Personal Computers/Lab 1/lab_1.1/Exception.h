#pragma once
class Exception
{
protected:
	int code;             //��� ������
	char error_msg[40];   //��������� �� ������
public:
	Exception(int, const char*);   //�����������
	int getErrorCode();   //�������� ��� ������
	~Exception();         //����������
	virtual void what();  //����� ������ ������ � �� ����� � �����������
};
