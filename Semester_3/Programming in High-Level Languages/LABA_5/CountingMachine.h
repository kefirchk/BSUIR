#pragma once
class CountingMachine //����� "�������������� ������"
{
protected:
	char brand[80];   //�������������
	int weight;       //���
public:
	CountingMachine();                            //����������� ��� ����������
	CountingMachine(char* name, int w);           //����������� � �����������
	CountingMachine(const CountingMachine& CM);   //����������� �����������
	CountingMachine(CountingMachine&& CM);       //����������� �����������
	~CountingMachine();                           //����������

	CountingMachine& operator=(const CountingMachine& CM);   //�������� ������������
	CountingMachine& operator=(CountingMachine&& CM);       //�������� ������������ �����������

	void setBrand(char*);  //����� ������� �������� �����
	void setWeight(int);   //����� ������� ����
	char* getBrand();      //����� ��������� �������� �����
	int getWeight();       //����� ��������� ����

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const CountingMachine& CM); //�������� << ��� ������
	friend istream& operator>>(istream& in, CountingMachine& CM);        //�������� >> ��� �����
};