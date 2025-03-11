#include "Header.h"                //����������� ����������

void destroy_tree(tree* &root)     //����������� ������� �������� ������
{ 
	if (root) {
		destroy_tree(root->left);  //����� ������� �������� ������ (������ ����)
		destroy_tree(root->right); //����� ������� �������� ������ (������� ����)
		free(root);                //������������ ������ �� ���������� ��������
		root = NULL;
	}
}