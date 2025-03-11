#pragma once
#include <iostream>          //����������� ���������� ������ �����-������
#include <windows.h>
#include "Exception.h"
using namespace std;         //������������� ������������ ��� std

void setColor(int color);    //����� ������� ����� ������

enum COLORS
{
	DARK_BLUE = 1,
	DARK_GREEN = 2,
	DARK_TURQUOISE = 3,   //���������
	DARK_RED = 4,
	DARK_PINK = 5,
	DARK_YELLOW = 6,
	DARK_WHITE = 7,
	DARK_GRAY = 8,
	BLUE = 9,
	GREEN = 10,
	TURQUOISE = 11,
	RED = 12,
	PINK = 13,
	YELLOW = 14,
	WHITE = 15,
	BLACK_on_blue = 16,
	nothing_on_blue = 17,
	GREEN_on_blue = 18,
	TURQUOISE_on_blue = 19,
	RED_on_blue = 20,
	PINK_on_blue = 21,
	YELLOW_on_blue = 22,
	WHITE_on_blue = 23,
	GRAY_on_blue = 24,
	BLUE_on_blue = 25
};