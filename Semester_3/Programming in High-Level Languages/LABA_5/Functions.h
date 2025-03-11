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

int get_int(int min, int max);
char get_char(char first, char second);
char* get_str(istream& in);