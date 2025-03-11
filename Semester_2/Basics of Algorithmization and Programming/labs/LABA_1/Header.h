#include <locale.h>   //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define len 20 

struct pupil           //��������� "������"
{
	char imya[len+1];    //���
	char familia[len+1]; //�������
	int clas;          //����� ������
	char letter;       //����� ������
};

struct pcopy           //����� ��������� "������"
{
	char name[len+1];    //���
	char surname[len+1]; //�������
	int number;        //����� ������
	char bukva;        //����� ������
};

pupil* input_n_and_mem(int &n, pupil *info1);  //������� ����� ���������� �������� � ��������� ������ ��� ������ ��������
pupil* give_memory(int n, pupil *&info1, pcopy *&info2, int* &ms, int *&ms2);   //������� ��������� ������ �� ��������� �� ������ ��������
pupil* input_info(int n, pupil* info);         //������� ����� ���������� � ��������
pupil* input(int i, pupil *info1, int choice); //������� ����� ������� ��� �����
void output_table(int n, pupil *info);         //������� ������ ��������� ���������� � ��������
int exercise_a(int n, pupil *info1, int* &ms); //������� ������ �������������
void realloc_ms1(int *&ms1, int size);         //������� ����������������� ������ ��� ������� ��������
void hat_for_ex1(pupil *info, int size, int *ms);    //������� ������ ���������� ������ �������������
int exercise_b(pupil *info1, int size, int *ms1, int *ms2); //������� ������ ������������� � ������������ �������
void realloc_ms2(int *&ms2, int size);         //������� ����������������� ������ ��� ������� ��������
void hat_for_ex2(pupil *info1, int size, int *ms2);  //������� ������ ������� ����������� ������ ������������� �� ������������ �������
int poisk(int n, pcopy *&info2, pupil *info1); //����� �������������� - �������, ��������� �� ����
void output_poisk(int t, pcopy *info2);        //������� ������ ���������� ������� ������ ��������������
void free_memory(pupil *info1, pcopy *info2, int* ms1, int* ms2); //������� ����������� ������
int offer();                                  //�������, ������� ���������� ���������� ���������