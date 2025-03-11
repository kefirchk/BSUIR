#include "Interface.cpp"

//======================================������������========================================
Smartphone::Smartphone()                  //����������� ��� ����������
{
	strcpy_s(this->touchScreen, 1, "");
	this->�ameraResolution = 0;
}

Smartphone::Smartphone(char* nameBrand, int w, int batCap, char* screen, int camera)  //����������� � �����������
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
	this->�ameraResolution = camera;
}

Smartphone::Smartphone(const Smartphone& phone)            //����������� �����������
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->�ameraResolution = phone.�ameraResolution;
}

Smartphone::Smartphone(Smartphone&& phone)                //����������� �����������
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->�ameraResolution = phone.�ameraResolution;
	phone.weight = phone.batteryCapacity = phone.�ameraResolution = 0;
}

Smartphone& Smartphone::operator=(const Smartphone& phone)   //�������� ������������
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		batteryCapacity = phone.batteryCapacity;
		�ameraResolution = phone.�ameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	}
	return *this;
}

Smartphone& Smartphone::operator=(Smartphone&& phone)       //�������� ������������ �����������
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		phone.weight = 0;
		batteryCapacity = phone.batteryCapacity;
		�ameraResolution = phone.�ameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
		phone.batteryCapacity = 0;
		phone.�ameraResolution = 0;
	}
	return *this;
}

bool Smartphone::operator==(Smartphone& phone)               //�������� ����� ��� ��������� ��������� ��� ������
{
	bool ok = false;
	if (phone.batteryCapacity)
		if (this->batteryCapacity == phone.batteryCapacity)
			ok = true;
		else return false;
	if (phone.weight)
		if (this->weight == phone.weight)
			ok = true;
		else return false;
	if (strcmp(phone.brand, ""))
		if (!strcmp(this->brand, phone.brand))
			ok = true;
		else return false;
	if (strcmp(phone.touchScreen, ""))
		if (!strcmp(this->touchScreen, phone.touchScreen))
			ok = true;
		else
			return false;
	if (phone.�ameraResolution)
		if (this->�ameraResolution == phone.�ameraResolution)
			ok = true;
		else
			return false;
	return ok;
}

Smartphone::~Smartphone()                           //����������
{}
//==========================================================================================

//=======================================������=============================================
void Smartphone::setTouchScreen(char* screen)       //����� ������� ���� ������
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
}
void Smartphone::setCameraResolution(int camera)    //����� ������� ���������� ������
{
	this->�ameraResolution = camera;
}
char* Smartphone::getTouchScreen()                  //����� ��������� ���� ������
{
	return this->touchScreen;
}
int Smartphone::getCameraResolution()               //����� ��������� ���������� ������
{
	return this->�ameraResolution;
}
//==========================================================================================

//=================================������������� �������====================================
ostream& operator<<(ostream& out, const Smartphone& phone) //�������� << ��� ������
{
	out << dynamic_cast<const PortableCM&>(phone);
	out << setw(10) << left << phone.touchScreen << "|"
		<< setw(21) << left << phone.�ameraResolution << "|";
	return out;
}
istream& operator>>(istream& in, Smartphone& phone)        //�������� >> ��� �����
{
	in >> dynamic_cast<PortableCM&>(phone);
	rewind(stdin);
	cout << "������� ��� ������ ���������:" << endl;
	char* str = get_str(in);
	strcpy_s(phone.touchScreen, strlen(str) + 1, str);
	rewind(stdin);
	cout << "������� ���������� ������ ���������(��):" << endl;
	phone.�ameraResolution = get_int(1, 200);
	rewind(stdin);
	return in;
}
//==========================================================================================

void Smartphone::beginOfTable()
{
	PortableCM::beginOfTable();
	for (int i = 0; i < 33; i++)
		cout << "_";
}

void Smartphone::outputHat()        //����� ��� ������ ����� ������� ���������
{
	PortableCM::outputHat();
	cout << setw(10) << left << "��� ������" << setw(22) << "|���������� ������, ��" << "|";
}

void Smartphone::endOfHat()
{
	PortableCM::endOfHat();
	for (int i = 0; i < 31; i++)
	{
		if (i == 10) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Smartphone::endOfTable()       //����� ��� ������ ����� ������� ���������
{
	PortableCM::endOfTable();
	for (int i = 0; i < 31; i++)
	{
		if (i == 10) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Smartphone::edit()         //����� ��� �������������� ���������� �������
{
	Interface<int> text;
	int choice;                 //����� ����� ���������
	do {
		rewind(stdin);          //������� ������
		text.setColor(13);      //�������
		cout << "�������� �����:" << endl;//<< "(����� ����� � ��������� [1, 6])" << endl;
		text.setColor(15);      //����-�����
		cout << "1 - �������� �������� �������������" << endl;
		cout << "2 - �������� ���" << endl;
		cout << "3 - �������� ������� ������������" << endl;
		cout << "4 - �������� ��� ������" << endl;
		cout << "5 - �������� ���������� ������" << endl;
		text.setColor(10);      //����-�������
		cout << "6 - ���������" << endl;
		text.setColor(7);       //�����
		choice = get_int(1, 6); //���� ������ ����� ���������
		this->set_parametres(choice);  //��������� ����������
	} while (choice != 6);
	cout << endl;
}

void Smartphone::choose_search_parametres()   //����� ��� ������ ���������� ������
{
	Interface<int> text;
	int choice;             //����� ��������� ������
	do {
		rewind(stdin);      //������� ������
		text.setColor(13);  //�������
		cout << endl << "�������� ��������� ������:" << endl; //<< "����� ����� � ��������� [1, 6]" << endl;
		text.setColor(15);  //����-�����
		cout << "1 - �������� �������������" << endl;
		cout << "2 - ���" << endl;
		cout << "3 - ������� ������������" << endl;
		cout << "4 - ��� ������" << endl;
		cout << "5 - ���������� ������" << endl;
		text.setColor(10);  //����-�������
		cout << "6 - �����" << endl;
		text.setColor(7);   //�����
		choice = get_int(1, 6);       //���� ������ ��������� ������
		this->set_parametres(choice); //��������� ����������
	} while (choice != 6);
}

void Smartphone::set_parametres(int choice)  //����� ��������� ����������
{
	Interface<int> text;
	rewind(stdin);
	switch (choice)
	{
	case 1:
		cout << "������� �������� �������������:" << endl;
		this->setBrand(get_str(cin));
		break;
	case 2:
		cout << "������� ���" << endl;// << "(����� ����� � ��������� [1, " << SHRT_MAX << "])" << endl;
		this->setWeight(get_int(1, SHRT_MAX));
		break;
	case 3:
		cout << "������� ������� ������������:" << endl;//<< "(����� ����� � ��������� [2000, 100000])" << endl;
		this->setBatteryCapacity(get_int(2000, 100000));
		break;
	case 4:
		cout << "������� ��� ������:" << endl;
		this->setTouchScreen(get_str(cin));
		break;
	case 5:
		cout << "������� ���������� ������:" << endl;//<< "(����� ����� � ��������� [1, 200])" << endl;
		this->setCameraResolution(get_int(1, 200));
		break;
	case 6: break;
	default:
		text.setColor(12);  //����-�������
		cout << endl << "������ ������!" << endl;
		text.setColor(7);   //�����
		break;
	}
}

void Smartphone::outputClassName() //����� ������ �������� ������
{
	cout << setw(40) << right << "����� << �������� >>" << endl << endl;
}