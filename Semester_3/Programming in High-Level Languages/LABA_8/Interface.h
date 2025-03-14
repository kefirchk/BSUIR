#pragma once
#include <map>
#include "BinaryTree.h"        //����������� ������ "�������� ������"
using namespace std;

template<class T>
class Interface
{
private:
	char name[30]; //= "� � � � � � �     � � � �";
public:
	Interface();               //�����������
	~Interface() {}            //����������
	void mainMenu();           //����� �������� ����
	int menu_workContainer();  //���� ������ ���������� ��� ������
	void instructions();       //���� ������ ���������� ��� ������
	void subMenu(BinaryTree<T>& tree); //����� �������
	void subMenu_withMultimap(multimap<int, T>& m_map);
	void outputName();         //����� ������ ������ "� � � � � � �     � � � �"
	void setColor(int color);  //����� ������� ����� ������
	void show_table(BinaryTree<T>& tree); //����� ������� ���������

	void add_element(BinaryTree<T>& tree);      //�������� � ������
	void delete_element(BinaryTree<T>& tree);   //������� �� ������
	void show_elements(BinaryTree<T>& tree);    //�������� ������
	void edit_element(BinaryTree<T>& tree);     //������������� ������� � ������
	void find_elements(BinaryTree<T>& tree);    //����� ������� � ������
	void sort_elements(BinaryTree<T>& tree);    //����������� ������

	void add_element(multimap<int, T>& m_map);   //�������� � multimap
	void delete_element(multimap<int, T>& m_map);//������� �� multimap'a
	void show_elements(multimap<int, T>& m_map); //�������� multimap
	void edit_element(multimap<int, T>& m_map);  //������������� ������� �� multimap'a
	void find_elements(multimap<int, T>& m_map); //����� ������� � multimap'e
	void sort_elements(multimap<int, T>& m_map); //����������� multimap
	void show_table(multimap<int, T>& m_map);    //����� ������� ���������
};

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