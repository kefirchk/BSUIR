#include "Header.h"                           //����������� ����������

tree* delete_node(tree* &root, int element)   //������� �������� ���� ��������� ������
{
	tree *run_ptr, *prev_ptr, *deleted_node;  //������� ��������� �� ������, ��������� �� ���������� ����, ��������� �� ��������� ������� 
	if (!root)                                //���� ������ �� �������
	{
		printf("%c[%d;%dm\n������ ������!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	int flag = 0;
	//printf("������� ��������� ����������: ");
	//int element = input_int();                //����� ������� ����� ����������
	prev_ptr = run_ptr = root;                //��������������� ��������� ������ ����������
	do                                        //���� ������ ���������� �������� �� ������
	{
		if (run_ptr && element == run_ptr->info)
		{
			flag = 1;
			break;  //��������� ���� ������
		}
		if (element < run_ptr->info)          //��������� ������� < �������������� ����
		{
			if (run_ptr->left)                //�������� ������ �� ���� run_ptr ����������
			{
				prev_ptr = run_ptr;           //���������� ������� ����
				run_ptr = run_ptr->left;      //��������� ����� ����� ���� ������
			}
			else break; 
		}
		if (element > run_ptr->info)          //��������� ������� > ������������� ����
		{
			if (run_ptr->right)               //���� �������� �������
			{
				prev_ptr = run_ptr;           //���������� ������� ����
				run_ptr = run_ptr->right;     //��������� ����� ������ ���� ������
			}
			else break;
		}
	} while (run_ptr);

	if (flag == 0)                            //������� ����������� � ������
	{
		printf("%c[%d;%dm��������� ������� �� ������!%c[%dm\n\n", 27, 1, 31, 27, 0);
		return root;
	}
	else                                      //������� ������
	{
		deleted_node = run_ptr;               //���������� ��������� ���� ������
		if (run_ptr == prev_ptr)              //��������� ���� - ��� ������ ������
		{
			if (run_ptr->right)               //���� �������� �������
			{
				deleted_node = run_ptr->right;//����������� �� ������ ����� ������
				while (deleted_node->left)    //���� �� ������ ���� �� ������, ���� �� ������ �������, ���� ����� �������� ����� �����
					deleted_node = deleted_node->left; //������� � ������ �������� �����
				root = run_ptr->right;        //�������� ������ ������
				deleted_node->left = run_ptr->left;    //��������� ����� ����� ��� ������
			}
			else root = run_ptr->left;        //����� ������ �������� ��������� �� ������ ������
		}
		else if (run_ptr < prev_ptr)          //��������� ������� < ����������
		{
			if (run_ptr->right)               //� ������� run_ptr ���� ����� ������
			{
				deleted_node = run_ptr->right;// ������� �� ������� ������ �� ��������� � �����
				while (deleted_node->left)    //���� �� ������ ������� ������� ����� ��������� ����� ���������� ����
					deleted_node = deleted_node->left; //������� � ������ �������� �����
				prev_ptr->left = run_ptr->right;       //����� ��������� ������� run_ptr
				deleted_node->left = run_ptr->left;    //������� �����, ������ ����� ���������� ��������
			}
			else prev_ptr->left = run_ptr->left;       //������ ����� ��������� �������
		}
		else                                  //��������� ������� > ����������
		{
			if (run_ptr->left)                //��������� ������� ����� ����� ������
			{
				deleted_node = run_ptr->left; //������� �� ������� ����� �� ��������� � �����
				while (deleted_node->right)   //���� �� ������ ������� ������� ����� ��������� ����� ���������� ����
					deleted_node = deleted_node->right; //������� � ���������� ��������
				prev_ptr->right = run_ptr->left;        //����� ��������� ������� run_ptr
				deleted_node->right = run_ptr->right;   //������� �����, ������ ����� ���������� ����
			}
			else prev_ptr->right = run_ptr->right;      //������ ����� ��������� �������, �� ������� ����� �����
		}
		free(run_ptr);                        //������������ ������ �� ���������� ����
	}
	printf("\n%c[%d;%dm������� ������!%c[%dm\n", 27, 1, 32, 27, 0);
}