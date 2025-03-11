#pragma once
#include "Functions.h"
#include "Interface.h"
#include "Algorithm.h"

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
		}
	} while (1);
}
//====================================== ������� ==========================================
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
			<< "10. �������� ����������� ���������� � ������� ������" << endl
			<< "11. ������� ����" << endl;
		setColor(TURQUOISE);
		cout << "-------�������� � TXT-�������--------" << endl;
		setColor(7);        //�����
		cout << "12. ��������� ����������" << endl
			<< "13. �������� ����������" << endl
			<< "14. ������������ ����������" << endl
			<< "15. �������� ����������� ���������� � ������� ������" << endl
			<< "16. ������� ����" << endl;
		setColor(TURQUOISE);
		cout << "-------------------------------------" << endl;
		setColor(14);       //������
		cout << "17. <-|�����|<-" << endl;
		setColor(7);        //�����
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

		BinaryTree<T> newTree;
		newTree.setRoot(copyTree(tree.getRoot()));
		newTree.firmwareOfTree();
		Algorithm<T> alg;
		auto it = alg.findFirst(newTree.begin(), newTree.end(), tempObject);
		if (it != nullptr)   //���� ����� ������ �������
		{
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

