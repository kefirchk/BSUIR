#pragma once
#include "Libs.h"

// ====================================================================
// ����� Webcam
// --------------------------------------------------------------------
class Webcam
{
public:
	string getData(DWORD property);   // �������� ������ � ���-������
	string getDriverName();           // �������� ��� �������� ���-������
	string getDriverVersion();        // �������� ������ �������� ���-������
};

