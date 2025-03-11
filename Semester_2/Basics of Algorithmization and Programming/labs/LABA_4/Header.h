#include <locale.h>    //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <io.h>

#define n2 15          //����� ������ ��� ������ ����� � ������� ��������

union currency         //�����������, ���������� ������ �����
{
	double dollar;     //�������
	double euro;       //����
	double RUB;        //���������� �����
	double BYN;        //����������� �����
};
union cash             //o����������, ���������� ���������� ��������� ������ �������� � ������ ��������� �����
{
	int count;         //���������� ��������� ������
	int mv[4] = { };   //������ ��������� ������
};

struct ripo            //��������� ������� �����
{
	char name[n2];     //���
	char surname[n2];  //�������
	int age;           //�������
	double BYN;        //����������� �����
};

struct person          //���������� ������� ���������
{
	char name[n2];           //���
	char surname[n2];        //�������
	int age;                 //������� ��������
	union cash data[2];      //o����������, ���������� ���������� ��������� ������ �������� � ������ ��������� �����
	union currency money[4]; //�����������, ���������� ������ �����
	//struct ripo result[4];   //��������� ����������� ������ ������� �����
};

void text_file_in_str(int size, FILE *f, person *&man); //������� �������� ���������� �� ���������� ����� � ���������
void binary_file_in_str(int size, FILE *f, person *&man); //������� �������� ���������� �� ��������� ����� � ���������
void struct_in_binary_file(char* name, FILE *f, person* man, char choice, int n); //������� ������ ��������� � �������� ����
void struct_in_text_file(char* name, FILE *f, person* man, char choice, int n); //������� ������ ��������� � ��������� ����
int checkFileOpen(errno_t ff);                   //������� �������� ����� �� ��������
int menu(person* &, FILE *&f, char*);            //������� ������ ������ ������ ���������
void show_file(char, FILE *f, char*, person*);   //������� ������ ����������� � �����
int file_in_str(person*&, char*, FILE *f, char); //������� �������� ���������� �� ����� � ������ �����
int del_person(FILE*&, person*&, char*, char);   //������� �������� ���������� � �������� �� �����
person* memory_struct(person* &man, int n);      //������� ��������� ������ ��� ������ ��������
int input_int(int);                              //������� ����� ���������� �����
int* currency_choice(person*&, int i, int);      //������� ������ ������
person* input_info(int n, person* &man);         //������� ����� ���������� � �����
char* input_str(int i, person*&, int choice);    //������� ����� ������� ��� �����
int input_float(double &value);                  //������� ����� ������ ��� ����������� ������
void output_table(int n, person *man);           //������� ������ ��������� ���������� � �����
int *poisk1(int n, person *&man, ripo *&);       //������� ������ �����, � ������� ������ ����� � ������ ����� ����������� ������
int *poisk2(int n, person *&man, ripo *&);       //������� ������ ������ �������� � ������ ������� ��������
double perevod(person *man, int i);              //������� �������� ������ � ����������� ����� � ������������ ���������� �������� � �������� ����������� ������
void output_result(person*, int*, int*, int n, ripo*);  //������� ������ ���������� ������ ��������� �����
int offer();                                     //������� ����������� ���������� ��� ��������� ���������