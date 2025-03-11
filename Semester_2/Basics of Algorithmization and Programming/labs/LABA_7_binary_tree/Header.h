#include <locale.h>     //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>

struct tree             //��������� ��� ��������� ������
{
	int info;           //�������������� ����
	int meeting;        //����� ������ �������� � �������� ������
	tree *left, *right; //��������� �� ����� � ������ ���������
};

struct stack            //���� ����� ������ ����� ������� �������������� �������� �� ����� 
{
	int flag = 0;       //������� ����������� ���� ���������
	tree *node;         //���������� �� ���� ������  
	stack *next;        //��������� �� ��������� ������� �����
};

void show_menu(tree *);                  //������� ���� ��������� ������ ������������
void show_recursively(tree*);            //������� ��������� ������ ���������� (�����������)
tree* create_menu(tree*&);               //������� ���� �������� ������ ������������
tree* create(tree*&, int);               //������� �������� ������ ������������
tree* create_recursively_menu(tree*&);   //������� ���� �������� ������ ����������
tree* create_recursively(tree*&, int);   //������� �������� ������ ����������
tree* delete_node(tree*&, int element);  //������� �������� ���� � ������
void destroy_tree(tree* &root);          //������� �������� ������
void Print(tree* root, int lvl);        //������� ������������������ ������ ����������� ��������� ������
tree* create_example(tree* &root);       //������� ������������ �������� ��������� ������ �� �������� ������� ��������

int offer();                             //�������, ������� ������ ���������� �� ���������� ���������  
int input_int();                         //������� ����� ������ �����
void instructions();                     //������� ������ ���������� ������ ���������
