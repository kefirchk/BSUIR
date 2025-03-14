#pragma once
#include "Functions.h"
#include "Interface.h"
#include "Exception.h"
//====================================== ������� ���� ==========================================
template<class T>
void Interface<T>::mainMenu()      //����� �������� ����
{
	int choice;
	do {
		rewind(stdin);      //������ ������
		setColor(10);       //���������
		this->outputName();
		setColor(13);       //�������
		cout << setw(59) << "�������� �����, � ������� ������ ��������:" << endl;
		setColor(7);        //�����
		cout << setw(48) << "->> 1. ��������� <<-" << endl;
		cout << setw(48) << "->> 2. ��������� <<-" << endl;
		cout << setw(46) << "->> 3. ������� <<-" << endl;
		setColor(12);       //����-�������
		cout << setw(44) << "->> 4. ����� <<-" << endl;
		setColor(7);        //�����
		choice = get_int(1, 4);
		switch (choice)
		{
		case 1: //������ � ������� ��������
		{
			Interface<Monoblock> object;
			BinaryTree<Monoblock> tree;
			system("cls");
			object.subMenu(tree);
		} break;
		case 2: //������ � ������� ��������
		{
			Interface<Smartphone> object;
			BinaryTree<Smartphone> tree;
			system("cls");
			object.subMenu(tree);
		} break;
		case 3: //������ � ������� �������
		{
			Interface<Notebook> object;
			BinaryTree<Notebook> tree;
			system("cls");
			object.subMenu(tree);
		} break;
		case 4:
			setColor(7);        //�����
			return;
		//default:
		//	system("cls");
		//	setColor(12);       //����-�������
		//	cout << "������! ������ ������ �� ����������." << endl;
		//	break;
		}
	} while (1);
}
//====================================== ������� ==========================================
template<class T>
void Interface<T>::subMenu(BinaryTree<T>& tree)
{
	int choice;             //���������� ��� ������ �����
	BinaryTree<T> newTree;  //����� ������, �������������� � ���������� ������
	BinaryTree<T> oldTree;  //������, � ������� ������������� �����
	TreeNode<T>* foundedNode; //��������� ���� ��� ������
	char s;                 //������� ����������� ������ ��� ��� ����������
	setColor(9);            //�����
	newTree.getRoot()->getData().outputClassName(); //����� �������� ������
	do {
		T tempObject;
		foundedNode = nullptr;
		rewind(stdin);      //������� ������
		setColor(13);       //�������
		cout << "�������� �����:" << endl;
		setColor(7);        //�����
		cout << "1. �������� �������" << endl
			<< "2. �������� �������" << endl
			<< "3. ������� �������" << endl
			<< "4. ������� ������ ���������" << endl
			<< "5. ����� �������" << endl;
		setColor(14);       //������
		cout << "6. <-|�����|<-" << endl;
		setColor(7);        //�����
		choice = get_int(1, 6);
		switch (choice)
		{
			//-------------------------------------������� �������� � ������----------------------------------------------------
		case 1:
			add_element(tree);
			break;
			//-------------------------------------��������� �������� ������----------------------------------------------------
		case 2:
			edit_element(tree);
			break;
			//-------------------------------------�������� �������� �� ������--------------------------------------------------
		case 3:
			delete_element(tree);
			break;
			//-------------------------------------����� ������ �� �����--------------------------------------------------------
		case 4:
			show_elements(tree);
			break;
			//-------------------------------------����� ���������� ��������� � ������������ ������-----------------------------
		case 5:
			find_elements(tree);
			break;
			//-------------------------------------����� �� ������� ������ � �������--------------------------------------------
		case 6:
			system("cls");  //������� ������
			return;
		//default:
		//	system("cls");  //������� ������
		//	setColor(12);   //����-�������
		//	cout << "������! ��� ����� �����." << endl;
		}
	} while (1);
}

template <class T>
void Interface<T>::outputName() //����� ������ �� ����� ������ "� � � � � � �   � � � �"
{
	cout << setw(50) << right << "-------------------------" << endl;
	cout << setw(25) << right << '|' << name << '|' << endl;
	cout << setw(50) << right << "-------------------------" << endl;
}

template <class T>
void Interface<T>::setColor(int color)        //����� ������� ����� ������
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color); //������� ����� ������
}

template <class T>
Interface<T>::Interface()             //�����������
{
	strcpy_s(this->name, 26, "� � � � � � �     � � � �");
}

template <class T>
void Interface<T>::show_table(BinaryTree<T>& tree)  //����� ������� ���������
{
	T tempObject;
	tempObject.beginOfTable();//����� ������ �����
	tempObject.outputHat();   //����� ����� ������� ���������
	tempObject.endOfHat();    //����� ����� �����
	tree.inorder(tree.getRoot()); //������������ �����
	tempObject.endOfTable();  //����� ����� ������� ���������
	cout << endl << endl;
}

template <class T>
void Interface<T>::add_element(BinaryTree<T>& tree)
{
	Interface<T> text;
	T tempObject;
	system("cls");                        //������� ������
	text.setColor(9);                          //�����
	tempObject.outputClassName();         //����� �������� ������
	text.setColor(7);                          //�����
	cin >> tempObject;                    //���� ��������
	tree.add(tree.getRoot(), tempObject); //���������� �������� � ������
	text.setColor(10);                         //����-�������
	cout << endl << "������� ��������!" << endl << endl;
}

