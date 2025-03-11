#include "Interface.cpp"

//======================================КОНСТРУКТОРЫ========================================
Smartphone::Smartphone()                  //конструктор без параметров
{
	strcpy_s(this->touchScreen, 1, "");
	this->сameraResolution = 0;
}

Smartphone::Smartphone(char* nameBrand, int w, int batCap, char* screen, int camera)  //конструктор с параметрами
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
	this->сameraResolution = camera;
}

Smartphone::Smartphone(const Smartphone& phone)            //конструктор копирования
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->сameraResolution = phone.сameraResolution;
}

Smartphone::Smartphone(Smartphone&& phone)                //конструктор перемещения
{
	strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
	this->weight = phone.weight;
	this->batteryCapacity = phone.batteryCapacity;
	strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	this->сameraResolution = phone.сameraResolution;
	phone.weight = phone.batteryCapacity = phone.сameraResolution = 0;
}

Smartphone& Smartphone::operator=(const Smartphone& phone)   //оператор присваивания
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		batteryCapacity = phone.batteryCapacity;
		сameraResolution = phone.сameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
	}
	return *this;
}

Smartphone& Smartphone::operator=(Smartphone&& phone)       //оператор присваивания перемещения
{
	if (this != &phone)
	{
		strcpy_s(brand, strlen(phone.brand) + 1, phone.brand);
		weight = phone.weight;
		phone.weight = 0;
		batteryCapacity = phone.batteryCapacity;
		сameraResolution = phone.сameraResolution;
		strcpy_s(touchScreen, strlen(phone.touchScreen) + 1, phone.touchScreen);
		phone.batteryCapacity = 0;
		phone.сameraResolution = 0;
	}
	return *this;
}

bool Smartphone::operator==(Smartphone& phone)               //оператор равно для сравнения элементов при поиске
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
	if (phone.сameraResolution)
		if (this->сameraResolution == phone.сameraResolution)
			ok = true;
		else
			return false;
	return ok;
}

Smartphone::~Smartphone()                           //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void Smartphone::setTouchScreen(const char* screen)       //метод задания типа экрана
{
	strcpy_s(touchScreen, strlen(screen) + 1, screen);
}
void Smartphone::setCameraResolution(int camera)    //метод задания разрешения камеры
{
	this->сameraResolution = camera;
}
char* Smartphone::getTouchScreen()                  //метод получения типа экрана
{
	return this->touchScreen;
}
int Smartphone::getCameraResolution()               //метод получения разрешения камеры
{
	return this->сameraResolution;
}
//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const Smartphone& phone) //оператор << для вывода
{
	out << dynamic_cast<const PortableCM&>(phone);
	out << setw(10) << left << phone.touchScreen << "|"
		<< setw(21) << left << phone.сameraResolution << "|";
	return out;
}
istream& operator>>(istream& in, Smartphone& phone)        //оператор >> для ввода
{
	in >> dynamic_cast<PortableCM&>(phone);
	rewind(stdin);
	cout << "Введите тип экрана смартфона:" << endl;
	char* str = get_str(in);
	strcpy_s(phone.touchScreen, strlen(str) + 1, str);
	rewind(stdin);
	cout << "Введите разрешение камеры смартфона(Мп):" << endl;
	phone.сameraResolution = get_int(1, 200);
	rewind(stdin);
	return in;
}

