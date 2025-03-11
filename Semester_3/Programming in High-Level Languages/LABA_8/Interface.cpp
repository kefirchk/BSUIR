#pragma once
#include "Functions.h"
#include "Interface.h"
#include "Algorithm.h"
#include <limits>
#include <map>
using namespace std;

//====================================== ГЛАВНОЕ МЕНЮ ==========================================
template<class T>
void Interface<T>::mainMenu()      //метод главного меню
{
	int choice, cont;
	do {
		cont = menu_workContainer();
		if (cont == 3) return;
		else
		{
			rewind(stdin);      //чистка буфера
			setColor(10);       //салатовый
			this->outputName();
			setColor(13);       //розовый
			cout << setw(59) << "Выберите класс, с которым будете работать:" << endl;
			setColor(7);        //белый
			cout << setw(48) << "->> 1. Моноблоки <<-" << endl;
			cout << setw(48) << "->> 2. Смартфоны <<-" << endl;
			cout << setw(46) << "->> 3. Ноубуки <<-" << endl;
			setColor(12);       //ярко-красный
			cout << setw(44) << "->> 4. ВЫХОД <<-" << endl;
			setColor(7);        //белый
			choice = get_int(1, 4);
			switch (choice)
			{
			case 1: //работа с классом Моноблок
			{
				Interface<Monoblock> object;
				BinaryTree<Monoblock> tree;
				multimap <int, Monoblock> m_map;
				system("cls");
				if (cont == 1)
					object.subMenu(tree);
				else
					object.subMenu_withMultimap(m_map);
			} break;
			case 2: //работа с классом Смартфон
			{
				Interface<Smartphone> object;
				BinaryTree<Smartphone> tree;
				multimap <int, Smartphone> m_map;
				system("cls");
				if (cont == 1)
					object.subMenu(tree);
				else
					object.subMenu_withMultimap(m_map);
			} break;
			case 3: //работа с классом Ноутбук
			{
				Interface<Notebook> object;
				BinaryTree<Notebook> tree;
				multimap <int, Notebook> m_map;
				system("cls");
				if (cont == 1)
					object.subMenu(tree);
				else
					object.subMenu_withMultimap(m_map);
			} break;
			case 4:
				setColor(7);        //белый
				return;
			}
		}
	} while (1);
}
//====================================== ПОДМЕНЮ ==========================================
template<class T>
void Interface<T>::subMenu_withMultimap(multimap<int, T>& m_map)
{
	T tempObject;
	string filename = choosing_file(tempObject);
	TxtFile<T> file_txt((filename + TXT).c_str());
	BinFile<T> file_bin((filename + BIN).c_str());
	int choice;             //переменная для выбора опции
	setColor(9);            //синий
	tempObject.outputClassName(); //вывод названия класса
	do {
		multimap<int, T> tempMultiMapForBin;
		multimap<int, T> tempMultiMapForTxt;
		rewind(stdin);      //очистка буфера
		instructions();
	    choice = get_int(1, 17);
		switch (choice)
		{
			//-------------------------------------ВСТАВКА ЭЛЕМЕНТА В ДЕРЕВО----------------------------------------------------
		case 1:
			add_element(m_map);
			break;
			//-------------------------------------ИЗМЕНЕНИЕ ЭЛЕМЕНТА ДЕРЕВА----------------------------------------------------
		case 2:
			edit_element(m_map);
			break;
			//-------------------------------------УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА--------------------------------------------------
		case 3:
			delete_element(m_map);
			break;
			//-------------------------------------ВЫВОД ДЕРЕВА НА ЭКРАН--------------------------------------------------------
		case 4:
			show_elements(m_map);
			break;
			//-------------------------------------СОРТИРОВКА ТАБЛИЦЫ ОБЪЕКТОВ--------------------------------------------------
		case 5:
			sort_elements(m_map);
			setColor(GREEN);
			cout << endl << "Контейнер успешно отсортирован!" << endl << endl;
			break;
			//-------------------------------------ПОИСК НЕСКОЛЬКИХ ЭЛЕМЕНТОВ С ПРОДОЛЖЕНИЕМ ПОИСКА-----------------------------
		case 6:
			find_elements(m_map);
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ BIN-ФАЙЛА--------------------------------------------
		case 7:
			if (file_bin.openBinFile(ios::in))
				file_bin.readFromFile(tempMultiMapForBin);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-----------------------------------------------
		case 8:
			if (file_bin.openBinFile(ios::app))
				file_bin.writeInFile(m_map);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-------------------------------------------
		case 9:
			if (file_bin.openBinFile(ios::out | ios::trunc))
				file_bin.writeInFile(m_map);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 10:
			if (file_bin.openBinFile(ios::in))
			{
				file_bin.readFromFile(tempMultiMapForBin);
				if (!tempMultiMapForBin.empty())
				{
					for (auto it = tempMultiMapForBin.begin(); it != tempMultiMapForBin.end(); it++)
					{
						int key = generate_id(m_map);
						m_map.emplace(key, it->second);
					}
					setColor(GREEN);
					cout << endl << "Информация успешно добавлена в multimap!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------УДАЛИТЬ ФАЙЛ-----------------------------------------------------------------
		case 11:
			file_bin.remove_file();
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ TXT-ФАЙЛА--------------------------------------------
		case 12:
			if (file_txt.openForRead())
				file_txt.readFromFile(tempMultiMapForTxt);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-----------------------------------------------
		case 13:
			if (file_txt.openForWrite(ios::app))
				file_txt.writeInFile(m_map);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-------------------------------------------
		case 14:
			if (file_txt.openForWrite(ios::out | ios::trunc))
				file_txt.writeInFile(m_map);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 15:
			if (file_txt.openForRead())
			{
				file_txt.readFromFile(tempMultiMapForTxt);
				if (!tempMultiMapForTxt.empty())
				{
					for (auto it = tempMultiMapForTxt.begin(); it != tempMultiMapForTxt.end(); it++)
					{
						int key = generate_id(m_map);
						m_map.emplace(key, it->second);
					}
					setColor(GREEN);
					cout << endl << "Информация успешно добавлена в multimap!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------УДАЛИТЬ ФАЙЛ-----------------------------------------------------------------
		case 16:
			file_txt.remove_file();
			break;
			//-------------------------------------ВЫХОД ИЗ ПОДМЕНЮ РАБОТЫ С КЛАССОМ--------------------------------------------
		case 17:
			system("cls");  //очистка экрана
			return;
		}
	} while (1);
}


template<class T>
void Interface<T>::subMenu(BinaryTree<T>& tree)
{
	T tempObject;
	string filename = choosing_file(tempObject);
	TxtFile<T> file_txt((filename + TXT).c_str());
	BinFile<T> file_bin((filename + BIN).c_str());
	int choice;             //переменная для выбора опции
	setColor(9);            //синий
	tempObject.outputClassName(); //вывод названия класса
	do {
		BinaryTree<T> tempTreeForBin;
		BinaryTree<T> tempTreeForTxt;
		rewind(stdin);      //очистка буфера
		instructions();
		choice = get_int(1, 17);
		switch (choice)
		{
			//-------------------------------------ВСТАВКА ЭЛЕМЕНТА В ДЕРЕВО----------------------------------------------------
		case 1:
			add_element(tree);
			break;
			//-------------------------------------ИЗМЕНЕНИЕ ЭЛЕМЕНТА ДЕРЕВА----------------------------------------------------
		case 2:
			edit_element(tree);
			break;
			//-------------------------------------УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА--------------------------------------------------
		case 3:
			delete_element(tree);
			break;
			//-------------------------------------ВЫВОД ДЕРЕВА НА ЭКРАН--------------------------------------------------------
		case 4:
			show_elements(tree);
			break;
			//-------------------------------------СОРТИРОВКА ТАБЛИЦЫ ОБЪЕКТОВ--------------------------------------------------
		case 5:
			sort_elements(tree);
			setColor(GREEN);
			cout << endl << "Контейнер успешно отсортирован!" << endl << endl;
			break;
			//-------------------------------------ПОИСК НЕСКОЛЬКИХ ЭЛЕМЕНТОВ С ПРОДОЛЖЕНИЕМ ПОИСКА-----------------------------
		case 6:
			find_elements(tree);
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ BIN-ФАЙЛА--------------------------------------------
		case 7: 
			if (file_bin.openBinFile(ios::in))
				file_bin.readFromFile(tempTreeForBin);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-----------------------------------------------
		case 8:
			if (file_bin.openBinFile(ios::app))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-------------------------------------------
		case 9:
			if (file_bin.openBinFile(ios::out | ios::trunc))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 10:
			if (file_bin.openBinFile(ios::in))
			{
				file_bin.readFromFile(tempTreeForBin);
				if (!tempTreeForBin.empty())
				{
					tree.uniteTrees(tempTreeForBin);
					setColor(GREEN);
					cout << endl << "Информация успешно добавлена в дерево!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------УДАЛИТЬ ФАЙЛ-----------------------------------------------------------------
		case 11:
			file_bin.remove_file();
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ TXT-ФАЙЛА--------------------------------------------
		case 12: 
			if (file_txt.openForRead())
				file_txt.readFromFile(tempTreeForTxt);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-----------------------------------------------
		case 13: 
			if (file_txt.openForWrite(ios::app))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-------------------------------------------
		case 14: 
			if (file_txt.openForWrite(ios::out | ios::trunc))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 15:
			if (file_txt.openForRead())
			{
				file_txt.readFromFile(tempTreeForTxt);
				if (!tempTreeForTxt.empty())
				{
					tree.uniteTrees(tempTreeForTxt);
					setColor(GREEN);
					cout << endl << "Информация успешно добавлена в дерево!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------УДАЛИТЬ ФАЙЛ-----------------------------------------------------------------
		case 16: 
			file_txt.remove_file();
			break;
			//-------------------------------------ВЫХОД ИЗ ПОДМЕНЮ РАБОТЫ С КЛАССОМ--------------------------------------------
		case 17:
			system("cls");  //очистка экрана
			return;
		}
	} while (1);
}


template <class T>
int Interface<T>::menu_workContainer()
{
	int choice;
	rewind(stdin);      //чистка буфера
	setColor(10);       //салатовый
	this->outputName();
	setColor(13);       //розовый
	cout << setw(60) << "Выберите контейнер, с которым будете работать:" << endl;
	setColor(7);        //белый
	cout << setw(48) << "->> 1. BinaryTree <<-" << endl;
	cout << setw(46) << "->> 2. Multimap <<-" << endl;
	setColor(RED);
	cout << setw(43) << "->> 3. ВЫХОД <<-" << endl;
	setColor(7);        //белый
	choice = get_int(1, 3);
	system("cls");
	return choice;
}


template<class T>
void Interface<T>::instructions()
{
	setColor(13);       //розовый
	cout << "Выберите опцию:" << endl;
	setColor(TURQUOISE);
	cout << "--------СТАНДАРТНЫЕ ОПЕРАЦИИ--------" << endl;
	setColor(7);        //белый
	cout << "1. Добавить элемент" << endl
		<< "2. Изменить элемент" << endl
		<< "3. Удалить элемент" << endl
		<< "4. Вывести дерево элементов" << endl
		<< "5. Сортировать" << endl
		<< "6. Поиск" << endl;
	setColor(TURQUOISE);
	cout << "-------ОПЕРАЦИИ С BIN-ФАЙЛАМИ--------" << endl;
	setColor(7);        //белый
	cout << "7. Прочитать информацию" << endl
		<< "8. Дописать информацию" << endl
		<< "9. Перезаписать информацию" << endl
		<< "10. Добавить прочитанную информацию в главный контейнер" << endl
		<< "11. Удалить файл" << endl;
	setColor(TURQUOISE);
	cout << "-------ОПЕРАЦИИ С TXT-ФАЙЛАМИ--------" << endl;
	setColor(7);        //белый
	cout << "12. Прочитать информацию" << endl
		<< "13. Дописать информацию" << endl
		<< "14. Перезаписать информацию" << endl
		<< "15. Добавить прочитанную информацию в главный контейнер" << endl
		<< "16. Удалить файл" << endl;
	setColor(TURQUOISE);
	cout << "-------------------------------------" << endl;
	setColor(14);       //желтый
	cout << "17. <-|НАЗАД|<-" << endl;
	setColor(7);        //белый
}


template <class T>
void Interface<T>::outputName() //метод вывода на экран текста "Г Л А В Н О Е   М Е Н Ю"
{
	cout << setw(50) << right << "-------------------------" << endl;
	cout << setw(25) << right << '|' << name << '|' << endl;
	cout << setw(50) << right << "-------------------------" << endl;
}

template <class T>
void Interface<T>::setColor(int color)        //метод задания цвета тексту
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color); //задание цвета текста
}

template<class T>
int generate_id(multimap<int, T>& m_map)
{
	try
	{
		int i = 1;
		for (; i < SHRT_MAX; i++)
		{
			if (i == SHRT_MAX - 1)
				throw ContainerException(1, "Ошибка контейнера!", "Переполнение ID адресов!");
			auto it = m_map.find(i);
			if (it == m_map.end())
				return i;
		}
	}
	catch (ContainerException& err)
	{
		err.what();
		exit(-1);
		//return -1;
	}
}

template <class T>
Interface<T>::Interface()             //конструктор
{
	strcpy_s(this->name, 26, "Г Л А В Н О Е     М Е Н Ю");
}

template <class T>
void Interface<T>::show_table(BinaryTree<T>& tree)  //вывод таблицы элементов
{
	T tempObject;
	tempObject.beginOfTable();//вывод начала шапки
	cout << "__";
	tempObject.outputHat();   //вывод шапки таблицы элементов
	cout << "№|";
	tempObject.endOfHat();    //вывод конца шапки
	cout << "_|";
	BinaryTree<T> newTree;
	newTree.setRoot(copyTree(tree.getRoot()));
	newTree.firmwareOfTree();
	int i = 1;
	for(auto it = newTree.begin(); it != nullptr; it++, i++)
		cout << endl << *it << i << "|";
	newTree.clearFirmwareTree();
	//tree.inorder(tree.getRoot()); //симметричный обход
	tempObject.endOfTable();  //вывод конца таблицы элементов
	cout << "_|";
	cout << endl << endl;
}

template <class T>
void Interface<T>::show_table(multimap<int, T>& m_map)  //вывод таблицы элементов
{
	T tempObject;
	tempObject.beginOfTable();//вывод начала шапки
	cout << "__";
	tempObject.outputHat();   //вывод шапки таблицы элементов
	cout << "№|";
	tempObject.endOfHat();    //вывод конца шапки
	cout << "_|";
	for (auto it = m_map.begin(); it != m_map.end(); it++)
		cout << endl << it->second << it->first << "|";
	tempObject.endOfTable();  //вывод конца таблицы элементов
	cout << "_|";
	cout << endl << endl;
}

template <class T>
void Interface<T>::add_element(BinaryTree<T>& tree)
{
	Interface<T> text;
	T tempObject;
	system("cls");                        //очистка экрана
	text.setColor(9);                          //синий
	tempObject.outputClassName();         //вывод названия класса
	text.setColor(7);                          //белый
	cin >> tempObject;                    //ввод элемента
	tree.add(tree.getRoot(), tempObject); //добавление элемента в дерево
	text.setColor(10);                         //ярко-зеленый
	cout << endl << "Элемент добавлен!" << endl << endl;
}

template <class T>
void Interface<T>::add_element(multimap<int, T>& m_map)
{
	Interface<T> text;
	T tempObject;
	system("cls");                        //очистка экрана
	text.setColor(9);                          //синий
	tempObject.outputClassName();         //вывод названия класса
	text.setColor(7);                          //белый
	cin >> tempObject;                    //ввод элемента
	int i = generate_id(m_map);
	m_map.emplace(i, tempObject);
	text.setColor(10);                         //ярко-зеленый
	cout << endl << "Элемент добавлен!" << endl << endl;
}

template <class T>
void Interface<T>::delete_element(BinaryTree<T>& tree)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (tree.empty())   //дерево пустое?
			throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
		system("cls");         //очистка экрана
		iface.setColor(9);           //синий
		tempObject.outputClassName(); //вывод названия класса
		iface.setColor(15);          //ярко-белый
		iface.show_table(tree);      //вывод таблицы элементов

		iface.setColor(13);          //розовый
		cout << "Опишите удаляемый объект." << endl;
		iface.setColor(7);           //белый
		cin >> tempObject;     //ввод объекта
		cout << endl;
		//=============================================================
		//cout << "Выберите номер удаляемого объекта." << endl;
		//int n = get_int(1, tree.size(tree.getRoot()));
		//=============================================================
		
		//-------------------------------------------------------------------------------
		//if (tree.find(tree.getRoot(), tempObject))   //если такой объект нашелся
		//{
		//	if (!(tree.deleteNode(tree.getRoot(), tempObject)))
		//		throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
		//	iface.setColor(10);  //ярко-зеленый
		//	cout << "Объект удален!" << endl << endl;
		//}
		//else
		//{
		//	iface.setColor(12);      //ярко-красный
		//	cout << "Такой элемент не был найден!" << endl << endl;
		//}
		//-------------------------------------------------------------------------------
		
		BinaryTree<T> newTree;
		newTree.setRoot(copyTree(tree.getRoot()));
		newTree.firmwareOfTree();
		Algorithm<T> alg;
		auto it = alg.findFirst(newTree.begin(), newTree.end(), tempObject);
		if (it != nullptr)   //если такой объект нашелся
		{
			//!!! it[n - 1]->getData() == tempObject !!!:
			if (!(tree.deleteNode(tree.getRoot(), tempObject)))
				throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
			iface.setColor(10);  //ярко-зеленый
			cout << "Объект удален!" << endl << endl;
		}
		else
		{
			iface.setColor(12);      //ярко-красный
			cout << "Такой элемент не был найден!" << endl << endl;
		}
		newTree.clearFirmwareTree();
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::delete_element(multimap<int, T>& m_map)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (m_map.empty())   //дерево пустое?
			throw ContainerException(1, "Ошибка контейнера!", "Multimap пуст");
		system("cls");         //очистка экрана
		iface.setColor(9);           //синий
		tempObject.outputClassName(); //вывод названия класса
		iface.setColor(15);          //ярко-белый
		iface.show_table(m_map);      //вывод таблицы элементов
		iface.setColor(13);          //розовый
		cout << "Выберите ключ изменяемого объекта." << endl;
		int n = get_int(1, m_map.size());
		if (m_map.count(n))  //если такой объект нашелся
		{
			m_map.erase(n);
			iface.setColor(10);  //ярко-зеленый
			cout << "Объект удален!" << endl << endl;
		}
		else
		{
			iface.setColor(12);      //ярко-красный
			cout << "Такой элемент не был найден!" << endl << endl;
		}
	}
	catch (ContainerException& err)
	{
		err.what();
	}

}

template <class T>
void Interface<T>::edit_element(BinaryTree<T>& tree)
{
	Interface<T> iface;
	TreeNode<T>* foundedNode;
	T tempObject;
	try
	{
		if (tree.empty())   //дерево пустое?
			throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
		system("cls");  //очистка экрана
		iface.setColor(9);                   //синий
		tempObject.outputClassName();  //вывод названия класса
		iface.setColor(15);       //ярко-белый
		iface.show_table(tree);   //вывод таблицы элементов
		iface.setColor(13);       //розовый
		//cout << "Опишите изменяемый объект." << endl;
		//iface.setColor(7);        //белый
		//cin >> tempObject;  //ввод объекта
		//cout << endl;
		//if (foundedNode = tree.find(tree.getRoot(), tempObject))  //если объект нашелся
		//{
		//	foundedNode->getData().edit(); //редактировать параметры объекта
		//	iface.setColor(10);                  //ярко-зеленый
		//	cout << "Объект изменен!" << endl << endl;
		//}
		//else
		//	throw ContainerException(1, "Ошибка контейнера!", "Объект не найден!");

		cout << "Выберите номер изменяемого объекта." << endl;
		int n = get_int(1, tree.size(tree.getRoot()));
		BinaryTree<T> newTree;
	    newTree.setRoot(copyTree(tree.getRoot()));
	    newTree.firmwareOfTree();
		auto it = newTree.begin();
		it[n - 1]->getData().edit();
		iface.setColor(10);               //ярко-зеленый
		cout << "Объект изменен!" << endl << endl;
		tree.~BinaryTree();
		for (it = newTree.begin(); it != nullptr; it++)
			tree.add(tree.getRoot(), *it);
	    newTree.clearFirmwareTree();
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::edit_element(multimap<int, T>& m_map)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (m_map.empty())   //контейнер пуст?
			throw ContainerException(1, "Ошибка контейнера!", "Multimap пуст");
		system("cls");       //очистка экрана
		iface.setColor(9);             //синий
		tempObject.outputClassName();  //вывод названия класса
		iface.setColor(15);            //ярко-белый
		iface.show_table(m_map);       //вывод таблицы элементов
		iface.setColor(13);            //розовый
		cout << "Выберите номер изменяемого объекта." << endl;
		int n = get_int(1, m_map.size());
		auto it = m_map.find(n);
		it->second.edit();
		iface.setColor(10);               //ярко-зеленый
		cout << "Объект изменен!" << endl << endl;
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}


template <class T>
void Interface<T>::show_elements(BinaryTree<T>& tree)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (!(tree.empty()))          //проверка дерева на пустоту
		{
			system("cls");            //очистка экрана
			iface.setColor(9);              //синий
			tempObject.outputClassName(); //вывод названия класса
			iface.setColor(15);             //ярко-белый
			iface.show_table(tree);         //вывод таблицы элементов
		}
		else
			throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::show_elements(multimap<int, T>& m_map)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (!(m_map.empty()))          //проверка дерева на пустоту
		{
			system("cls");            //очистка экрана
			iface.setColor(9);              //синий
			tempObject.outputClassName(); //вывод названия класса
			iface.setColor(15);             //ярко-белый
			iface.show_table(m_map);         //вывод таблицы элементов
		}
		else
			throw ContainerException(1, "Ошибка контейнера!", "Multimap пуст");
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template<class T>
void Interface<T>::sort_elements(BinaryTree<T>& tree)
{
	try 
	{
		if (tree.empty())
			throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое!");
		T parameter;
		parameter.set_sort_parametres();
		BinaryTree<T> newTree;
	    newTree.setRoot(copyTree(tree.getRoot()));
		newTree.firmwareOfTree();
		tree.~BinaryTree();
		for (auto it = newTree.begin(); it != nullptr; it++)
			tree.addByParameter(tree.getRoot(), *it, parameter);
		newTree.clearFirmwareTree();
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template<class T>
void Interface<T>::sort_elements(multimap<int, T>& m_map)
{
	try
	{
		if (m_map.empty())
			throw ContainerException(1, "Ошибка контейнера!", "Multimap пуст!");
		T parameter;
		parameter.set_sort_parametres();
		Algorithm<T> alg;
		alg.sort(m_map.begin(), m_map.end(), parameter);
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::find_elements(BinaryTree<T>& tree)
{
	Interface<T> iface;
	BinaryTree<T> oldTree, newTree;
	T tempObject;
	char s;
	try
	{
		if (tree.empty())   //дерево пустое?
			throw ContainerException(1, "Ошибка контейнера!", "Дерево пустое");
		system("cls");      //очистка экрана
		iface.setColor(9);  //синий
		tempObject.outputClassName();   //вывод названия класса
		iface.setColor(15);     //ярко-белый
		iface.show_table(tree); //вывод таблицы элементов

		oldTree.setRoot(copyTree(tree.getRoot()));  //копирование дерева tree в oldTree
		do
		{
			rewind(stdin);                          //очистка буфера
			tempObject.choose_search_parametres();  //выборка поисковых параметров
			//---------------------------
			BinaryTree<T> fmTree;
			Algorithm<T> alg;
			fmTree.setRoot(copyTree(oldTree.getRoot()));
			fmTree.firmwareOfTree();
			newTree = alg.findAll(fmTree.begin(), fmTree.end(), tempObject);
			fmTree.clearFirmwareTree();
			//----------------------------
			//oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //поиск элементов в дереве oldTree, найденные элементы будут в newTree
			if (newTree.empty())                    //проверка дерева на пустоту
			{
				iface.setColor(12);                       //ярко-красный
				cout << endl << "По данному запросу ничего не найдено!" << endl << endl;
			}
			else
			{
				iface.setColor(13);             //розовый
				cout << endl << "Результаты поиска:" << endl;
				iface.setColor(15);             //ярко-белый
				iface.show_table(newTree);      //вывод таблицы элементов
				oldTree.~BinaryTree();                          //удаляем старое дерево поиска oldTree
				oldTree.setRoot(copyTree(newTree.getRoot()));   //делаем из newTree НОВОЕ oldTree
				newTree.~BinaryTree();                          //чистим newTree
				newTree.setRoot(nullptr);                       //указатель на корень newTree зануляем
			}
			iface.setColor(14);          //желтый
			cout << "Продолжить поиск?(y\\n)" << endl;
			iface.setColor(7);           //белый
			s = get_char('n', 'y');//ввод признака продолжения или прерывания поиска
		} while (s != 'n');
		oldTree.~BinaryTree();     //вызов деструктора для дерева oldTree
		oldTree.setRoot(nullptr);  //зануление указателя на корень дерева oldTree
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::find_elements(multimap<int, T>& m_map)
{
	Interface<T> iface;
	multimap<int, T> oldMap, newMap;
	T tempObject;
	char s;
	try
	{
		if (m_map.empty())   //multimap пуст?
			throw ContainerException(1, "Ошибка контейнера!", "Multimap пуст");
		system("cls");       //очистка экрана
		iface.setColor(9);   //синий
		tempObject.outputClassName();   //вывод названия класса
		iface.setColor(15);      //ярко-белый
		iface.show_table(m_map); //вывод таблицы элементов
		oldMap = m_map;
		do
		{
			rewind(stdin);                          //очистка буфера
			tempObject.choose_search_parametres();  //выборка поисковых параметров
			for (auto it = oldMap.begin(); it != oldMap.end(); it++)
			{
				if (it->second == tempObject)
				{
					int key = generate_id(newMap);
					newMap.emplace(key, it->second);
				}
			}
			if (newMap.empty())                 //проверка дерева на пустоту
			{
				iface.setColor(12);             //ярко-красный
				cout << endl << "По данному запросу ничего не найдено!" << endl << endl;
			}
			else
			{
				iface.setColor(13);             //розовый
				cout << endl << "Результаты поиска:" << endl;
				iface.setColor(15);             //ярко-белый
				iface.show_table(newMap);       //вывод таблицы элементов
				oldMap.clear();
				oldMap = newMap;
				newMap.clear();
			}
			iface.setColor(14);          //желтый
			cout << "Продолжить поиск?(y\\n)" << endl;
			iface.setColor(7);           //белый
			s = get_char('n', 'y');      //ввод признака продолжения или прерывания поиска
		} while (s != 'n');
		oldMap.clear();
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

