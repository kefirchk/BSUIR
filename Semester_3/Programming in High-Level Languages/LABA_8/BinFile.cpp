#pragma once
#include "BinFile.h"

template<class T>
int generate_id(multimap<int, T>& m_map);

template<class T>
bool BinFile<T>::openBinFile(int option)
{
	try
	{
		_stream.open(_fileName, ios::binary | option);
		if (!_stream.good())
			throw FileException(1, "Ошибка файла!", "Проверьте наличие файла!");
		if (!_stream.is_open())
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
		cout << endl << "Запись успешно проведена!" << endl << endl;
		iface.setColor(WHITE);
		_stream.close();
	}
	else
	{
		iface.setColor(RED);
		cout << endl << "Дерево пустое!" << endl << endl;
		iface.setColor(DARK_WHITE);
	}
}

template<class T>
void BinFile<T>::writeInFile(multimap <int, T>& m_map)
{
	Interface<int> iface;
	if (!m_map.empty())
	{
		for (auto it = m_map.begin(); it != m_map.end(); it++)
			_stream << it->second;
		iface.setColor(GREEN);
		cout << endl << "Запись успешно проведена!" << endl << endl;
		iface.setColor(WHITE);
		_stream.close();
	}
	else
	{
		iface.setColor(RED);
		cout << endl << "Multimap пуст!" << endl << endl;
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
	cout << endl << "Считывание успешно проведено!" << endl;
	iface.setColor(DARK_WHITE);
	system("pause");
	iface.show_elements(tree);
	_stream.close();
}

template <class T>
void BinFile<T>::readFromFile(multimap<int, T>& m_map)
{
	T obj;
	while (!_stream.eof())
	{
		if (!(_stream >> obj) || _stream.eof()) break;
		int key = generate_id(m_map);
		m_map.emplace(key, obj);
	}
	Interface<T> iface;
	iface.setColor(GREEN);
	cout << endl << "Считывание успешно проведено!" << endl;
	iface.setColor(DARK_WHITE);
	system("pause");
	iface.show_elements(m_map);
	_stream.close();
}