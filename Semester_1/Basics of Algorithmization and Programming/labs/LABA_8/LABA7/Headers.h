#include <windows.h>                                           //����������� ���������
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>
#include <conio.h>
#include <stdarg.h>

int input_n(int, ...);                                         //������� ����� ���������� �����
int input_size(int &size, char &choice);                       //������� ����� ������� �����
char** memory_for_str(int n, int size, char** str);            //������� ��������� ������ ��� �����
char* memory_for_new_str(int num, char* &new_str);             //������� ��������� ������ ��� ������ ����
void str_equals_new_str(int n, char* &new_str, char** &str);   //������� ���������� ������ new_str
char** input_text(int n, int size, char **&str);               //������� ����� ������
void output_text(char** str, int &n);                          //������� ������ ���������� ������
void search_words(char** &str, int n, int size);               //������� ������ ���� � ������
void output_highlighted_words(int n, char** new_str);          //������� ������ ��������� ����
char choose_option_sort(int, ...);                             //������� ������ �������� ���������� (� ������� �������� ��� ������������)
void sort_by_row(char** str, int n, char &number);             //������� ���������� ���� �� �������
//void revers(char **&str, int begin, int end, int &i);          //������� ������������ ���� ��� ���� ����� ������(������)
void revers_new(char *&new_str, int begin, int end);           //������� ������������ ���� ��� ����� ������� ������ (������)
void realloc_str(int n, char** &str, int &size);               //������� ����������������� ������
char choice_to_sort_text(char &choice);                        //������� ������ ��������� ���������� ����(�� ������� ��� ���������� �� �� ������������� � ������)
char* sort_all_text(char* &new_str, char &number);             //������� ���������� ���� ���������� �� �� ������������� � ������
int lenght_strok(int &n, char** &str);                         //������� ���������� ������� ������� ��� ������ new_str
void output_one_str_of_words(char* new_str);                   //������� ������ ������, ���������� ��� ��������� ����� � ������
void output_complete_text(char** str, int n);                  //������� ������ ��������������� ���� �� �������, � ������� ������ ���� �������
void output_complete_text_2(char* &new_str, int num);          //������� ������ ������ ��������������� ���� �� �� �����, ������� ������� ����� � ������
void clean_memory_param(char** &str, int &n, char* &new_str, char &choice);
//void clean_memory(char** &str, int &n, char* &new_str, char &choice); //������� ������������ ������ �� ���������� �� ��������� � �� ���������� �� ������
void recurs_slova(char* &new_str);                             //������� ���������� ���� � ������ ���������   
void recurs_stroki(char* &new_str);                            //������� ���������� ������ ���������
int add_offer(char choice);                                    //������� ������, ������� ���������� ���������� ���������� ��������� ��� ���