#include "Interface.cpp"

//======================================КОНСТРУКТОРЫ========================================
Monoblock::Monoblock()                                   //конструктор без параметров
{
	strcpy_s(this->mouse, 1, "");
	strcpy_s(this->keyboard, 1, "");
}

Monoblock::Monoblock(char* nameBrand, int w, char* nameLocation, char* nameMouse, char* nameKeyboard)  //конструктор с параметрами
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}

Monoblock::Monoblock(const Monoblock &MonoB)            //конструктор копирования
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	this->weight = MonoB.weight;
}

Monoblock::Monoblock(Monoblock && MonoB)                //конструктор перемещения
{
	strcpy_s(brand, strlen(MonoB.brand) + 1, MonoB.brand);
	this->weight = MonoB.weight;
	strcpy_s(location, strlen(MonoB.location) + 1, MonoB.location);
	strcpy_s(mouse, strlen(MonoB.mouse) + 1, MonoB.mouse);
	strcpy_s(keyboard, strlen(MonoB.keyboard) + 1, MonoB.keyboard);
	MonoB.weight = 0;
}

Monoblock& Monoblock::operator=(const Monoblock& MonoB)   //оператор присваивания
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

Monoblock& Monoblock::operator=(Monoblock && MonoB)       //оператор присваивания перемещения
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

bool Monoblock::operator==(Monoblock& monoblock)          //оператор равно для поиска элементов
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
			ok = false;
	return ok;
}

Monoblock::~Monoblock()                          //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void Monoblock::setMouse(char* nameMouse)        //метод задания названия мышки
{
	strcpy_s(mouse, strlen(nameMouse) + 1, nameMouse);
}
void Monoblock::setKeyboard(char* nameKeyboard)  //метод задания названия клавиатуры
{
	strcpy_s(keyboard, strlen(nameKeyboard) + 1, nameKeyboard);
}
char* Monoblock::getMouse()                      //метод получения названия мышки
{
	return this->mouse;
}
char* Monoblock::getKeyboard()                   //метод получения названия клавиатуры
{
	return this->keyboard;
}

//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const Monoblock& MonoB) //оператор << для вывода
{
	out << dynamic_cast<const StationaryCM&>(MonoB);
	out << setw(19) << left << MonoB.mouse << "|"
		<< setw(19) << left << MonoB.keyboard << "|";
	return out;
}
istream& operator>>(istream& in, Monoblock& MonoB)        //оператор >> для ввода
{
	in >> dynamic_cast<StationaryCM&>(MonoB);
	rewind(stdin);
	cout << "Введите название компьютерной мыши:" << endl;
	in.getline(MonoB.mouse, 80);
	rewind(stdin);
	cout << "Введите название клавиатуры:" << endl;
	in.getline(MonoB.keyboard, 80);
	rewind(stdin);
	return in;
}
//==========================================================================================

void Monoblock::beginOfTable()
{
	StationaryCM::beginOfTable();
	for (int i = 0; i < 40; i++)
		cout << "_";
}

void Monoblock::outputHat()     //метод вывода шапки таблицы элементов
{
	StationaryCM::outputHat();
	cout << setw(19) << left << "Компьютерная мышь"
		<< setw(20) << left << "|Клавиатура" << "|";
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

void Monoblock::endOfTable()    //метод вывода конца таблицы элементов
{
	StationaryCM::endOfTable();
	for (int i = 0; i < 38; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

//void Monoblock::outputHat()     //метод вывода шапки таблицы элементов
//{
//	cout << " ";
//	for (int i = 0; i < 89; i++)
//		cout << "_";
//	cout << endl;
//	cout << setw(20) << left << "|Производитель" << setw(10) << left << "|Вес, г"
//		<< setw(20) << left << "|Местоположение" << setw(20) << left << "|Компьютерная мышь"
//		<< setw(20) << left << "|Клавиатура" << "|" << endl << "|";
//	for (int i = 0; i < 85; i++)
//	{
//		if (i == 19 || i == 28 || i == 47 || i == 66) cout << "|";
//		cout << "_";
//	}
//	cout << "|";
//}
//
//void Monoblock::endOfTable()    //метод вывода конца таблицы элементов
//{
//	cout << endl;
//	for (int i = 0; i < 85; i++)
//	{
//		if (i == 0 || i == 19 || i == 28 || i == 47 || i == 66) cout << "|";
//		cout << "_";
//	}
//	cout << "|" << endl << endl;
//}

void Monoblock::edit()          //метод редактирования параметров объекта
{
	Interface<int> text;
	int choice;                 //опция изменения объекта
	do {
		rewind(stdin);          //очистка буфера
		text.setColor(13);      //розовый
		cout << "Выберите опцию:" << endl;
		text.setColor(15);      //ярко-белый
		cout << "1 - изменить название производителя" << endl;
		cout << "2 - изменить вес" << endl;
		cout << "3 - изменить название компьютерной мыши" << endl;
		cout << "4 - изменить название клавиатуры" << endl;
		cout << "5 - изменить местоположение" << endl;
		text.setColor(10);      //ярко-зеленый
		cout << "6 - ПРИМЕНИТЬ" << endl;
		text.setColor(7);       //белый
		cin >> choice;          //ввод опции изменения
		this->set_parametres(choice); //установить параметры объекта
	} while (choice != 6);
	cout << endl;
}

void Monoblock::choose_search_parametres()
{
	Interface<int> text;
	int choice;                 //выбранный параметр поиска
	do {
		rewind(stdin);          //очистка буфера
		text.setColor(13);      //розовый
		cout << endl << "Выберите параметры поиска:" << endl;
		text.setColor(15);      //ярко-белый
		cout << "1 - название производителя" << endl;
		cout << "2 - вес" << endl;
		cout << "3 - название компьютерной мыши" << endl;
		cout << "4 - название клавиатуры" << endl;
		cout << "5 - местоположение" << endl;
		text.setColor(10);      //ярко-зеленый
		cout << "6 - НАЙТИ" << endl;
		text.setColor(7);       //белый
		cin >> choice;          //выбор параметра поиска
		this->set_parametres(choice); //установка параметров поиска
	} while (choice != 6);
}

void Monoblock::set_parametres(int choice)
{
	Interface<int> text;
	char buffer[80]; //буфер для строк
	int x;           //переменная для целых чисел
	rewind(stdin);   //очистка буфера
	switch (choice)
	{
	case 1:
		cout << "Введите название производителя:" << endl;
		cin.getline(buffer, 80);
		this->setBrand(buffer);
		break;
	case 2:
		cout << "Введите вес" << endl;
		cin >> x;
		this->setWeight(x);
		break;
	case 3:
		cout << "Введите название компьютерной мыши:" << endl;
		cin.getline(buffer, 80);
		this->setMouse(buffer);
		break;
	case 4:
		cout << "Введите название клавиатуры:" << endl;
		cin.getline(buffer, 80);
		this->setKeyboard(buffer);
		break;
	case 5:
		cout << "Введите местоположение:" << endl;
		cin.getline(buffer, 80);
		this->setLocation(buffer);
		break;
	case 6: break;
	default:
		text.setColor(12);      //ярко-красный
		cout << endl << "Ошибка выбора!" << endl;
		text.setColor(7);       //белый
		break;
	}
}

void Monoblock::outputClassName() //метод вывода названия класса
{
	cout << setw(40) << right << "КЛАСС << МОНОБЛОК >>" << endl << endl;
}