#include "Interface.cpp"

//======================================КОНСТРУКТОРЫ========================================
Notebook::Notebook()                                   //конструктор без параметров
{
	strcpy_s(this->typeOfNotebook, 1, "");
	keyboardBacklight = '?';
}

Notebook::Notebook(char* nameBrand, int w, int batCap, char keyboardlight, char* type)  //конструктор с параметрами
{
	strcpy_s(typeOfNotebook, strlen(type) + 1, type);
	this->keyboardBacklight = keyboardlight;
}

Notebook::Notebook(const Notebook& notebook)            //конструктор копирования
{
	strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
	this->weight = notebook.weight;
	this->batteryCapacity = notebook.batteryCapacity;
	strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	this->keyboardBacklight = notebook.keyboardBacklight;
}

Notebook::Notebook(Notebook&& notebook)                //конструктор перемещения
{
	strcpy_s(brand, strlen(notebook.brand) + 1, notebook.brand);
	this->weight = notebook.weight;
	this->batteryCapacity = notebook.batteryCapacity;
	strcpy_s(typeOfNotebook, strlen(notebook.typeOfNotebook) + 1, notebook.typeOfNotebook);
	this->keyboardBacklight = notebook.keyboardBacklight;
	notebook.weight = notebook.batteryCapacity = 0;
	notebook.keyboardBacklight = '-';
}

Notebook& Notebook::operator=(const Notebook& notebook)   //оператор присваивания
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

Notebook& Notebook::operator=(Notebook&& notebook)       //оператор присваивания перемещения
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

bool Notebook::operator==(Notebook& notebook)         //оператор равно для сравнения элементов при поиске
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

Notebook::~Notebook()                                    //деструктор
{}
//==========================================================================================

//=======================================МЕТОДЫ=============================================
void Notebook::setKeyboardBacklight(char keyboardlight)  //метод задания наличия подсветки клавиатуры
{
	this->keyboardBacklight = keyboardlight;
}
void Notebook::setTypeOfNotebook(char* type)             //метод задания типа ноутбука
{
	strcpy_s(typeOfNotebook, strlen(type) + 1, type);
}
char Notebook::getKeyboardBacklight()             //метод получения данных о наличии подсветки клавиатуры
{
	return this->keyboardBacklight;
}
char* Notebook::getTypeOfNotebook()               //метод получения типа ноутбука
{
	return this->typeOfNotebook;
}
//==========================================================================================

//=================================ДРУЖЕСТВЕННЫЕ ФУНКЦИИ====================================
ostream& operator<<(ostream& out, const Notebook& notebook) //оператор << для вывода
{
	out << dynamic_cast<const PortableCM&>(notebook);
	out << setw(19) << left << notebook.typeOfNotebook << "|"
		<< setw(14) << setfill(' ') << right << notebook.keyboardBacklight << setw(15) << "|";
	return out;
}
istream& operator>>(istream& in, Notebook& notebook)        //оператор >> для ввода
{
	in >> dynamic_cast<PortableCM&>(notebook);
	rewind(stdin);
	cout << "Введите признак наличия подсветки клавиатуры('+' - есть, '-' - нет):" << endl;
	notebook.keyboardBacklight = get_char('+', '-');
	rewind(stdin);
	cout << "Введите тип ноутбука:" << endl;
	char* str = get_str(in);
	strcpy_s(notebook.typeOfNotebook, strlen(str) + 1, str);
	rewind(stdin);
	return in;
}

ofstream& operator<<(ofstream& fout, const Notebook& notebook) //оператор << для вывода
{
	fout << dynamic_cast<const PortableCM&>(notebook);
	fout << setw(19) << left << notebook.typeOfNotebook << '|'
		<< setw(14) //<< setfill(' ') 
		<< right << notebook.keyboardBacklight << '\n'; //<< setw(15);//<< "|";
	return fout;
}
ifstream& operator>>(ifstream& fin, Notebook& notebook)        //оператор >> для ввода
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

void Notebook::outputHat()           //метод вывода шапки таблицы элементов
{
	PortableCM::outputHat();
	cout << setw(19) << left << "Тип ноутбука"
		<< setw(25) << "|Наличие подсветки клавиатуры" << "|";
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

void Notebook::endOfTable() //метод вывода конца таблицы элементов
{
	PortableCM::endOfTable();
	for (int i = 0; i < 47; i++)
	{
		if (i == 19) cout << "|";
		cout << "_";
	}
	cout << "|";
}

void Notebook::edit()        //метод редактирования параметров объекта
{
	Interface<int> text;
	int choice;              //выбранный параметр для редактирования 
	do {
		rewind(stdin);       //очистка буфера
		text.setColor(13);   //розовый
		cout << "Выберите опцию:" << endl;
		text.setColor(15);   //ярко-белый
		cout << "1 - изменить название производителя" << endl;
		cout << "2 - изменить вес" << endl;
		cout << "3 - изменить емкость аккумулятора" << endl;
		cout << "4 - изменить наличе подсветки клавиатуры" << endl;
		cout << "5 - изменить тип ноутбука" << endl;
		text.setColor(10);   //ярко-зеленый
		cout << "6 - ПРИМЕНИТЬ" << endl;
		text.setColor(7);    //белый
		choice = get_int(1, 6); //ввод номера выбранного параметра
		this->set_parametres(choice); //установка параметров
	} while (choice != 6);
	cout << endl;
}

void Notebook::choose_search_parametres()   //метод выбора параметров поиска
{
	Interface<int> text;
	int choice;              //номер параметра
	do {
		rewind(stdin);       //очистка буфера
		text.setColor(13);   //розовый
		cout << endl << "Выберите параметры поиска." << endl;
		text.setColor(15);   //ярко-белый
		cout << "1 - название производителя" << endl;
		cout << "2 - вес" << endl;
		cout << "3 - емкость аккумулятора" << endl;
		cout << "4 - наличие подсветки клавиатуры" << endl;
		cout << "5 - тип ноутбука" << endl;
		text.setColor(10);   //ярко-зеленый
		cout << "6 - НАЙТИ" << endl;
		text.setColor(7);    //белый
		choice = get_int(1, 6); //ввод номера параметра поиска
		this->set_parametres(choice);  //установка параметров
	} while (choice != 6);
}

void Notebook::set_parametres(int choice) //метод установки параметров
{
	Interface<int> text;
	rewind(stdin);       //очистка буфера
	switch (choice)
	{
	case 1:
		cout << "Введите название производителя:" << endl;
		this->setBrand(get_str(cin));
		break;
	case 2:
		cout << "Введите вес:" << endl;
		this->setWeight(get_int(0, INT_MAX));
		break;
	case 3:
		cout << "Введите емкость аккумулятора:" << endl;
		this->setBatteryCapacity(get_int(0, INT_MAX));
		break;
	case 4:
		cout << "Введите наличие подсветки клавиатуры('+' - есть, '-' - нет):" << endl;
		this->setKeyboardBacklight(get_char('+', '-'));
		break;
	case 5:
		cout << "Введите тип ноутбука:" << endl;
		this->setTypeOfNotebook(get_str(cin));
		break;
	case 6: break;
	default:
		text.setColor(12);     //ярко-красный
		cout << endl << "Ошибка выбора!" << endl;
		text.setColor(7);      //белый
		break;
	}
}

void Notebook::outputClassName() //метод вывода названия класса
{
	cout << setw(40) << right << "КЛАСС << НОУТБУК >>" << endl << endl;
}