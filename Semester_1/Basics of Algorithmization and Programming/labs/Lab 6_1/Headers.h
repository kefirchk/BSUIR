#include <windows.h>                                        //����������� ���������
#include <locale.h>
#include <stdio.h>                                            
#include <stdlib.h>
#include <conio.h>

int input_n(int &n, char &choice);                          //������� ����� ������������ ����� n
char* memory_s(int &n, char* &str_s);                       //������� ��������� ������ ��� ������ s
char* memory_a(int &n, char* &str_a);                       //������� ��������� ������ ��� ������ �
void input_stroka_s(char* &str_s, int &n);                  //������� ����� ������ s 
void input_stroka_a(char* &str_a, int &n);                  //������� ����� ������ �
char* memory_del_elements(int n, char* str_del);            //������� ��������� ������ ��� ��������� �������
int choose_str(int number_str);                             //������� ������ ������, ������� ����� ���������������
void algorithm(char* str_s, char* str_a, int &n, char* str_del, int &k);   //������� �������� �� ������ ���� ��������, ������� ���� � ������ ������
void output_main_result(int &k, char* str_s, char* str_a, char* str_del, int number_str);//������� ������ ��������������� ������ s
char add_offer_for_del(char &c);                            //������� ���������� ������� ��������� �������
void output_del_elements(char* str_del, int number_str);    //������� ������ ��������� ��������
void clean_memory(char* &str_s, char* &str_a, char* &str_del); //������� ����������� ������ �� ���������� �� ������
void add_offer(char choice);                                //������� ������, ������� ������ ���������� �� ���������� ��������� ��� ���