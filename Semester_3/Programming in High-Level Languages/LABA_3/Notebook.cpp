#include "Functions.h"

//======================================������������========================================
Notebook::Notebook()                                   //����������� ��� ����������
{
	weight = batteryCapacity = 0;
	keyboardBacklight = '-';
}

Notebook::Notebook(char* nameBrand, int w, int batCap, bool keyboardlight, char* type)  //����������� � �����������
{
	strcpy_s(brand, strlen(nameBrand) + 1, nameBrand);
	this->weight = w;
	this->batteryCapacity = batCap;
	strcpy_s(typeOfNotebook, strlen(type) + 1, type);
	this->keyboardBacklight = keyboardlight;
}

Notebook::Notebook(const Notebook &notebook)            //����������� �����������
{
	strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
	this->weight = notebook.weight;
	this->batteryCapacity = notebook.batteryCapacity;
	strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	this->keyboardBacklight = notebook.keyboardBacklight;
}

Notebook::Notebook(Notebook && notebook)                //����������� �����������
{
	strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
	this->weight = notebook.weight;
	this->batteryCapacity = notebook.batteryCapacity;
	strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	this->keyboardBacklight = notebook.keyboardBacklight;
	notebook.weight = notebook.batteryCapacity = 0;
	notebook.keyboardBacklight = '-';
}

Notebook& Notebook::operator=(const Notebook& notebook)   //�������� ������������
{
	if (this != &notebook)
	{
		strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
		weight = notebook.weight;
		batteryCapacity = notebook.batteryCapacity;
		keyboardBacklight = notebook.keyboardBacklight;
		strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	}
	return *this;
}

Notebook& Notebook::operator=(Notebook && notebook)       //�������� ������������ �����������
{
	if (this != &notebook)
	{
		strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
		weight = notebook.weight;
		notebook.weight = 0;
		batteryCapacity = notebook.batteryCapacity;
		keyboardBacklight = notebook.keyboardBacklight;
		strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
		notebook.batteryCapacity = 0;
		notebook.keyboardBacklight = '-';
	}
	return *this;
}

Notebook::~Notebook()                                  //����������
{}
//==========================================================================================

//=======================================������=============================================
void Notebook::setKeyboardBacklight(char keyboardlight)  //����� ������� ������� ��������� ����������
{
	this->keyboardBacklight = keyboardlight;
}
void Notebook::setTypeOfNotebook(char* type)             //����� ������� ���� ��������
{
	strcpy_s(typeOfNotebook, strlen(type) + 1, type);
}
bool Notebook::getKeyboardBacklight()             //����� ��������� ������ � ������� ��������� ����������
{
	return this->keyboardBacklight;
}
char* Notebook::getTypeOfNotebook()               //����� ��������� ���� ��������
{
	return this->typeOfNotebook;
}
//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const Notebook& notebook) //�������� << ��� ������
{
	out << "|" << setw(19) << left << notebook.brand << "|"
		<< setw(9) << left << notebook.weight << "|"
		<< setw(25) << left << notebook.batteryCapacity << "|" 
		<< setw(19) << left << notebook.typeOfNotebook << "|"
		<< setw(14) << setfill(' ') << right << notebook.keyboardBacklight << setw(15) << "|" << endl;
	return out;
}
istream& operator>>(istream& in, Notebook& notebook)        //�������� >> ��� �����
{
	PortableCM PCM;
	cin >> PCM;
	rewind(stdin);
	strcpy_s(notebook.brand, strlen(PCM.getBrand()) + 1, PCM.getBrand());
	notebook.weight = PCM.getWeight();
	cout << "������� ������� ������� ��������� ����������('+' - ����, '-' - ���):" << endl;
	cin >> notebook.keyboardBacklight;
	rewind(stdin);
	cout << "������� ��� ��������:" << endl;
	in.getline(notebook.typeOfNotebook, 80);
	rewind(stdin);
	return in;
}
//==========================================================================================

void Notebook::outputHat()
{
	cout << " ";
	for (int i = 0; i < 104; i++)
		cout << "_";
	cout << endl;
	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
		<< setw(17) << left << "|������� ������������, mAh" << setw(20) << left << "|��� ��������"
		<< setw(25) << "|������� ��������� ����������" << "|" << endl << "|";
	for (int i = 0; i < 100; i++)
	{
		if (i == 19 || i == 28 || i == 53 || i == 72) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}

void Notebook::endOfTable()
{
	for (int i = 0; i < 100; i++)
	{
		if (i == 0 || i == 19 || i == 28 || i == 53 || i == 72) cout << "|";
		cout << "_";
	}
	cout << "|" << endl;
}