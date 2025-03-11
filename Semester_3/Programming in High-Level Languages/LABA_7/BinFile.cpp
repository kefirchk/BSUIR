#pragma once
#include "BinFile.h"

template<class T>
bool BinFile<T>::openBinFile(int option)
{
	try
	{
		_stream.open(_fileName, ios::binary | option);
		if (!_stream.good())
			throw FileException(1, "������ �����!", "��������� ������� �����!");
		if (!_stream.is_open())
			throw FileException(2, "������ �������� �����!", "��������� ����������� �����");
		return true;
	}
	catch (FileException& file)
	{
		file.what();
		return false;
	}
}

template<class T>
void BinFile<T>::writeInFile(BinaryTree<T>& tree)
{
	Interface<int> iface;
	if (!tree.empty())
	{
		vector <T> v;
		tree.treeToArray(tree.getRoot(), v);
		for (unsigned int i = 0; i < v.size(); i++)
			_stream << v[i];
		iface.setColor(GREEN);
		cout << endl << "������ ������� ���������!" << endl << endl;
		iface.setColor(WHITE);
		_stream.close();
	}
	else
	{
		iface.setColor(RED);
		cout << endl << "������ ������!" << endl << endl;
		iface.setColor(DARK_WHITE);
	}
}


template <class T>
void BinFile<T>::readFromFile(BinaryTree<T>& tree)
{
	T obj;
	while (!_stream.eof())
	{
		if (!(_stream >> obj) || _stream.eof()) break;
		tree.add(tree.getRoot(), obj);
	}
	Interface<T> iface;
	iface.setColor(GREEN);
	cout << endl << "���������� ������� ���������!" << endl;
	iface.setColor(DARK_WHITE);
	system("pause");
	iface.show_elements(tree);
	_stream.close();
}