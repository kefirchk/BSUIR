#include "Interface.cpp"

//======================================������������========================================
Notebook::Notebook()                                   //����������� ��� ����������
{
	strcpy_s(this->typeOfNotebook, 1, "");
	keyboardBacklight = '?';
}

Notebook::Notebook(char* nameBrand, int w, int batCap, char keyboardlight, char* type)  //����������� � �����������
{
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

bool Notebook::operator==(Notebook& notebook)         //�������� ����� ��� ��������� ��������� ��� ������
{
	bool ok = false;
	if (notebook.getBatteryCapacity())
		if (this->batteryCapacity == notebook.getBatteryCapacity())
			ok = true;
		else return false;
	if (notebook.getWeight())
		if (this->weight == notebook.getWeight())
			ok = true;
		else return false;
	if (strcmp(notebook.getBrand(), ""))
		if (!strcmp(this->brand, notebook.getBrand()))
			ok = true;
		else return false;
	if (strcmp(notebook.getTypeOfNotebook(), ""))
		if (!strcmp(this->typeOfNotebook, notebook.getTypeOfNotebook()))
			ok = true;
		else
			return false;
	if (notebook.getKeyboardBacklight() != '?')
		if (this->keyboardBacklight == notebook.getKeyboardBacklight())
			ok = true;
		else
			ok = false;
	return ok;
}

Notebook::~Notebook()                                    //����������
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
char Notebook::getKeyboardBacklight()             //����� ��������� ������ � ������� ��������� ����������
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
	out << dynamic_cast<const PortableCM&>(notebook);
	out	<< setw(19) << left << notebook.typeOfNotebook << "|"
		<< setw(14) << setfill(' ') << right << notebook.keyboardBacklight << setw(15) << "|";
	return out;
}
istream& operator>>(istream& in, Notebook& notebook)        //�������� >> ��� �����
{
	in >> dynamic_cast<PortableCM&>(notebook);
	rewind(stdin);
	cout << "������� ������� ������� ��������� ����������('+' - ����, '-' - ���):" << endl;
	cin >> notebook.keyboardBacklight;
	rewind(stdin);
	cout << "������� ��� ��������:" << endl;
	in.getline(notebook.typeOfNotebook, 80);
	rewind(stdin);
	return in;
}
//==========================================================================================

void Notebook::beginOfTable()
{
	PortableCM::beginOfTable();
	for (int i = 0; i < 49; i++)
		cout << "_";
}

void Notebook::outputHat()           //����� ������ ����� ������� ���������
{
	PortableCM::outputHat();
	cout << setw(19) << left << "��� ��������"
		<< setw(25) << "|������� ��������� ����������" << "|";
}

void Notebook::endOfHat()
{
	PortableCM::endOfHat();
	for (int i = 0; i < 47; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Notebook::endOfTable() //����� ������ ����� ������� ���������
{
	PortableCM::endOfTable();
	for (int i = 0; i < 47; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

//void Notebook::outputHat()           //����� ������ ����� ������� ���������
//{
//	cout << " ";
//	for (int i = 0; i < 104; i++)
//		cout << "_";
//	cout << endl;
//	cout << setw(20) << left << "|�������������" << setw(10) << left << "|���, �"
//		<< setw(17) << left << "|������� ������������, mAh" << setw(20) << left << "|��� ��������"
//		<< setw(25) << "|������� ��������� ����������" << "|" << endl << "|";
//	for (int i = 0; i < 100; i++)
//	{
//		if (i == 19 || i == 28 || i == 53 || i == 72) cout << "|";
//		cout << "_";
//	}
//	cout << "|";
//}
//
//void Notebook::endOfTable() //����� ������ ����� ������� ���������
//{
//	cout << endl;
//	for (int i = 0; i < 100; i++)
//	{
//		if (i == 0 || i == 19 || i == 28 || i == 53 || i == 72) cout << "|";
//		cout << "_";
//	}
//	cout << "|" << endl << endl;
//}

void Notebook::edit()        //����� �������������� ���������� �������
{
	Interface<int> text;
	int choice;              //��������� �������� ��� �������������� 
	do {
		rewind(stdin);       //������� ������
		text.setColor(13);   //�������
		cout << "�������� �����:" << endl;
		text.setColor(15);   //����-�����
		cout << "1 - �������� �������� �������������" << endl;
		cout << "2 - �������� ���" << endl;
		cout << "3 - �������� ������� ������������" << endl;
		cout << "4 - �������� ������ ��������� ����������" << endl;
		cout << "5 - �������� ��� ��������" << endl;
		text.setColor(10);   //����-�������
		cout << "6 - ���������" << endl;
		text.setColor(7);    //�����
		cin >> choice;       //���� ������ ���������� ���������
		this->set_parametres(choice); //��������� ����������
	} while (choice != 6);
	cout << endl;
}

void Notebook::choose_search_parametres()   //����� ������ ���������� ������
{
	Interface<int> text;
	int choice;              //����� ���������
	do {
		rewind(stdin);       //������� ������
		text.setColor(13);   //�������
		cout << endl << "�������� ��������� ������." << endl;
		text.setColor(15);   //����-�����
		cout << "1 - �������� �������������" << endl;
		cout << "2 - ���" << endl;
		cout << "3 - ������� ������������" << endl;
		cout << "4 - ������� ��������� ����������" << endl;
		cout << "5 - ��� ��������" << endl;
		text.setColor(10);   //����-�������
		cout << "6 - �����" << endl;
		text.setColor(7);    //�����
		cin >> choice;       //���� ������ ��������� ������
		this->set_parametres(choice);  //��������� ����������
	} while (choice != 6);
}

void Notebook::set_parametres(int choice) //����� ��������� ����������
{
	Interface<int> text;
	char buffer[80], y;  //����� ��� �����, ��������� ���������� ��� ������ ���������� �����
	int x;               //��������� ���������� ��� ����� �����
	rewind(stdin);       //������� ������
	switch (choice)
	{
	case 1:
		cout << "������� �������� �������������:" << endl;
		cin.getline(buffer, 80);
		this->setBrand(buffer);
		break;
	case 2:
		cout << "������� ���:" << endl;
		cin >> x;
		this->setWeight(x);
		break;
	case 3:
		cout << "������� ������� ������������:" << endl;
		cin >> x;
		this->setBatteryCapacity(x);
		break;
	case 4:
		cout << "������� ������� ��������� ����������:" << endl;
		cin >> y;
		this->setKeyboardBacklight(y);
		break;
	case 5:
		cout << "������� ��� ��������:" << endl;
		cin.getline(buffer, 80);
		this->setTypeOfNotebook(buffer);
		break;
	case 6: break;
	default: 
		text.setColor(12);     //����-�������
		cout << endl << "������ ������!" << endl;
		text.setColor(7);      //�����
		break;
	}
}

void Notebook::outputClassName() //����� ������ �������� ������
{
	cout << setw(40) << right << "����� << ������� >>" << endl << endl;
}