ofstream& operator<<(ofstream& fout, const Smartphone& phone) //оператор << для вывода
{
	fout << dynamic_cast<const PortableCM&>(phone);
	fout << setw(10) << left << phone.touchScreen << '|'
		<< setw(21) << left << phone.сameraResolution << '\n';//<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, Smartphone& phone)        //оператор >> для ввода
{
	fin >> dynamic_cast<PortableCM&>(phone);
	//fin >> phone.touchScreen >> phone.сameraResolution;
	fin.getline(phone.touchScreen, 80, '|');
	char* s = phone.touchScreen;
	delete_spaces(s);
	fin >> phone.сameraResolution;
	return fin;
}

fstream& operator>>(fstream& fin, Smartphone& phone)
{
	fin.read(reinterpret_cast<char*>(&phone), sizeof(Smartphone));
	return fin;
}

fstream& operator<<(fstream& fout, const Smartphone& phone)
{
	fout.write(reinterpret_cast<const char*>(&phone), sizeof(Smartphone));
	return fout;
}
//==========================================================================================

void Smartphone::beginOfTable()
{
	PortableCM::beginOfTable();
	for (int i = 0; i < 33; i++)
		cout << "_";
}

void Smartphone::outputHat()        //метод для вывода шапки таблицы элементов
{
	PortableCM::outputHat();
	cout << setw(10) << left << "Тип экрана" << setw(22) << "|Разрешение камеры, Мп" << "|";
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

void Smartphone::endOfTable()       //метод для вывода конца таблицы элементов
{
	PortableCM::endOfTable();
	for (int i = 0; i < 31; i++)
	{
		if (i == 10) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Smartphone::edit()         //метод для редактирования параметров объекта
{
	Interface<int> text;
	int choice;                 //номер опции изменения
	do {
		rewind(stdin);          //очистка буфера
		text.setColor(13);      //розовый
		cout << "Выберите опцию:" << endl;//<< "(целое число в диапазоне [1, 6])" << endl;
		text.setColor(15);      //ярко-белый
		cout << "1 - изменить название производителя" << endl;
		cout << "2 - изменить вес" << endl;
		cout << "3 - изменить емкость аккумулятора" << endl;
		cout << "4 - изменить тип экрана" << endl;
		cout << "5 - изменить разрешение камеры" << endl;
		text.setColor(10);      //ярко-зеленый
		cout << "6 - ПРИМЕНИТЬ" << endl;
		text.setColor(7);       //белый
		choice = get_int(1, 6); //ввод номера опции изменения
		this->set_parametres(choice);  //установка параметров
	} while (choice != 6);
	cout << endl;
}

void Smartphone::choose_search_parametres()   //метод для выбора параметров поиска
{
	Interface<int> text;
	int choice;             //номер параметра поиска
	do {
		rewind(stdin);      //очистка буфера
		text.setColor(13);  //розовый
		cout << endl << "Выберите параметры поиска:" << endl; //<< "целое число в диапазоне [1, 6]" << endl;
		text.setColor(15);  //ярко-белый
		cout << "1 - название производителя" << endl;
		cout << "2 - вес" << endl;
		cout << "3 - емкость аккумулятора" << endl;
		cout << "4 - тип экрана" << endl;
		cout << "5 - разрешение камеры" << endl;
		text.setColor(10);  //ярко-зеленый
		cout << "6 - НАЙТИ" << endl;
		text.setColor(7);   //белый
		choice = get_int(1, 6);       //ввод номера параметра поиска
		this->set_parametres(choice); //установка параметров
	} while (choice != 6);
}

void Smartphone::set_parametres(int choice)  //метод установки параметров
{
	Interface<int> text;
	rewind(stdin);
	switch (choice)
	{
	case 1:
		cout << "Введите название производителя:" << endl;
		this->setBrand(get_str(cin));
		break;
	case 2:
		cout << "Введите вес" << endl;// << "(целое число в диапазоне [1, " << SHRT_MAX << "])" << endl;
		this->setWeight(get_int(1, SHRT_MAX));
		break;
	case 3:
		cout << "Введите емкость аккумулятора:" << endl;//<< "(целое число в диапазоне [2000, 100000])" << endl;
		this->setBatteryCapacity(get_int(2000, 100000));
		break;
	case 4:
		cout << "Введите тип экрана:" << endl;
		this->setTouchScreen(get_str(cin));
		break;
	case 5:
		cout << "Введите разрешение камеры:" << endl;//<< "(целое число в диапазоне [1, 200])" << endl;
		this->setCameraResolution(get_int(1, 200));
		break;
	case 6: break;
	default:
		text.setColor(12);  //ярко-красный
		cout << endl << "Ошибка выбора!" << endl;
		text.setColor(7);   //белый
		break;
	}
}

void Smartphone::outputClassName() //метод вывода названия класса
{
	cout << setw(40) << right << "КЛАСС << СМАРТФОН >>" << endl << endl;
}

void Smartphone::cleanSomeFields(Smartphone& phone)
{
	if (!strcmp(phone.brand, ""))
		strcpy_s(this->brand, strlen(this->brand), phone.brand);
	if (!phone.weight)
		this->weight = 0;
	if (phone.batteryCapacity == 0)
		this->batteryCapacity = 0;
	if (!strcmp(phone.touchScreen, ""))
		strcpy_s(this->touchScreen, strlen(this->touchScreen), phone.touchScreen);
	if (phone.сameraResolution == 0)
		this->сameraResolution = 0;
}

bool Smartphone::operator<(Smartphone& phone)
{
	if (strcmp(phone.brand, ""))
	{
		if (strcmp(this->brand, phone.brand) < 0)
			return true;
		return false;
	}
	if (phone.weight != 0)
	{
		if (this->weight < phone.weight)
			return true;
		return false;
	}
	if (phone.batteryCapacity != 0)
	{
		if (this->batteryCapacity < phone.batteryCapacity)
			return true;
		return false;
	}
	if (strcmp(phone.touchScreen, ""))
	{
		if (strcmp(this->touchScreen, phone.touchScreen) < 0)
			return true;
		return false;
	}
	if (phone.сameraResolution != 0)
	{
		if (this->сameraResolution < phone.сameraResolution)
			return true;
		return false;
	}
	return false;
}


void Smartphone::set_sort_parametres()
{
	Interface<int> text;
	int choice;         //номер параметра поиска
	rewind(stdin);      //очистка буфера
	text.setColor(13);  //розовый
	cout << endl << "Выберите параметр сортировки:" << endl; //<< "целое число в диапазоне [1, 6]" << endl;
	text.setColor(15);  //ярко-белый
	cout << "1 - название производителя" << endl;
	cout << "2 - вес" << endl;
	cout << "3 - емкость аккумулятора" << endl;
	cout << "4 - тип экрана" << endl;
	cout << "5 - разрешение камеры" << endl;
	text.setColor(7);   //белый
	choice = get_int(1, 5);       //ввод номера параметра
	switch (choice)
	{
	case 1: this->setBrand("-"); break;
	case 2: this->setWeight(1); break;
	case 3: this->setBatteryCapacity(1); break;
	case 4: this->setTouchScreen("-"); break;
	case 5: this->setCameraResolution(1); break;
	default: break;
	}
}