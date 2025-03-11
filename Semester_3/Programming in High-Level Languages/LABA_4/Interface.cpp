#pragma once
#include "Functions.h"
#include "Interface.h"
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
		cin >> choice;
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
		default: 
			system("cls");
			setColor(12);       //����-�������
			cout << "������! ������ ������ �� ����������." << endl;
			break;
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
			<< "5. �����" << endl;
		setColor(14);       //������
		cout << "6. <-|�����|<-" << endl;
		setColor(7);        //�����
		cin >> choice;
		switch (choice)
		{
//-------------------------------------������� �������� � ������----------------------------------------------------
		case 1:
			system("cls");                        //������� ������
			setColor(9);                          //�����
			tempObject.outputClassName();         //����� �������� ������
			setColor(7);                          //�����
			cin >> tempObject;                    //���� ��������
			tree.add(tree.getRoot(), tempObject); //���������� �������� � ������
			setColor(10);                         //����-�������
			cout << endl << "������� ��������!" << endl << endl;
			break;
//-------------------------------------��������� �������� ������----------------------------------------------------
		case 2:
			if (tree.empty())   //������ ������?
			{
				setColor(12);   //����-�������
				cout << endl << "������ ������!" << endl << endl;
			}
			else                //������ �� ������
			{
				system("cls");  //������� ������
				setColor(9);                   //�����
				tempObject.outputClassName();  //����� �������� ������
				setColor(15);             //����-�����

				tempObject.beginOfTable();//����� ������ �����
				tempObject.outputHat();   //����� ����� ������� ���������
				tempObject.endOfHat();    //����� ����� �����
				tree.inorder(tree.getRoot()); //������������ �����
				tempObject.endOfTable();  //����� ����� ������� ���������
				cout << endl << endl;

				setColor(13);   //�������
				cout << "������� ���������� ������." << endl;
			    setColor(7);    //�����
				cin >> tempObject;  //���� �������
				cout << endl;
				if (foundedNode = tree.find(tree.getRoot(), tempObject))  //���� ������ �������
				{
					foundedNode->getData().edit(); //������������� ��������� �������
					setColor(10);                  //����-�������
					cout << "������ �������!" << endl << endl;
				}
				else
				{
					setColor(12);   //����-�������
					cout << "������ �� ������!" << endl << endl;
				}
			}
			break;
//-------------------------------------�������� �������� �� ������--------------------------------------------------
		case 3:
			if (tree.empty())   //������ ������?
			{
				setColor(12);   //����-�������
				cout << endl << "������ ������!" << endl << endl;
			}
			else
			{
				system("cls");         //������� ������
				setColor(9);           //�����
				tempObject.outputClassName(); //����� �������� ������

				setColor(15);             //����-�����
				tempObject.beginOfTable();//����� ������ �����
				tempObject.outputHat();   //����� ����� ������� ���������
				tempObject.endOfHat();    //����� ����� �����
				tree.inorder(tree.getRoot()); //������������ �����
				tempObject.endOfTable();  //����� ����� ������� ���������
				cout << endl << endl;

				setColor(13);          //�������
				cout << "������� ��������� ������." << endl;
				setColor(7);           //�����
				cin >> tempObject;     //���� �������
				cout << endl;
				if (tree.find(tree.getRoot(), tempObject))   //���� ����� ������ �������
				{
					if (!(tree.deleteNode(tree.getRoot(), tempObject)))
					{
						setColor(12);  //����-�������
						cout << endl << "������ ������!" << endl << endl;
					}
					else
					{
						setColor(10);  //����-�������
						cout << "������ ������!" << endl << endl;
					}
				}
				else
				{
					setColor(12);      //����-�������
					cout << "����� ������� �� ��� ������!" << endl << endl;
				}
			}
			break;
//-------------------------------------����� ������ �� �����--------------------------------------------------------
		case 4:
			if (!(tree.empty()))          //�������� ������ �� �������
			{
				system("cls");            //������� ������
				setColor(9);              //�����
				tempObject.outputClassName(); //����� �������� ������
				setColor(15);             //����-�����
			
				tempObject.beginOfTable();//����� ������ �����
				tempObject.outputHat();   //����� ����� ������� ���������
				tempObject.endOfHat();    //����� ����� �����
				tree.inorder(tree.getRoot()); //������������ �����
				tempObject.endOfTable();  //����� ����� ������� ���������
				cout << endl << endl;
			}
			else
			{
				setColor(12);             //����-�������
				cout << endl << "������ ������!" << endl << endl;
			}
			break;
//-------------------------------------����� ���������� ��������� � ������������ ������-----------------------------
		case 5:
			if (tree.empty())   //������ ������?
			{
				setColor(12);   //����-�������
				cout << endl << "������ ������!" << endl << endl;
			}
			else
			{
				system("cls");  //������� ������
				setColor(9);    //�����
				tempObject.outputClassName();               //����� �������� ������
				setColor(15);             //����-�����
				
				tempObject.beginOfTable();//����� ������ �����
				tempObject.outputHat();   //����� ����� ������� ���������
				tempObject.endOfHat();    //����� ����� �����
				tree.inorder(tree.getRoot()); //������������ �����
				tempObject.endOfTable();  //����� ����� ������� ���������
				cout << endl << endl;

				oldTree.setRoot(copyTree(tree.getRoot()));  //����������� ������ tree � oldTree
				do
				{
					rewind(stdin);                          //������� ������
					tempObject.choose_search_parametres();  //������� ��������� ����������
					oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //����� ��������� � ������ oldTree, ��������� �������� ����� � newTree
					if (newTree.empty())                    //�������� ������ �� �������
					{
						setColor(12);                       //����-�������
						cout << endl << "�� ������� ������� ������ �� �������!" << endl << endl;
					}
					else
					{
						setColor(13);             //�������
						cout << endl << "���������� ������:" << endl;
						setColor(15);             //����-�����
						
						tempObject.beginOfTable();//����� ������ �����
						tempObject.outputHat();   //����� ����� ������� ���������
						tempObject.endOfHat();    //����� ����� �����
						newTree.inorder(newTree.getRoot()); //������������ �����
						tempObject.endOfTable();  //����� ����� ������� ���������
						cout << endl << endl;

						oldTree.~BinaryTree();                          //������� ������ ������ ������ oldTree
						oldTree.setRoot(copyTree(newTree.getRoot()));   //������ �� newTree ����� oldTree
						newTree.~BinaryTree();                          //������ newTree
						newTree.setRoot(nullptr);                       //��������� �� ������ newTree ��������
					}
					do  //����������� ���������� ����� � ����� ������ ������ newTree
					{
						rewind(stdin);              //������� ������ �����
						setColor(14);               //������
						cout << "���������� �����?(y\\n)" << endl;
						setColor(7);                //�����
						cin >> s;                   //���� �������� ����������� ��� ���������� ������
						if (s != 'n' && s != 'y')   //�������� �� ������������ ����� �������
						{
							setColor(12);           //����-�������
							cout << endl << "������!" << endl;
						}
					} while (s != 'n' && s != 'y'); //���� �� ������ ���������� ������ ����������� ��� ���������� ������
				} while (s != 'n');
				oldTree.~BinaryTree();     //����� ����������� ��� ������ oldTree
				oldTree.setRoot(nullptr);  //��������� ��������� �� ������ ������ oldTree
			}
			break;
//-------------------------------------����� �� ������� ������ � �������--------------------------------------------
		case 6:
			system("cls");  //������� ������
			return;
		default:
			system("cls");  //������� ������
			setColor(12);   //����-�������
			cout << "������! ��� ����� �����." << endl;
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

//template <class T>
//void show(T &obj, BinaryTree<T> &tree)
//{
//	obj.beginOfTable();//����� ������ �����
//	obj.outputHat();   //����� ����� ������� ���������
//	obj.endOfHat();    //����� ����� �����
//	tree.inorder(tree.getRoot()); //������������ �����
//	obj.endOfTable();  //����� ����� ������� ���������
//	cout << endl << endl;
//}