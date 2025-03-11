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

	void setBrand(const char*);  //����� ������� �������� �����
	void setWeight(int);   //����� ������� ����
	char* getBrand();      //����� ��������� �������� �����
	int getWeight();       //����� ��������� ����

	virtual void beginOfTable(); //����� ������ ������ �������
	virtual void outputHat();  //����� �������
	virtual void endOfHat();   //����� �����
	virtual void endOfTable(); //����� �������(����������)

	friend ostream& operator<<(ostream& out, const CountingMachine& CM); //�������� << ��� ������
	friend istream& operator>>(istream& in, CountingMachine& CM);        //�������� >> ��� �����
	friend ifstream& operator>>(ifstream& fin, CountingMachine& CM);
	friend ofstream& operator<<(ofstream& fout, const CountingMachine& CM);
	friend fstream& operator>>(fstream& fin, CountingMachine& CM);
	friend fstream& operator<<(fstream& fout, const CountingMachine& CM);
};