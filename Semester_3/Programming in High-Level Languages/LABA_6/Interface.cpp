#pragma once
#include "Functions.h"
#include "Interface.h"

//====================================== ГЛАВНОЕ МЕНЮ ==========================================
template<class T>
void Interface<T>::mainMenu()      //метод главного меню
{
	int choice;
	do {
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
			system("cls");
			object.subMenu(tree);
		} break;
		case 2: //работа с классом Смартфон
		{
			Interface<Smartphone> object;
			BinaryTree<Smartphone> tree;
			system("cls");
			object.subMenu(tree);
		} break;
		case 3: //работа с классом Ноутбук
		{
			Interface<Notebook> object;
			BinaryTree<Notebook> tree;
			system("cls");
			object.subMenu(tree);
		} break;
		case 4:
			setColor(7);        //белый
			return;
		}
	} while (1);
}
//====================================== ПОДМЕНЮ ==========================================
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
		setColor(13);       //розовый
		cout << "Выберите опцию:" << endl;
		setColor(TURQUOISE);
		cout << "--------СТАНДАРТНЫЕ ОПЕРАЦИИ--------" << endl;
	    setColor(7);        //белый
		cout << "1. Добавить элемент" << endl
			<< "2. Изменить элемент" << endl
			<< "3. Удалить элемент" << endl
			<< "4. Вывести дерево элементов" << endl
			<< "5. Найти элемент" << endl;
		setColor(TURQUOISE);
		cout << "-------ОПЕРАЦИИ С BIN-ФАЙЛАМИ--------" << endl;
		setColor(7);        //белый
		cout << "6. Прочитать информацию" << endl
			<< "7. Дописать информацию" << endl
			<< "8. Перезаписать информацию" << endl
			<< "9. Добавить прочитанную информацию в главное дерево" << endl
			<< "10. Удалить файл" << endl;
		setColor(TURQUOISE);
		cout << "-------ОПЕРАЦИИ С TXT-ФАЙЛАМИ--------" << endl;
		setColor(7);        //белый
		cout << "11. Прочитать информацию" << endl
			<< "12. Дописать информацию" << endl
			<< "13. Перезаписать информацию" << endl
			<< "14. Добавить прочитанную информацию в главное дерево" << endl
			<< "15. Удалить файл" << endl;
		setColor(TURQUOISE);
		cout << "-------------------------------------" << endl;
		setColor(14);       //желтый
		cout << "16. <-|НАЗАД|<-" << endl;
		setColor(7);        //белый
		choice = get_int(1, 16);
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
			//-------------------------------------ПОИСК НЕСКОЛЬКИХ ЭЛЕМЕНТОВ С ПРОДОЛЖЕНИЕМ ПОИСКА-----------------------------
		case 5:
			find_elements(tree);
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ BIN-ФАЙЛА--------------------------------------------
		case 6: 
			if (file_bin.openBinFile(ios::in))
				file_bin.readFromFile(tempTreeForBin);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-----------------------------------------------
		case 7:
			if (file_bin.openBinFile(ios::app))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В BIN-ФАЙЛ-------------------------------------------
		case 8:
			if (file_bin.openBinFile(ios::out | ios::trunc))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 9:
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
		case 10:
			file_bin.remove_file();
			break;
			//-------------------------------------ПРОЧИТАТЬ ИНФОРМАЦИЮ ИЗ TXT-ФАЙЛА--------------------------------------------
		case 11: 
			if (file_txt.openForRead())
				file_txt.readFromFile(tempTreeForTxt);
			break;
			//-------------------------------------ДОПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-----------------------------------------------
		case 12: 
			if (file_txt.openForWrite(ios::app))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------ПЕРЕЗАПИСАТЬ ИНФОРМАЦИЮ В TXT-ФАЙЛ-------------------------------------------
		case 13: 
			if (file_txt.openForWrite(ios::out | ios::trunc))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------ДОБАВИТЬ ПРОЧИТАННУЮ ИНФОРМАЦИЮ В ГЛАВНОЕ ДЕРЕВО-----------------------------
		case 14:
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
		case 15: 
			file_txt.remove_file();
			break;
			//-------------------------------------ВЫХОД ИЗ ПОДМЕНЮ РАБОТЫ С КЛАССОМ--------------------------------------------
		case 16:
			system("cls");  //очистка экрана
			return;
		}
	} while (1);
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
	tempObject.outputHat();   //вывод шапки таблицы элементов
	tempObject.endOfHat();    //вывод конца шапки
	tree.inorder(tree.getRoot()); //симметричный обход
	tempObject.endOfTable();  //вывод конца таблицы элементов
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
		if (tree.find(tree.getRoot(), tempObject))   //если такой объект нашелся
		{
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
		cout << "Опишите изменяемый объект." << endl;
		iface.setColor(7);        //белый
		cin >> tempObject;  //ввод объекта
		cout << endl;
		if (foundedNode = tree.find(tree.getRoot(), tempObject))  //если объект нашелся
		{
			foundedNode->getData().edit(); //редактировать параметры объекта
			iface.setColor(10);                  //ярко-зеленый
			cout << "Объект изменен!" << endl << endl;
		}
		else
			throw ContainerException(1, "Ошибка контейнера!", "Объект не найден!");
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
		system("cls");  //очистка экрана
		iface.setColor(9);    //синий
		tempObject.outputClassName();   //вывод названия класса
		iface.setColor(15);     //ярко-белый
		iface.show_table(tree); //вывод таблицы элементов

		oldTree.setRoot(copyTree(tree.getRoot()));  //копирование дерева tree в oldTree
		do
		{
			rewind(stdin);                          //очистка буфера
			tempObject.choose_search_parametres();  //выборка поисковых параметров
			oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //поиск элементов в дереве oldTree, найденные элементы будут в newTree
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

