#include "Headers.h"                                      //����������� ����������

void recursWord(char* new_str, int begin, int end);       //������� ���������� ����� ���������
void poisk_word(char* new_str, int n);                    //������� ������ ���� � ������

void recurs_slova(char* &new_str)                         //������� ���������� ����� � ������ ���������
{
	int num=0;                                            //������ ������
	while(new_str[num] != '\0')num++;                     //���������� ������� ������
	poisk_word(new_str, num);                             //��������� � ������� ������ ���������� �����
	//puts(new_str);                                      //����� ������
	static int j;                                         //�������
	if ((*(new_str + j)) != '\0')                         //������ �� ������
	{
		j++;
		recurs_stroki(new_str);                           //��������
	}
	printf("%c", new_str[--j]);                           //����� ��������
}


void poisk_word(char* new_str, int num)                   //������� ������ ���� � ������
{
	static int begin, end;                                //������ � ����� �����
	if (num > 0) poisk_word(new_str, num - 1);            //��������� � ������� ������ �����
	if ((new_str[num] == ' ') || (new_str[num] == '\0')) 
	{
		end = num - 1;                                    //��������� ����� �����  
		recursWord(new_str, begin, end);
 		begin = num + 1;                                  //��������� ������ �����
	}
}


void recursWord(char* new_str, int begin, int end)        //������� ���������� ����� ���������
{
	static char temp;                                     //��������� ����������
	if (end> begin) 
	{
		recursWord(new_str, begin + 1, end - 1);          //��������� � ������� ���������� �����
	}
	else return;
	temp = new_str[begin];                               
	new_str[begin] = new_str[end];
	new_str[end] = temp;
}