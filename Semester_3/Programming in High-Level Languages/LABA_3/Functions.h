#pragma once
#include <iostream>          //����������� ���������� ������ �����-������
#include <iomanip>
using namespace std;         //������������� ������������ ��� std
#include "CountingMachine.h" //����������� ���������� ������ "�������������� ������"
#include "StationaryCM.h"    //����������� ���������� ������ "������������ ��"
#include "PortableCM.h"      //����������� ���������� ������ "����������� ��"
#include "Monoblock.h"       //����������� ���������� ������ "��������"
#include "Notebook.h"        //����������� ���������� ������ "�������"
#include "Smartphone.h"      //����������� ���������� ������ "��������"

void outputHatCM();
void outputHatSCM();
void outputHatPCM();
void outputHatMonoblock();
void outputHatNotebook();
void outputHatSmartphone();