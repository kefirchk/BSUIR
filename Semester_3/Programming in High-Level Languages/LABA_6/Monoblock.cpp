#include "Interface.cpp"

//======================================������������========================================
Monoblock::Monoblock()                                   //����������� ��� ����������
{
	strcpy_s(this->mouse, 1, "");
	strcpy_s(this->keyboard, 1, "");
}

Monoblock::Monoblock(char* nameBrand, int w, char* nameLocation, char* nameMouse, char* nameKeyboard)  //����������� � �����������
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}

Monoblock::Monoblock(const Monoblock& MonoB)            //����������� �����������
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	this->weight = MonoB.weight;
}

Monoblock::Monoblock(Monoblock&& MonoB)                //����������� �����������
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	this->weight = MonoB.weight;
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	MonoB.weight = 0;
}

Monoblock& Monoblock::operator=(const Monoblock& MonoB)   //�������� ������������
{
	if (this != &MonoB)
	{
		strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
		weight = MonoB.weight;
		strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
		strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
		strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	}
	return *this;
}

Monoblock& Monoblock::operator=(Monoblock&& MonoB)       //�������� ������������ �����������
{
	if (this != &MonoB)
	{
		strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
		weight = MonoB.weight;
		MonoB.weight = 0;
		strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
		strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
		strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	}
	return *this;
}

bool Monoblock::operator==(Monoblock& monoblock)          //�������� ����� ��� ������ ���������
{
	bool ok = false;
	if (strcmp(monoblock.getLocation(), ""))
		if (!strcmp(this->location, monoblock.getLocation()))
			ok = true;
		else return false;
	if (monoblock.getWeight())
		if (this->weight == monoblock.getWeight())
			ok = true;
		else return false;
	if (strcmp(monoblock.getBrand(), ""))
		if (!strcmp(this->brand, monoblock.getBrand()))
			ok = true;
		else return false;
	if (strcmp(monoblock.getKeyboard(), ""))
		if (!strcmp(this->keyboard, monoblock.getKeyboard()))
			ok = true;
		else
			return false;
	if (strcmp(monoblock.getMouse(), ""))
		if (!strcmp(this->mouse, monoblock.getMouse()))
			ok = true;
		else
			return false;
	return ok;
}

Monoblock::~Monoblock()                          //����������
{}
//==========================================================================================

//=======================================������=============================================
void Monoblock::setMouse(char* nameMouse)        //����� ������� �������� �����
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
}
void Monoblock::setKeyboard(char* nameKeyboard)  //����� ������� �������� ����������
{
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}
char* Monoblock::getMouse()                      //����� ��������� �������� �����
{
	return this->mouse;
}
char* Monoblock::getKeyboard()                   //����� ��������� �������� ����������
{
	return this->keyboard;
}

//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const Monoblock& MonoB) //�������� << ��� ������
{
	out << dynamic_cast<const StationaryCM&>(MonoB);
	out << setw(19) << left << MonoB.mouse << "|"
		<< setw(19) << left << MonoB.keyboard << "|";
	return out;
}
istream& operator>>(istream& in, Monoblock& MonoB)        //�������� >> ��� �����
{
	in >> dynamic_cast<StationaryCM&>(MonoB);
	rewind(stdin);
	cout << "������� �������� ������������ ����:" << endl;
	char* str = get_str(in);
	strcpy_s(MonoB.mouse, strlen(str) + 1, str);
	rewind(stdin);
	cout << "������� �������� ����������:" << endl;
	str = get_str(in);
	strcpy_s(MonoB.keyboard, strlen(str) + 1, str);
	rewind(stdin);
	return in;
}

ifstream& operator>>(ifstream& fin, Monoblock& MonoB)
{
	fin >> dynamic_cast<StationaryCM&>(MonoB);
	//fin >> MonoB.mouse >> MonoB.keyboard;
	fin.getline(MonoB.mouse, 80, '|');
	fin.getline(MonoB.keyboard, 80, '|');
	return fin;
}

