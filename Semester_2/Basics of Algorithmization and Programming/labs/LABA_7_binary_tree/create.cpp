#include "Header.h"                    //����������� ����������

tree* create(tree* &root, int element) //������� �������� ������ ������������
{
	tree* newElement, *pointer = root; //��������� �� ����� ����������� ������� � ������
	if (!(newElement = (tree*)calloc(1, sizeof(tree))))  //��������� ������ ��� ����� �������
	{
		printf("%c[%d;%dm\n������ �� ��������!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	newElement->info = element;        //����������� ���������� � ���������
	newElement->meeting = 0;           //��������� ����� ������ ��������
	newElement->left = newElement->right = NULL;
	if (!root) return newElement;                   //���� ������ ������
	else
	{
		while (pointer)                             //��������� ��������� �� ������ �� �������� ���� ��� �� ����� �����
		{
			if (pointer->info == newElement->info)  //���� � ����� ����������� ��� � ������ ����
			{ 
				pointer->meeting++;                 //���������� ����� ������
				free(newElement);                   //������������ ������ ��� ����� �������
				break;                              //�������� ����
			}
			else
				if (newElement->info < pointer->info)  //����� ������� ������ �������������� ����
					if (!pointer->left)                //�� ������� ��� �������� ����� 
					{
						pointer->left = newElement;    //������� ���� � ������
						break;
					}
					else pointer = pointer->left;      //������� � ��������� ������� ������ �����
				else 
					if (!pointer->right)               //�� ������� ��� �������� ������ 
					{
						pointer->right = newElement;   //������� ���� � ������
						break;
					}
					else pointer = pointer->right;     //������� � ��������� ������� ������ ������
		}
	}
	return root;
}