#include "Header.h"               //����������� ����������

void Print(tree* root, int lvl) //����������������� ����� ����������� ��������� ������
{
	if(root)Print(root->right, lvl + 1); //����� ������� ������ ������ (������ �����) � ����� ������� ������
	if(root)for (int i = 0; i < lvl; i++) printf("   ");
	if(root)printf("%d\n", root->info);  //����� ����
	if(root)Print(root->left, lvl + 1);  //����� ������� ������ ������ (����� �����) � ����� ������� ������
}