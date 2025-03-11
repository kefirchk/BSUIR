#include <locale.h>         //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#define len 15  //����� �������� ����

union currency  //����������� "������"
{
	int dollar; //�������
	int euro;   //����
	int RUB;    //���������� �����
	int BYN;    //����������� �����
};

struct info     //���������, �������� ���������� � ��������
{
	char name[len + 1];     //���
	char surname[len + 1];  //�������
	int PIN;                //PIN-��� ������������
	currency cash[4];       //���������, �������� ������ ��������
	info* next;             //��������� �� ��������� ���������
};

void instructions();        //������� ������� ���������� �� ������ ���������
int input_int();            //������� ����� ������ �����
char* input_str();          //������� ����� ������
info* input_PIN(info* tail);//������� ����� PIN-����
int currency_choice();      //������� ������ ������
int sum_choice();           //������� ������ �����
int offer();                //�������, ������� ������ ���������� ��� ��������� ���������� ���������  
void clean(info** tail);    //������� ������� �������

void get_or_push_money(info* tail, info* head, char*, FILE* &f, int); //������� ������ �� ����� �������� �������
void show_balance(info* tail, info* head, FILE* f, char* fileName);   //������� ��������� �������
void add_person(info** tail, info** head, char* fileName, FILE* f);   //������� ���������� �������� � �������
void del_person(info** tail, info** head, info* &element);            //������� �������� �������� �� �������
int del_in_file(FILE *&f, info *&tail, info* &head, char* fileName);  //������� �������� �������� �� �����
void transfer_money(info* head, info* tail, char*, FILE* f);          //������� �������� �������� ������� � ������ ����� �� ������
void changePIN(info* head, info* tail, char* fileName, FILE* f);      //������� ����� PIN-����

void struct_in_file(char* name, FILE *&f, info* tail);                //������� ������ ��������� � ��������� ����
int file_in_str(info* &tail, info* &head, char* name, FILE *f);       //������� �������� ���������� �� ����� � ������
void show_file(FILE *f, char* name, info* head, info* tail);          //������� ��������� �����
void replace_file(info*&tail, char* fileName, FILE* &f);              //������� ������ �����