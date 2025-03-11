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
void Smartphone::setTouchScreen(char* screen)       //метод задания типа экрана
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