template <class T>
void Interface<T>::delete_element(BinaryTree<T> &tree)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (tree.empty())   //������ ������?
		{
			//iface.setColor(12);   //����-�������
			throw ContainerException(1, "������ ����������!", "������ ������");
			//cout << endl << "������ ������!" << endl << endl;
		}
		else
		{
			system("cls");         //������� ������
			iface.setColor(9);           //�����
			tempObject.outputClassName(); //����� �������� ������
			iface.setColor(15);          //����-�����
			iface.show_table(tree);      //����� ������� ���������
			iface.setColor(13);          //�������
			cout << "������� ��������� ������." << endl;
			iface.setColor(7);           //�����
			cin >> tempObject;     //���� �������
			cout << endl;
			if (tree.find(tree.getRoot(), tempObject))   //���� ����� ������ �������
			{
				if (!(tree.deleteNode(tree.getRoot(), tempObject)))
				{
					throw ContainerException(1, "������ ����������!", "������ ������");
					//iface.setColor(12);  //����-�������
					//cout << endl << "������ ������!" << endl << endl;
				}
				else
				{
					iface.setColor(10);  //����-�������
					cout << "������ ������!" << endl << endl;
				}
			}
			else
			{
				iface.setColor(12);      //����-�������
				cout << "����� ������� �� ��� ������!" << endl << endl;
			}
		}
	}
	catch (ContainerException& err)
	{
		err.what();
	}
	
}

template <class T>
void Interface<T>::edit_element(BinaryTree<T> &tree)
{
	Interface<T> iface;
	TreeNode<T> *foundedNode;
	T tempObject;
	try
	{
		if (tree.empty())   //������ ������?
		{
			throw ContainerException(1, "������ ����������!", "������ ������");
			//iface.setColor(12);   //����-�������
			//cout << endl << "������ ������!" << endl << endl;
		}
		else                //������ �� ������
		{
			system("cls");  //������� ������
			iface.setColor(9);                   //�����
			tempObject.outputClassName();  //����� �������� ������
			iface.setColor(15);       //����-�����
			iface.show_table(tree);   //����� ������� ���������
			iface.setColor(13);       //�������
			cout << "������� ���������� ������." << endl;
			iface.setColor(7);        //�����
			cin >> tempObject;  //���� �������
			cout << endl;
			if (foundedNode = tree.find(tree.getRoot(), tempObject))  //���� ������ �������
			{
				foundedNode->getData().edit(); //������������� ��������� �������
				iface.setColor(10);                  //����-�������
				cout << "������ �������!" << endl << endl;
			}
			else
			{
				throw ContainerException(1, "������ ����������!", "������ �� ������!");
				//iface.setColor(12);   //����-�������
				//cout << "������ �� ������!" << endl << endl;
			}
		}
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
		if (!(tree.empty()))          //�������� ������ �� �������
		{
			system("cls");            //������� ������
			iface.setColor(9);              //�����
			tempObject.outputClassName(); //����� �������� ������
			iface.setColor(15);             //����-�����
			iface.show_table(tree);         //����� ������� ���������
		}
		else
		{
			throw ContainerException(1, "������ ����������!", "������ ������");
			//iface.setColor(12);             //����-�������
			//cout << endl << "������ ������!" << endl << endl;
		}
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

template <class T>
void Interface<T>::find_elements(BinaryTree<T> &tree)
{
	Interface<T> iface;
	BinaryTree<T> oldTree, newTree;
	T tempObject;
	char s;
	try
	{
		if (tree.empty())   //������ ������?
		{
			throw ContainerException(1, "������ ����������!", "������ ������");
			//iface.setColor(12);   //����-�������
			//cout << endl << "������ ������!" << endl << endl;
		}
		else
		{
			system("cls");  //������� ������
			iface.setColor(9);    //�����
			tempObject.outputClassName();   //����� �������� ������
			iface.setColor(15);     //����-�����
			iface.show_table(tree); //����� ������� ���������

			oldTree.setRoot(copyTree(tree.getRoot()));  //����������� ������ tree � oldTree
			do
			{
				rewind(stdin);                          //������� ������
				tempObject.choose_search_parametres();  //������� ��������� ����������
				oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //����� ��������� � ������ oldTree, ��������� �������� ����� � newTree
				if (newTree.empty())                    //�������� ������ �� �������
				{
					iface.setColor(12);                       //����-�������
					cout << endl << "�� ������� ������� ������ �� �������!" << endl << endl;
				}
				else
				{
					iface.setColor(13);             //�������
					cout << endl << "���������� ������:" << endl;
					iface.setColor(15);             //����-�����
					iface.show_table(newTree);      //����� ������� ���������
					oldTree.~BinaryTree();                          //������� ������ ������ ������ oldTree
					oldTree.setRoot(copyTree(newTree.getRoot()));   //������ �� newTree ����� oldTree
					newTree.~BinaryTree();                          //������ newTree
					newTree.setRoot(nullptr);                       //��������� �� ������ newTree ��������
				}
				iface.setColor(14);          //������
				cout << "���������� �����?(y\\n)" << endl;
				iface.setColor(7);           //�����
				s = get_char('n', 'y');//���� �������� ����������� ��� ���������� ������
			} while (s != 'n');
			oldTree.~BinaryTree();     //����� ����������� ��� ������ oldTree
			oldTree.setRoot(nullptr);  //��������� ��������� �� ������ ������ oldTree
		}
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

