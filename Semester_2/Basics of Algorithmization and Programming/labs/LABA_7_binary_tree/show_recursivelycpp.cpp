#include "Header.h"                //����������� ����������
 
void show_recursively(tree* root)  //����������� ����� ����������� ��������� ������
{
	if (root)
	{
		if (root->left) show_recursively(root->left);     //����� ����� ����� ������
		printf("%d ", root->info);         //������������ �����
		if (root->right) show_recursively(root->right);   //����� ������ ����� ������
	}
}

//void show_recursively(tree* root)  //����������� ����� ����������� ��������� ������
//{
//	if (root)
//	{
//		printf("%d\n", root->info, root->meeting);        //������ �����
//		if (root->left) show_recursively(root->left);     //����� ����� ����� ������
//		if (root->right) show_recursively(root->right);   //����� ������ ����� ������
//	}
//}
//
//void show_recursively(tree* root)  //����������� ����� ����������� ��������� ������
//{
//	if (root)
//	{
//		if (root->left) show_recursively(root->left);     //����� ����� ����� ������
//		if (root->right) show_recursively(root->right);   // ����� ������ ����� ������
//		printf("%d\n", root->info, root->meeting);        //�������� �����
//	}
//}