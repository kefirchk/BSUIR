#include "Headers.h"                                               //����������� ����������

char* sort_all_text(char* &new_str, char &number)                  //������� ���������� ���� ���������� �� �� ������������� � ������ � ������� �����������
{
	int begin1 = 0, end1 = 0, lenght1 = 0, begin2 = 0, end2 = 0, lenght2 = 0, flag = 0;//���������� ����������, 
	//��� lenght1, lenght1 - ����� ����, begin1, begin2 - ��������� ������� ����, end1, end2 - �������� ������� ����
	for (int j = 0; new_str[j] != '\0';)                           //���� �� j ��� ������� �� �������� ������                                                  
	{
		while ((*(new_str+j)) == ' ' || ((*(new_str + j)) >= '0' && (*(new_str + j)) <= '9')) j++; //����� ������ �����                            
		begin1 = j;                                                //������ ���������� ������� �����
		while ((*(new_str + j)) != ' ' && (*(new_str + j)) != '\0' && (((*(new_str + j)) > 64 && (*(new_str + j)) < 91) || ((*(new_str + j)) > 96 && (*(new_str + j)) < 123))) j++; //����� ����� �����
		end1 = j;                                                  //����� ���������� ������� �����
		int jj = j;
		lenght1 = end1 - begin1;                                   //����� ������� �����
		for (; (*(new_str + jj)) != '\0';)                         //���� ��� ������ ��������� ����, ��������� �� � ������ � �� ������������ ��� ���������� ��������� �������
		{
			while ((*(new_str + jj)) == ' ') jj++;                 //������� ��������� ��������
			begin2 = jj;                                           //������ ���������� ������� �����
			while ((*(new_str + jj)) != ' ' && (*(new_str + jj)) != '\0') jj++; //������ �� �����
			end2 = jj;                                             //����� ���������� ������� �����
			lenght2 = end2 - begin2;                               //����� ������� �����
			if ((number == '1' && lenght2 < lenght1) || (number == '2' && lenght2 > lenght1))     //���������� �� ����������� ��� ��������
			{
				revers_new(new_str, begin1, end2);                 //������ �� ������ ������� ����� �� ����� �������
				int k1 = begin1 + lenght2;
				revers_new(new_str, begin1, k1);                   //������ ������� (��� �������) �����
				int k2 = end2 - lenght1;
				revers_new(new_str, k2, end2);                     //������ ������� (��� �������) �����
				int k3 = begin1 + lenght2;
				revers_new(new_str, k3, k2);                       //������ ��������� ����� ������ ����� ����� �������
				begin1 = end2 - lenght1;                           //����� ������ ������� �����
				end1 = end2;                                       //����� ����� ������� �����
				flag++;
			}
		}
		if (flag > 0) j = 0;                                       //���� ���� �����-�� ������������ � ������ ������, �� ����� ���������� ��������� ������ ����� � �������
		else while ((*(new_str + j)) != ' ' && (*(new_str + j)) != '\0') j++;  //���� ������������ �� ����, �� ��������� � ������� �����
		flag = 0;
	}
	return new_str;                                                //����������� �������� new_str
}