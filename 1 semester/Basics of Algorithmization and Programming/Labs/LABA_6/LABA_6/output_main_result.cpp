#include "Headers.h"                                                     //����������� ����������

void output_main_result(int &k, char* str_s, char* str_a, char* str_del, int number_str) //������� ������ ��������������� ������
{
	char c;                                                              //���������� ������������� ����������
	if (k > 0)                                                           //���� ������� ���� �� ���� ����������� ������� �����
	{
		printf("\n��������������� ������: ");                 
		if(number_str==1) puts(str_s);                                   //����� ��������������� ������ s-��������
		else puts(str_a);                                                //����� ��������������� ������ �-��������
		add_offer_for_del(c);                                            //����� ������� ����������� ������� ��������� �������
		if (c == 'y') output_del_elements(str_del, number_str);                      //����� ������ ��������� ��������
	}
	else printf("\n��������������� ������ �� ����������� ���������������.");  //���� �� ���� ������� ��������������� ������ �� ������ � �����-���� ��������� ������ ������ 
}