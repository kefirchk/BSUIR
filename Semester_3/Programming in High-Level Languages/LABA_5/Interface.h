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
	void show_table(BinaryTree<T>& tree); //����� ������� ���������

	void add_element(BinaryTree<T>& tree);
	void delete_element(BinaryTree<T>& tree);
	void show_elements(BinaryTree<T>& tree);
	void edit_element(BinaryTree<T>& tree);
	void find_elements(BinaryTree<T>& tree);
};