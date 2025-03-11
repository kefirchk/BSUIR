#pragma once
#include "Functions.h"
#include "Interface.h"
#include "Algorithm.h"
#include <limits>
#include <map>
using namespace std;

//====================================== ������� ���� ==========================================
template<class T>
void Interface<T>::mainMenu()      //����� �������� ����
{
	int choice, cont;
	do {
		cont = menu_workContainer();
		if (cont == 3) return;
		else
		{
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
				multimap <int, Monoblock> m_map;
				system("cls");
				if (cont == 1)
					object.subMenu(tree);
				else
					object.subMenu_withMultimap(m_map);
			} break;
			case 2: //������ � ������� ��������
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
			case 3: //������ � ������� �������
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
				setColor(7);        //�����
				return;
			}
		}
	} while (1);
}
//====================================== ������� ==========================================
template<class T>
void Interface<T>::subMenu_withMultimap(multimap<int, T>& m_map)
{
	T tempObject;
	string filename = choosing_file(tempObject);
	TxtFile<T> file_txt((filename + TXT).c_str());
	BinFile<T> file_bin((filename + BIN).c_str());
	int choice;             //���������� ��� ������ �����
	setColor(9);            //�����
	tempObject.outputClassName(); //����� �������� ������
	do {
		multimap<int, T> tempMultiMapForBin;
		multimap<int, T> tempMultiMapForTxt;
		rewind(stdin);      //������� ������
		instructions();
	    choice = get_int(1, 17);
		switch (choice)
		{
			//-------------------------------------������� �������� � ������----------------------------------------------------
		case 1:
			add_element(m_map);
			break;
			//-------------------------------------��������� �������� ������----------------------------------------------------
		case 2:
			edit_element(m_map);
			break;
			//-------------------------------------�������� �������� �� ������--------------------------------------------------
		case 3:
			delete_element(m_map);
			break;
			//-------------------------------------����� ������ �� �����--------------------------------------------------------
		case 4:
			show_elements(m_map);
			break;
			//-------------------------------------���������� ������� ��������--------------------------------------------------
		case 5:
			sort_elements(m_map);
			setColor(GREEN);
			cout << endl << "��������� ������� ������������!" << endl << endl;
			break;
			//-------------------------------------����� ���������� ��������� � ������������ ������-----------------------------
		case 6:
			find_elements(m_map);
			break;
			//-------------------------------------��������� ���������� �� BIN-�����--------------------------------------------
		case 7:
			if (file_bin.openBinFile(ios::in))
				file_bin.readFromFile(tempMultiMapForBin);
			break;
			//-------------------------------------�������� ���������� � BIN-����-----------------------------------------------
		case 8:
			if (file_bin.openBinFile(ios::app))
				file_bin.writeInFile(m_map);
			break;
			//-------------------------------------������������ ���������� � BIN-����-------------------------------------------
		case 9:
			if (file_bin.openBinFile(ios::out | ios::trunc))
				file_bin.writeInFile(m_map);
			break;
			//-------------------------------------�������� ����������� ���������� � ������� ������-----------------------------
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
					cout << endl << "���������� ������� ��������� � multimap!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------������� ����-----------------------------------------------------------------
		case 11:
			file_bin.remove_file();
			break;
			//-------------------------------------��������� ���������� �� TXT-�����--------------------------------------------
		case 12:
			if (file_txt.openForRead())
				file_txt.readFromFile(tempMultiMapForTxt);
			break;
			//-------------------------------------�������� ���������� � TXT-����-----------------------------------------------
		case 13:
			if (file_txt.openForWrite(ios::app))
				file_txt.writeInFile(m_map);
			break;
			//-------------------------------------������������ ���������� � TXT-����-------------------------------------------
		case 14:
			if (file_txt.openForWrite(ios::out | ios::trunc))
				file_txt.writeInFile(m_map);
			break;
			//-------------------------------------�������� ����������� ���������� � ������� ������-----------------------------
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
					cout << endl << "���������� ������� ��������� � multimap!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------������� ����-----------------------------------------------------------------
		case 16:
			file_txt.remove_file();
			break;
			//-------------------------------------����� �� ������� ������ � �������--------------------------------------------
		case 17:
			system("cls");  //������� ������
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
	int choice;             //���������� ��� ������ �����
	setColor(9);            //�����
	tempObject.outputClassName(); //����� �������� ������
	do {
		BinaryTree<T> tempTreeForBin;
		BinaryTree<T> tempTreeForTxt;
		rewind(stdin);      //������� ������
		instructions();
		choice = get_int(1, 17);
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
			//-------------------------------------���������� ������� ��������--------------------------------------------------
		case 5:
			sort_elements(tree);
			setColor(GREEN);
			cout << endl << "��������� ������� ������������!" << endl << endl;
			break;
			//-------------------------------------����� ���������� ��������� � ������������ ������-----------------------------
		case 6:
			find_elements(tree);
			break;
			//-------------------------------------��������� ���������� �� BIN-�����--------------------------------------------
		case 7: 
			if (file_bin.openBinFile(ios::in))
				file_bin.readFromFile(tempTreeForBin);
			break;
			//-------------------------------------�������� ���������� � BIN-����-----------------------------------------------
		case 8:
			if (file_bin.openBinFile(ios::app))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------������������ ���������� � BIN-����-------------------------------------------
		case 9:
			if (file_bin.openBinFile(ios::out | ios::trunc))
				file_bin.writeInFile(tree);
			break;
			//-------------------------------------�������� ����������� ���������� � ������� ������-----------------------------
		case 10:
			if (file_bin.openBinFile(ios::in))
			{
				file_bin.readFromFile(tempTreeForBin);
				if (!tempTreeForBin.empty())
				{
					tree.uniteTrees(tempTreeForBin);
					setColor(GREEN);
					cout << endl << "���������� ������� ��������� � ������!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------������� ����-----------------------------------------------------------------
		case 11:
			file_bin.remove_file();
			break;
			//-------------------------------------��������� ���������� �� TXT-�����--------------------------------------------
		case 12: 
			if (file_txt.openForRead())
				file_txt.readFromFile(tempTreeForTxt);
			break;
			//-------------------------------------�������� ���������� � TXT-����-----------------------------------------------
		case 13: 
			if (file_txt.openForWrite(ios::app))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------������������ ���������� � TXT-����-------------------------------------------
		case 14: 
			if (file_txt.openForWrite(ios::out | ios::trunc))
				file_txt.writeInFile(tree);
			break;
			//-------------------------------------�������� ����������� ���������� � ������� ������-----------------------------
		case 15:
			if (file_txt.openForRead())
			{
				file_txt.readFromFile(tempTreeForTxt);
				if (!tempTreeForTxt.empty())
				{
					tree.uniteTrees(tempTreeForTxt);
					setColor(GREEN);
					cout << endl << "���������� ������� ��������� � ������!" << endl << endl;
					setColor(WHITE);
				}
			}
			break;
			//-------------------------------------������� ����-----------------------------------------------------------------
		case 16: 
			file_txt.remove_file();
			break;
			//-------------------------------------����� �� ������� ������ � �������--------------------------------------------
		case 17:
			system("cls");  //������� ������
			return;
		}
	} while (1);
}


template <class T>
int Interface<T>::menu_workContainer()
{
	int choice;
	rewind(stdin);      //������ ������
	setColor(10);       //���������
	this->outputName();
	setColor(13);       //�������
	cout << setw(60) << "�������� ���������, � ������� ������ ��������:" << endl;
	setColor(7);        //�����
	cout << setw(48) << "->> 1. BinaryTree <<-" << endl;
	cout << setw(46) << "->> 2. Multimap <<-" << endl;
	setColor(RED);
	cout << setw(43) << "->> 3. ����� <<-" << endl;
	setColor(7);        //�����
	choice = get_int(1, 3);
	system("cls");
	return choice;
}


template<class T>
void Interface<T>::instructions()
{
	setColor(13);       //�������
	cout << "�������� �����:" << endl;
	setColor(TURQUOISE);
	cout << "--------����������� ��������--------" << endl;
	setColor(7);        //�����
	cout << "1. �������� �������" << endl
		<< "2. �������� �������" << endl
		<< "3. ������� �������" << endl
		<< "4. ������� ������ ���������" << endl
		<< "5. �����������" << endl
		<< "6. �����" << endl;
	setColor(TURQUOISE);
	cout << "-------�������� � BIN-�������--------" << endl;
	setColor(7);        //�����
	cout << "7. ��������� ����������" << endl
		<< "8. �������� ����������" << endl
		<< "9. ������������ ����������" << endl
		<< "10. �������� ����������� ���������� � ������� ���������" << endl
		<< "11. ������� ����" << endl;
	setColor(TURQUOISE);
	cout << "-------�������� � TXT-�������--------" << endl;
	setColor(7);        //�����
	cout << "12. ��������� ����������" << endl
		<< "13. �������� ����������" << endl
		<< "14. ������������ ����������" << endl
		<< "15. �������� ����������� ���������� � ������� ���������" << endl
		<< "16. ������� ����" << endl;
	setColor(TURQUOISE);
	cout << "-------------------------------------" << endl;
	setColor(14);       //������
	cout << "17. <-|�����|<-" << endl;
	setColor(7);        //�����
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

template<class T>
int generate_id(multimap<int, T>& m_map)
{
	try
	{
		int i = 1;
		for (; i < SHRT_MAX; i++)
		{
			if (i == SHRT_MAX - 1)
				throw ContainerException(1, "������ ����������!", "������������ ID �������!");
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
Interface<T>::Interface()             //�����������
{
	strcpy_s(this->name, 26, "� � � � � � �     � � � �");
}

template <class T>
void Interface<T>::show_table(BinaryTree<T>& tree)  //����� ������� ���������
{
	T tempObject;
	tempObject.beginOfTable();//����� ������ �����
	cout << "__";
	tempObject.outputHat();   //����� ����� ������� ���������
	cout << "�|";
	tempObject.endOfHat();    //����� ����� �����
	cout << "_|";
	BinaryTree<T> newTree;
	newTree.setRoot(copyTree(tree.getRoot()));
	newTree.firmwareOfTree();
	int i = 1;
	for(auto it = newTree.begin(); it != nullptr; it++, i++)
		cout << endl << *it << i << "|";
	newTree.clearFirmwareTree();
	//tree.inorder(tree.getRoot()); //������������ �����
	tempObject.endOfTable();  //����� ����� ������� ���������
	cout << "_|";
	cout << endl << endl;
}

template <class T>
void Interface<T>::show_table(multimap<int, T>& m_map)  //����� ������� ���������
{
	T tempObject;
	tempObject.beginOfTable();//����� ������ �����
	cout << "__";
	tempObject.outputHat();   //����� ����� ������� ���������
	cout << "�|";
	tempObject.endOfHat();    //����� ����� �����
	cout << "_|";
	for (auto it = m_map.begin(); it != m_map.end(); it++)
		cout << endl << it->second << it->first << "|";
	tempObject.endOfTable();  //����� ����� ������� ���������
	cout << "_|";
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
void Interface<T>::add_element(multimap<int, T>& m_map)
{
	Interface<T> text;
	T tempObject;
	system("cls");                        //������� ������
	text.setColor(9);                          //�����
	tempObject.outputClassName();         //����� �������� ������
	text.setColor(7);                          //�����
	cin >> tempObject;                    //���� ��������
	int i = generate_id(m_map);
	m_map.emplace(i, tempObject);
	text.setColor(10);                         //����-�������
	cout << endl << "������� ��������!" << endl << endl;
}

template <class T>
void Interface<T>::delete_element(BinaryTree<T>& tree)
{
	Interface<T> iface;
	T tempObject;
	try
	{
		if (tree.empty())   //������ ������?
			throw ContainerException(1, "������ ����������!", "������ ������");
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
		//=============================================================
		//cout << "�������� ����� ���������� �������." << endl;
		//int n = get_int(1, tree.size(tree.getRoot()));
		//=============================================================
		
		//-------------------------------------------------------------------------------
		//if (tree.find(tree.getRoot(), tempObject))   //���� ����� ������ �������
		//{
		//	if (!(tree.deleteNode(tree.getRoot(), tempObject)))
		//		throw ContainerException(1, "������ ����������!", "������ ������");
		//	iface.setColor(10);  //����-�������
		//	cout << "������ ������!" << endl << endl;
		//}
		//else
		//{
		//	iface.setColor(12);      //����-�������
		//	cout << "����� ������� �� ��� ������!" << endl << endl;
		//}
		//-------------------------------------------------------------------------------
		
		BinaryTree<T> newTree;
		newTree.setRoot(copyTree(tree.getRoot()));
		newTree.firmwareOfTree();
		Algorithm<T> alg;
		auto it = alg.findFirst(newTree.begin(), newTree.end(), tempObject);
		if (it != nullptr)   //���� ����� ������ �������
		{
			//!!! it[n - 1]->getData() == tempObject !!!:
			if (!(tree.deleteNode(tree.getRoot(), tempObject)))
				throw ContainerException(1, "������ ����������!", "������ ������");
			iface.setColor(10);  //����-�������
			cout << "������ ������!" << endl << endl;
		}
		else
		{
			iface.setColor(12);      //����-�������
			cout << "����� ������� �� ��� ������!" << endl << endl;
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
		if (m_map.empty())   //������ ������?
			throw ContainerException(1, "������ ����������!", "Multimap ����");
		system("cls");         //������� ������
		iface.setColor(9);           //�����
		tempObject.outputClassName(); //����� �������� ������
		iface.setColor(15);          //����-�����
		iface.show_table(m_map);      //����� ������� ���������
		iface.setColor(13);          //�������
		cout << "�������� ���� ����������� �������." << endl;
		int n = get_int(1, m_map.size());
		if (m_map.count(n))  //���� ����� ������ �������
		{
			m_map.erase(n);
			iface.setColor(10);  //����-�������
			cout << "������ ������!" << endl << endl;
		}
		else
		{
			iface.setColor(12);      //����-�������
			cout << "����� ������� �� ��� ������!" << endl << endl;
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
		if (tree.empty())   //������ ������?
			throw ContainerException(1, "������ ����������!", "������ ������");
		system("cls");  //������� ������
		iface.setColor(9);                   //�����
		tempObject.outputClassName();  //����� �������� ������
		iface.setColor(15);       //����-�����
		iface.show_table(tree);   //����� ������� ���������
		iface.setColor(13);       //�������
		//cout << "������� ���������� ������." << endl;
		//iface.setColor(7);        //�����
		//cin >> tempObject;  //���� �������
		//cout << endl;
		//if (foundedNode = tree.find(tree.getRoot(), tempObject))  //���� ������ �������
		//{
		//	foundedNode->getData().edit(); //������������� ��������� �������
		//	iface.setColor(10);                  //����-�������
		//	cout << "������ �������!" << endl << endl;
		//}
		//else
		//	throw ContainerException(1, "������ ����������!", "������ �� ������!");

		cout << "�������� ����� ����������� �������." << endl;
		int n = get_int(1, tree.size(tree.getRoot()));
		BinaryTree<T> newTree;
	    newTree.setRoot(copyTree(tree.getRoot()));
	    newTree.firmwareOfTree();
		auto it = newTree.begin();
		it[n - 1]->getData().edit();
		iface.setColor(10);               //����-�������
		cout << "������ �������!" << endl << endl;
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
		if (m_map.empty())   //��������� ����?
			throw ContainerException(1, "������ ����������!", "Multimap ����");
		system("cls");       //������� ������
		iface.setColor(9);             //�����
		tempObject.outputClassName();  //����� �������� ������
		iface.setColor(15);            //����-�����
		iface.show_table(m_map);       //����� ������� ���������
		iface.setColor(13);            //�������
		cout << "�������� ����� ����������� �������." << endl;
		int n = get_int(1, m_map.size());
		auto it = m_map.find(n);
		it->second.edit();
		iface.setColor(10);               //����-�������
		cout << "������ �������!" << endl << endl;
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
			throw ContainerException(1, "������ ����������!", "������ ������");
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
		if (!(m_map.empty()))          //�������� ������ �� �������
		{
			system("cls");            //������� ������
			iface.setColor(9);              //�����
			tempObject.outputClassName(); //����� �������� ������
			iface.setColor(15);             //����-�����
			iface.show_table(m_map);         //����� ������� ���������
		}
		else
			throw ContainerException(1, "������ ����������!", "Multimap ����");
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
			throw ContainerException(1, "������ ����������!", "������ ������!");
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
			throw ContainerException(1, "������ ����������!", "Multimap ����!");
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
		if (tree.empty())   //������ ������?
			throw ContainerException(1, "������ ����������!", "������ ������");
		system("cls");      //������� ������
		iface.setColor(9);  //�����
		tempObject.outputClassName();   //����� �������� ������
		iface.setColor(15);     //����-�����
		iface.show_table(tree); //����� ������� ���������

		oldTree.setRoot(copyTree(tree.getRoot()));  //����������� ������ tree � oldTree
		do
		{
			rewind(stdin);                          //������� ������
			tempObject.choose_search_parametres();  //������� ��������� ����������
			//---------------------------
			BinaryTree<T> fmTree;
			Algorithm<T> alg;
			fmTree.setRoot(copyTree(oldTree.getRoot()));
			fmTree.firmwareOfTree();
			newTree = alg.findAll(fmTree.begin(), fmTree.end(), tempObject);
			fmTree.clearFirmwareTree();
			//----------------------------
			//oldTree.findAll(oldTree.getRoot(), tempObject, newTree); //����� ��������� � ������ oldTree, ��������� �������� ����� � newTree
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
		if (m_map.empty())   //multimap ����?
			throw ContainerException(1, "������ ����������!", "Multimap ����");
		system("cls");       //������� ������
		iface.setColor(9);   //�����
		tempObject.outputClassName();   //����� �������� ������
		iface.setColor(15);      //����-�����
		iface.show_table(m_map); //����� ������� ���������
		oldMap = m_map;
		do
		{
			rewind(stdin);                          //������� ������
			tempObject.choose_search_parametres();  //������� ��������� ����������
			for (auto it = oldMap.begin(); it != oldMap.end(); it++)
			{
				if (it->second == tempObject)
				{
					int key = generate_id(newMap);
					newMap.emplace(key, it->second);
				}
			}
			if (newMap.empty())                 //�������� ������ �� �������
			{
				iface.setColor(12);             //����-�������
				cout << endl << "�� ������� ������� ������ �� �������!" << endl << endl;
			}
			else
			{
				iface.setColor(13);             //�������
				cout << endl << "���������� ������:" << endl;
				iface.setColor(15);             //����-�����
				iface.show_table(newMap);       //����� ������� ���������
				oldMap.clear();
				oldMap = newMap;
				newMap.clear();
			}
			iface.setColor(14);          //������
			cout << "���������� �����?(y\\n)" << endl;
			iface.setColor(7);           //�����
			s = get_char('n', 'y');      //���� �������� ����������� ��� ���������� ������
		} while (s != 'n');
		oldMap.clear();
	}
	catch (ContainerException& err)
	{
		err.what();
	}
}

