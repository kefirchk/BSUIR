#include <locale.h>  //����������� ���������
#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#define len 80

struct stack       //��������� "����"
{
	char bracket;  //���� ��� �������� ������
	int index;     //���� ��� �������� ������� ������
	stack* next;   //��������� �� ��������� ������� �����
};

//����� �������
int offer();           //������� ������, ������� ������ ���������� �� ���������� ���������  
void output_str(char *str, int i);     //������� ������ �������� ������
char* input_str(char); //������� ����� ������
char choose_option();  //������� ������ ������ ������ ���������
void test1(char c, char *&str); //������� �������� ��������� ��� ������������� �����
void test2(char c, char *&str); //������� �������� ��������� � �������������� �����
char* del_symbol(int index, char* str);//������� �������� ������� � ������
void save(char* &strcopy, char* &str); //������� ���������� ��������� � ������

//������� � �������������� �����
int check_with_stack(stack *&head, char *str, int);  //������� �������� ����������� ������ � �������������� �����
void push(stack **h, char c, int i);   //������� ���������� � ���� ��������
char pop(stack **s);   //������� �������� ���������� �������� ����� (� ������� �����)
void show(stack *s);   //������� ��������� ��������� �����
void stack_fix(stack *&head, char* &str, int index); //������� ���������� ������ ����������� ������ �� ��������
char* correct_option_1(stack* head, char* str, int index); //������� ����������� ��������� ������ �� ������(������ 1)
void correct_option_2(stack *&head, char* &str, int index); //������� ����������� ��������� ������ �� ������(������ 2)
int check2(stack* head, int index, char* str, int c); //������� �������� � ����������� ������
char* del(stack *&head, char *str, int index); //������� ������� ������������ ������
char* add(stack *&head, char* str, int index); //������� ���������� ��� ��������� ������
void error(stack *head, int c); //������� ������� ����� �� ������ � ��������� �����

//������� ��� ������������� �����
void string_fix(char* stack, char *str, int index);   //������� �������� ������������ ������
int check_without_stack(char *str, int c);    //������� �������� ����������� ������ ��� ������������� �����
void correct_without_stack(char* stack, char *str, int index); //������� ����������� ��������� ������ ��� �����
int check1(char* stack, int index, char* str, int c); //������� �������� � ����������� ������