ofstream& operator<<(ofstream& fout, const Monoblock& MonoB)
{
	fout << dynamic_cast<const StationaryCM&>(MonoB);
	fout << setw(19) << left << MonoB.mouse << '|'
		<< setw(19) << left << MonoB.keyboard << '|' << '\n';
	return fout;
}

fstream& operator>>(fstream& fin, Monoblock& monoblock)
{
	fin.read(reinterpret_cast<char*>(&monoblock), sizeof(Monoblock));
	return fin;
}

fstream& operator<<(fstream& fout, const Monoblock& monoblock)
{
	fout.write(reinterpret_cast<const char*>(&monoblock), sizeof(Monoblock));
	return fout;
}
//==========================================================================================

void Monoblock::beginOfTable()
{
	StationaryCM::beginOfTable();
	for (int i = 0; i < 40; i++)
		cout << "_";
}

void Monoblock::outputHat()     //����� ������ ����� ������� ���������
{
	StationaryCM::outputHat();
	cout << setw(19) << left << "������������ ����"
		<< setw(20) << left << "|����������" << "|";
}

void Monoblock::endOfHat()
{
	StationaryCM::endOfHat();
	for (int i = 0; i < 38; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Monoblock::endOfTable()    //����� ������ ����� ������� ���������
{
	StationaryCM::endOfTable();
	for (int i = 0; i < 38; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Monoblock::edit()          //����� �������������� ���������� �������
{
	Interface<int> text;
	int choice;                 //����� ��������� �������
	do {
		rewind(stdin);          //������� ������
		text.setColor(13);      //�������
		cout << "�������� �����:" << endl;
		text.setColor(15);      //����-�����
		cout << "1 - �������� �������� �������������" << endl;
		cout << "2 - �������� ���" << endl;
		cout << "3 - �������� �������� ������������ ����" << endl;
		cout << "4 - �������� �������� ����������" << endl;
		cout << "5 - �������� ��������������" << endl;
		text.setColor(10);      //����-�������
		cout << "6 - ���������" << endl;
		text.setColor(7);       //�����
		choice = get_int(1, 6); //���� ����� ���������
		this->set_parametres(choice); //���������� ��������� �������
	} while (choice != 6);
	cout << endl;
}

void Monoblock::choose_search_parametres()
{
	Interface<int> text;
	int choice;                 //��������� �������� ������
	do {
		rewind(stdin);          //������� ������
		text.setColor(13);      //�������
		cout << endl << "�������� ��������� ������:" << endl;
		text.setColor(15);      //����-�����
		cout << "1 - �������� �������������" << endl;
		cout << "2 - ���" << endl;
		cout << "3 - �������� ������������ ����" << endl;
		cout << "4 - �������� ����������" << endl;
		cout << "5 - ��������������" << endl;
		text.setColor(10);      //����-�������
		cout << "6 - �����" << endl;
		text.setColor(7);       //�����
		choice = get_int(1, 6); //����� ��������� ������
		this->set_parametres(choice); //��������� ���������� ������
	} while (choice != 6);
}

void Monoblock::set_parametres(int choice)
{
	Interface<int> text;
	rewind(stdin);   //������� ������
	switch (choice)
	{
	case 1:
		cout << "������� �������� �������������:" << endl;
		this->setBrand(get_str(cin));
		break;
	case 2:
		cout << "������� ���" << endl;
		this->setWeight(get_int(0, INT_MAX));
		break;
	case 3:
		cout << "������� �������� ������������ ����:" << endl;
		this->setMouse(get_str(cin));
		break;
	case 4:
		cout << "������� �������� ����������:" << endl;
		this->setKeyboard(get_str(cin));
		break;
	case 5:
		cout << "������� ��������������:" << endl;
		this->setLocation(get_str(cin));
		break;
	case 6: break;
	default:
		text.setColor(12);      //����-�������
		cout << endl << "������ ������!" << endl;
		text.setColor(7);       //�����
		break;
	}
}

void Monoblock::outputClassName() //����� ������ �������� ������
{
	cout << setw(40) << right << "����� << �������� >>" << endl << endl;
}