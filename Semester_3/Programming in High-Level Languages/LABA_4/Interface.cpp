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
		cin >> choice;
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
		default: 
			system("cls");
			setColor(12);       //ярко-красный
			cout << "Ошибка! Такого класса не существует." << endl;
			break;
		}
	} while (1);
}
//====================================== ПОДМЕНЮ ==========================================
template<class T>
void Interface<T>::subMenu(BinaryTree<T>& tree)
{
	int choice;             //переменная для выбора опции
	BinaryTree<T> newTree;  //новое дерево, сформированное в результате поиска
	BinaryTree<T> oldTree;  //дерево, в котором осуществлялся поиск
	TreeNode<T>* foundedNode; //найденный узел при поиске
	char s;                 //признак продолжения поиска или его прерывания
	setColor(9);            //синий
	newTree.getRoot()->getData().outputClassName(); //вывод названия класса
	do {
		T tempObject;
		foundedNode = nullptr;
		rewind(stdin);      //очистка буфера
		setColor(13);       //розовый
		cout << "Выберите опцию:" << endl;
	    setColor(7);        //белый
		cout << "1. Добавить элемент" << endl
			<< "2. Изменить элемент" << endl
			<< "3. Удалить элемент" << endl
			<< "4. Вывести дерево элементов" << endl
			<< "5. Поиск" << endl;
		setColor(14);       //желтый
		cout << "6. <-|НАЗАД|<-" << endl;
		setColor(7);        //белый
		cin >> choice;
		switch (choice)
		{
//-------------------------------------ВСТАВКА ЭЛЕМЕНТА В ДЕРЕВО----------------------------------------------------
		case 1:
			system("cls");                        //очистка экрана
			setColor(9);                          //синий
			tempObject.outputClassName();         //вывод названия класса
			setColor(7);                          //белый
			cin >> tempObject;                    //ввод элемента
			tree.add(tree.getRoot(), tempObject); //добавление элемента в дерево
			setColor(10);                         //ярко-зеленый
			cout << endl << "Элемент добавлен!" << endl << endl;
			break;
//-------------------------------------ИЗМЕНЕНИЕ ЭЛЕМЕНТА ДЕРЕВА----------------------------------------------------
		case 2:
			if (tree.empty())   //дерево пустое?
			{
				setColor(12);   //ярко-красный
				cout << endl << "Дерево пустое!" << endl << endl;
			}
			else                //дерево не пустое
			{
				system("cls");  //очистка экрана
				setColor(9);                   //синий
				tempObject.outputClassName();  //вывод названия класса
				setColor(15);             //ярко-белый

				tempObject.beginOfTable();//вывод начала шапки
				tempObject.outputHat();   //вывод шапки таблицы элементов
				tempObject.endOfHat();    //вывод конца шапки
				tree.inorder(tree.getRoot()); //симметричный обход
				tempObject.endOfTable();  //вывод конца таблицы элементов
				cout << endl << endl;

				setColor(13);   //розовый
				cout << "Опишите изменяемый объект." << endl;
			    setColor(7);    //белый
				cin >> tempObject;  //ввод объекта
				cout << endl;
				if (foundedNode = tree.find(tree.getRoot(), tempObject))  //если объект нашелся
				{
					foundedNode->getData().edit(); //редактировать параметры объекта
					setColor(10);                  //ярко-зеленый
					cout << "Объект изменен!" << endl << endl;
				}
				else
				{
					setColor(12);   //ярко-красный
					cout << "Объект не найден!" << endl << endl;
				}
			}
			break;
//-------------------------------------УДАЛЕНИЕ ЭЛЕМЕНТА ИЗ ДЕРЕВА--------------------------------------------------
		case 3:
			if (tree.empty())   //дерево пустое?
			{
				setColor(12);   //ярко-красный
				cout << endl << "Дерево пустое!" << endl << endl;
			}
			else
			{
				system("cls");         //очистка экрана
				setColor(9);           //синий
				tempObject.outputClassName(); //вывод названия класса

				setColor(15);             //ярко-белый
				tempObject.beginOfTable();//вывод начала шапки
				tempObject.outputHat();   //вывод шапки таблицы элементов
				tempObject.endOfHat();    //вывод конца шапки
				tree.inorder(tree.getRoot()); //симметричный обход
				tempObject.endOfTable();  //вывод конца таблицы элементов
				cout << endl << endl;

				setColor(13);          //розовый
				cout << "Опишите удаляемый объект." << endl;
				setColor(7);           //белый
				cin >> tempObject;     //ввод объекта
				cout << endl;
				if (tree.find(tree.getRoot(), tempObject))   //если такой объект нашелся
				{
					if (!(tree.deleteNode(tree.getRoot(), tempObject)))
					{
						setColor(12);  //ярко-красный
						cout << endl << "Дерево пустое!" << endl << endl;
					}
					else
					{
						setColor(10);  //ярко-зеленый
						cout << "Объект удален!" << endl << endl;
					}
				}
				else
				{
					setColor(12);      //ярко-красный
					cout << "Такой элемент не был найден!" << endl << endl;
				}
			}
			break;
//-------------------------------------ВЫВОД ДЕРЕВА НА ЭКРАН--------------------------------------------------------
		case 4:
			if (!(tree.empty()))          //проверка дерева на пустоту
			{
				system("cls");            //очистка экрана
				setColor(9);              //синий
				tempObject.outputClassName(); //вывод названия класса
				setColor(15);             //ярко-белый
			
				tempObject.beginOfTable();//вывод начала шапки
				tempObject.outputHat();   //вывод шапки таблицы элементов
				tempObject.endOfHat();    //вывод конца шапки
				tree.inorder(tree.getRoot()); //симметричный обход
				tempObject.endOfTable();  //вывод конца таблицы элементов
				cout << endl << endl;
			}
			else
			{
				setColor(12);             //ярко-красный
				cout << endl << "Дерево пустое!" << endl << endl;
			}
			break;
//-------------------------------------ПОИСК НЕСКОЛЬКИХ ЭЛЕМЕНТОВ С ПРОДОЛЖЕНИЕМ ПОИСКА-----------------------------
		case 5:
			if (tree.empty())   //дерево пустое?
			{
				setColor(12);   //ярко-красный
				cout << endl << "Дерево пустое!" << endl << endl;
			}
			else
			{
				system("cls");  //очистка экрана
				setColor(9);    //синий
				tempObject.outputClassName();               //вывод названия класса
				setColor(15);             //ярко-белый
				
				tempObject.beginOfTable();//вывод начала шапки
				tempObject.outputHat();   //вывод шапки таблицы элементов
				tempObject.endOfHat();    //вывод конца шапки
				tree.inorder(tree.getRoot()); //симметричный обход
				tempObject.endOfTable();  //вывод конца таблицы элементов
				cout << endl << endl;

				oldTree.setRoot(copyTree(tree.getRoot()));  //копирование дерева tree в oldTree
				do
				{
					rewind(stdin);                          //очистка буфера
					tempObject.choose_search_parametres();  //выборка поисковых параметров
					oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //поиск элементов в дереве oldTree, найденные элементы будут в newTree
					if (newTree.empty())                    //проверка дерева на пустоту
					{
						setColor(12);                       //ярко-красный
						cout << endl << "По данному запросу ничего не найдено!" << endl << endl;
					}
					else
					{
						setColor(13);             //розовый
						cout << endl << "Результаты поиска:" << endl;
						setColor(15);             //ярко-белый
						
						tempObject.beginOfTable();//вывод начала шапки
						tempObject.outputHat();   //вывод шапки таблицы элементов
						tempObject.endOfHat();    //вывод конца шапки
						newTree.inorder(newTree.getRoot()); //симметричный обход
						tempObject.endOfTable();  //вывод конца таблицы элементов
						cout << endl << endl;

						oldTree.~BinaryTree();                          //удаляем старое дерево поиска oldTree
						oldTree.setRoot(copyTree(newTree.getRoot()));   //делаем из newTree НОВОЕ oldTree
						newTree.~BinaryTree();                          //чистим newTree
						newTree.setRoot(nullptr);                       //указатель на корень newTree зануляем
					}
					do  //предложение продолжить поиск в новом дереве поиска newTree
					{
						rewind(stdin);              //очистка буфера ввода
						setColor(14);               //желтый
						cout << "Продолжить поиск?(y\\n)" << endl;
						setColor(7);                //белый
						cin >> s;                   //ввод признака продолжения или прерывания поиска
						if (s != 'n' && s != 'y')   //проверка на корректность ввода символа
						{
							setColor(12);           //ярко-красный
							cout << endl << "Ошибка!" << endl;
						}
					} while (s != 'n' && s != 'y'); //пока не введен корректный символ продолжения или прерывания поиска
				} while (s != 'n');
				oldTree.~BinaryTree();     //вызов деструктора для дерева oldTree
				oldTree.setRoot(nullptr);  //зануление указателя на корень дерева oldTree
			}
			break;
//-------------------------------------ВЫХОД ИЗ ПОДМЕНЮ РАБОТЫ С КЛАССОМ--------------------------------------------
		case 6:
			system("cls");  //очистка экрана
			return;
		default:
			system("cls");  //очистка экрана
			setColor(12);   //ярко-красный
			cout << "Ошибка! Нет такой опции." << endl;
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

//template <class T>
//void show(T &obj, BinaryTree<T> &tree)
//{
//	obj.beginOfTable();//вывод начала шапки
//	obj.outputHat();   //вывод шапки таблицы элементов
//	obj.endOfHat();    //вывод конца шапки
//	tree.inorder(tree.getRoot()); //симметричный обход
//	obj.endOfTable();  //вывод конца таблицы элементов
//	cout << endl << endl;
//}