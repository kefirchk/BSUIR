#pragma once
#include <iostream>          //����������� ���������� ������ �����-������
#include <iomanip>
#include <windows.h>
#include <limits>
using namespace std;         //������������� ������������ ��� std

#include "CountingMachine.h" //����������� ������ "�������������� ������"
#include "StationaryCM.h"    //����������� ������ "������������ ��"
#include "PortableCM.h"      //����������� ������ "����������� ��"
#include "Monoblock.h"       //����������� ������ "��������"
#include "Notebook.h"        //����������� ������ "�������"
#include "Smartphone.h"      //����������� ������ "��������"

#include "BinaryTree.cpp"    //����������� ������ "�������� ������" � "���� ������" 
#include "BinFile.cpp"
#include "TxtFile.cpp"

int get_int(int min, int max);
char get_char(char first, char second);
char* get_str(istream& in);
void skip_spaces(ifstream& fin);

template<class T>
const char* choosing_file(T& obj)
{
	string className = typeid(T).name(), filename = PATH;
	if (className == "class Monoblock")
		filename += "Monoblocks";
	else if (className == "class Smartphone")
		filename += "Smartphones";
	else if (className == "class Notebook")
		filename += "Notebooks";
	char* str = new char[filename.size() + 1];
	strcpy_s(str, filename.size() + 1, filename.c_str());
	return str;
}