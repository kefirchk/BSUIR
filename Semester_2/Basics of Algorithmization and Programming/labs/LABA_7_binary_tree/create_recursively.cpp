#include "Header.h"                                  //����������� ����������

tree* create_recursively(tree* &root, int element)   //������� �������� ��������� ������ ����������
{
	if (!root)
	{
		if (!(root = (tree *)malloc(sizeof(tree))))  //��������� ������ ��� ����� ������� ������
		{
			printf("%c[%d;%dm\n������ �� ��������!%c[%dm\n", 27, 1, 31, 27, 0);
			return NULL;
		}
		root->info = element;                        //����������� ��������� ���������� � ���������
		root->meeting = 0;                           //��������� ����� ��������
		root->left = root->right = NULL;
	}
	else 
		if (root->info == element) root->meeting++; //���������� ��� ���� � ������
		else 
			if (element < root->info) root->left = create_recursively(root->left, element); //����� �������� �����
			else root->right = create_recursively(root->right, element);                         //�������� ������
	return root;
}