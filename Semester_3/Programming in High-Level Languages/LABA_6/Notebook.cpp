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

Notebook::Notebook(const Notebook& notebook)            //����������� �����������
{
	strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
	this->weight = notebook.weight;
	this->batteryCapacity = notebook.batteryCapacity;
	strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	this->keyboardBacklight = notebook.keyboardBacklight;
}

Notebook::Notebook(Notebook&& notebook)                //����������� �����������
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

Notebook& Notebook::operator=(Notebook&& notebook)       //�������� ������������ �����������
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
			return false;
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
	out << setw(19) << left << notebook.typeOfNotebook << "|"
		<< setw(14) << setfill(' ') << right << notebook.keyboardBacklight << setw(15) << "|";
	return out;
}
istream& operator>>(istream& in, Notebook& notebook)        //�������� >> ��� �����
{
	in >> dynamic_cast<PortableCM&>(notebook);
	rewind(stdin);
	cout << "������� ������� ������� ��������� ����������('+' - ����, '-' - ���):" << endl;
	notebook.keyboardBacklight = get_char('+', '-');
	rewind(stdin);
	cout << "������� ��� ��������:" << endl;
	char* str = get_str(in);
	strcpy_s(notebook.typeOfNotebook, strlen(str) + 1, str);
	rewind(stdin);
	return in;
}

ofstream& operator<<(ofstream& fout, const Notebook& notebook) //�������� << ��� ������
{
	fout << dynamic_cast<const PortableCM&>(notebook);
	fout << setw(19) << left << notebook.typeOfNotebook << '|'
		<< setw(14) //<< setfill(' ') 
		<< right << notebook.keyboardBacklight << '\n'; //<< setw(15);//<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, Notebook& notebook)        //�������� >> ��� �����
{
	fin >> dynamic_cast<PortableCM&>(notebook);
	//fin >>  notebook.typeOfNotebook >> notebook.keyboardBacklight;
	fin.getline(notebook.typeOfNotebook, 80, '|');
	skip_spaces(fin);
	fin >> notebook.keyboardBacklight;
	return fin;
}

fstream& operator>>(fstream& fin, Notebook& notebook)
{
	fin.read(reinterpret_cast<char*>(&notebook), sizeof(Notebook));
	return fin;
}

fstream& operator<<(fstream& fout, const Notebook& notebook)
{
	fout.write(reinterpret_cast<const char*>(&notebook), sizeof(Notebook));
	return fout;
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
		choice = get_int(1, 6); //���� ������ ���������� ���������
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
		choice = get_int(1, 6); //���� ������ ��������� ������
		this->set_parametres(choice);  //��������� ����������
	} while (choice != 6);
}

void Notebook::set_parametres(int choice) //����� ��������� ����������
{
	Interface<int> text;
	rewind(stdin);       //������� ������
	switch (choice)
	{
	case 1:
		cout << "������� �������� �������������:" << endl;
		this->setBrand(get_str(cin));
		break;
	case 2:
		cout << "������� ���:" << endl;
		this->setWeight(get_int(0, INT_MAX));
		break;
	case 3:
		cout << "������� ������� ������������:" << endl;
		this->setBatteryCapacity(get_int(0, INT_MAX));
		break;
	case 4:
		cout << "������� ������� ��������� ����������('+' - ����, '-' - ���):" << endl;
		this->setKeyboardBacklight(get_char('+', '-'));
		break;
	case 5:
		cout << "������� ��� ��������:" << endl;
		this->setTypeOfNotebook(get_str(cin));
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