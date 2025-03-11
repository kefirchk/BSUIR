#include <locale.h>   //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define n2 15  //����� �����/������� ��������

union currency //�����������, ���������� ������ ��������
{
	long float dollar; //�������
	long float euro;   //����
	long float RUB;    //���������� �����
	long float BYN;    //����������� �����
};
union cash     //�����������, ���������� ���������� ��������� ������ �������� � ������ ��������� �����
{
	int count; //���������� ��������� ������
	int *mv;   //��������� �� ������ ��������� ������
};

struct ripo            //��������� ������� �����
{
	char name[n2];     //���
	char surname[n2];  //�������
	int age;           //�������
	long float BYN;    //����������� �����
};

struct person  //���������� ��������� ���������� � ��������
{
	char name[n2];           //��� ��������
	char surname[n2];        //������� ��������
	int age;                 //������� ��������
	union cash data[2];      //�����������, ���������� ���������� ��������� ������ �������� � ������ ��������� �����
	union currency money[4]; //�����������, ���������� ������ ��������
	struct ripo result[4];   //��������� ������� �����
};

person* input_n_and_mem(int &n, person *man);    //������� ����� ���������� ����� � ��������� ������ ��� ������ ��������
int* currency_choice(person*, int i, int count); //������� ������ ������
int input_int(int choice);                       //������� ����� ���������� ��������� �����
int* mem_for_mv(person *man, int count, int i);  //������� ��������� ������ ��� ������ ������� ��������� �����
person* input_info(int n, person* &man);         //������� ����� ���������� � �����
person* input_str(int i, person*, int choice);   //������� ����� ������� ��� �����
int input_float(long float &value);              //������� ����� ������ ��� ����������� ������
void output_table(int n, person *man);           //������� ������ ��������� ���������� � �����
int *poisk1(int n, person *man);                 //������� ������ �����, � ������� ������ ����� � ������ ����� ����������� ������
int *poisk2(int n, person *man);                 //������� ������ ������ �������� � ������ ������� ��������
long float perevod(person *man, int i);          //������� �������� ������ � ����������� ����� � ������������ ���������� �������� � �������� ����������� ������
void output_result(person*, int*, int*, int n);  //������� ������ ���������� ������ ��������� �����
void free_memory(int n, person *man);            //������� ������������ ������
int offer();                                     //�������, ������� ���������� ���������� ���������