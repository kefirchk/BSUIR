#include "Header.h"  //����������� ����������

word* repeats(word* ab, int k) //������� �������� ����� ��������� ������� �����
{
	for (int i = 0; i < k; i++)
		for (int j = i; j < k; j++)
			if (!(strcmp(ab[i].word, ab[j].word)) && ab[i].repeat > -1) //�������� �� ���������� ���� � �� ��, ���� �� ����� ��� �����������
			{
				ab[i].repeat += 1; //���������� ����������� ����� ��������� �����
				if(i!=j) ab[j].repeat = -1; //������� �� �����, ��� ��� ������������� �� �����
			}
	return ab;       //������� ��������� �� ������ �����
}