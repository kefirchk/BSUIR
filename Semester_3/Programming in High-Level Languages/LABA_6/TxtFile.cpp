#pragma once
#include "TxtFile.h"
void skip_spaces(ifstream&);

template<class T>
bool TxtFile<T>::openForWrite(int option)
{
	try
	{
		_fout.open(_fileName, option);
		if (!_fout.good())
			throw FileException(1, "Ошибка файла!", "Проверьте наличие файла!");
		if (!_fout.is_open())
			throw FileException(2, "Ошибка открытия файла!", "Проверьте целостность файла");
		return true;
	}
	catch (FileException& file)
	{
		file.what();
		return false;
	}
}

template<class T>
bool TxtFile<T>::openForRead()
{
	try
	{
		_fin.open(_fileName, ios::in);
		if (!_fin.good())
			throw FileException(1, "Ошибка файла!", "Проверьте наличие файла!");
		if (!_fin.is_open())
			throw FileException(2, "Ошибка открытия файла!", "Проверьте целостность файла");
		return true;
	}
	catch (FileException& file)
	{
		file.what();
		return false;
	}
}

template<class T>
void TxtFile<T>::writeInFile(BinaryTree<T>& tree)
{
	Interface<int> iface;
	if (!tree.empty())
	{
		vector <T> v;
		T obj;
		tree.treeToArray(tree.getRoot(), v);
		for (int i = 0; i < v.size(); i++)
			_fout << v[i];
		iface.setColor(GREEN);
		cout << endl << "Запись успешно проведена!" << endl << endl;
		iface.setColor(WHITE);
		_fout.close();
	}
	else
	{
		iface.setColor(RED);
		cout << endl << "Дерево пустое!" << endl << endl;
		iface.setColor(DARK_WHITE);
	}
}


template <class T>
void TxtFile<T>::readFromFile(BinaryTree<T>& tree)
{
	T obj;
	while (!(_fin.eof()))
	{
		if (!(_fin >> obj) || _fin.eof()) break;
		tree.add(tree.getRoot(), obj);
		skip_spaces(_fin);
	}
	Interface<T> iface;
	iface.setColor(GREEN);
	cout << endl << "Считывание успешно проведено!" << endl;
	iface.setColor(DARK_WHITE);
	system("pause");
	iface.show_elements(tree);
	_fin.close();
}