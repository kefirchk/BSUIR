#pragma once
#include "BinaryTree.h"        //����������� ������ "�������� ������"

template<class T>
class Interface
{
private:
	char name[30]; //= "� � � � � � �     � � � �";
public:
	Interface();               //�����������
	~Interface() {}            //����������
	void mainMenu();           //����� �������� ����
	void subMenu(BinaryTree<T>& tree); //����� �������
	void outputName();         //����� ������ ������ "� � � � � � �     � � � �"
	void setColor(int color);  //����� ������� ����� ������
};