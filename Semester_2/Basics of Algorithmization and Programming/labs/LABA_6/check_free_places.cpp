#include "Header.h"                                                //����������� ����������

int check_free_places(floor* tailFloor, int* ms)                   //������� �������� ��������� �� ������� ��������� ����
{
	floor* pointerFloor = tailFloor;                               //��������� �� ������
	int freePlaces = 0, i = 1;                                     //����� ���-�� ��������� ���� � ������� �� ������
	while (pointerFloor || i <= ms[0])                             //���� ��� ������� �� ������
	{
		if (pointerFloor && i == pointerFloor->numberOfFloor)      //���� ���� �� ������� � ������������� ��������
		{
			freePlaces += pointerFloor->freePlaces;                //������� ���-�� ��������� ����
			pointerFloor = pointerFloor->next_floor;               //��������� � ���������� �����
		}
		else freePlaces += ms[1] * ms[2];                          //���� �� ��� �� ����� ������, ���������, ��� �� ��������
		i++;                                                       //���������� ��������
	}
	printf("\n����� �������� %d ��������� ����\n", freePlaces);    //����� ������ ���-�� ��������� ����
	if (freePlaces)                                                //���� ���� ��������� �����, �� ����� �� �� ������
	{
		int k = 0;                                                 //�������
		
		printf(" ");
		while (k++ < 26) printf("_");                              //������� ������� ������� �������
		printf("\n|����|���-�� ��������� ����|\n|");               //����� "�����"
		while (--k > 1)                                            //���������� ������� ������� �������
		{
			if (k == 22) printf("|");
			printf("_");
		}
		i = 1;
		pointerFloor = tailFloor;                                  //������������� ��������� �� ������ ���� (�����)
		while (pointerFloor || i <= ms[0])
		{
			freePlaces = 0;                                        //��������� ���-�� ����
			if (pointerFloor && i == pointerFloor->numberOfFloor)  //���� ���� ������������� ��������
			{
				freePlaces += pointerFloor->freePlaces;            //������� ���-�� ����
				pointerFloor = pointerFloor->next_floor;           //������� � ���������� �����
			}
			else freePlaces += ms[1] * ms[2];                      //���� �� ��� ������ �� �����, ���������, ��� �� ��������� ��������
			printf("|\n|%-4d|          %-11d", i, freePlaces);     //����� ����������
			i++;                                                   //���������� ��������
		}
		printf("|\n|");
		while (k++ < 26)                                           //������� ������ ������� �������
		{
			if (k == 6) printf("|");
			printf("_");
		} puts("|");
	}
	return freePlaces;                                             //������� ���-�� ��������� ����
}