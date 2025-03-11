#include <locale.h>   //����������� ���������
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <io.h>

#define n1 2    //���������� ����� � ������
#define n2 20   //����� �����

struct word     //���������, ������� �������� ���������� � �����
{
	char word[n2 + 1];   //�����
	int repeat;          //����� ��������� � ������
};

int menu(char** &, FILE *&f, char*);             //������� ������ ������ ������ ���������
void show_file(FILE *f, char* name);             //������� ������ ����������� � �����
int file_in_str(char*, char **&str, FILE *f);    //������� �������� ���������� �� ����� � ������ �����
int input_n(int k);                              //������� ����� ���������� ����, ������� ����� ����������
char** input_text(char*, char **, FILE *&, int); //������� ����� ������
char* input_word(int);                           //������� ����� �����
char** memory_for_text(char **&str, int);        //������� ��������� ������ ��� �����
char **realloc_text(char **&str, int size);      //������� ����������������� ������ ��� �����
int poisk_words(word*&, char **, int size);      //������� ������ ���� � ������
int special_order(int k, word* ab);              //�������, ������� ���������� ������� �� ����� �������� �������� ����� 
void special_output(int k, word*, char* sl);     //������� ������ ��������� �����
word* memory_struct(word *ab, int k);            //������� ��������� ������ ��� ������ ��������
word* repeats(word* ab, int k);                  //������� �������� ����� ��������� ������� �����
word* delete_same_words(word* ab, int &k);       //������� �������� ���������� ���� �� ������� ��������
word* sort_ms(word* ab, int k);                  //������� ���������� ���� �� �� ����� ��������� � ������� ��������
void output_result(int n, word* ab, int);        //������� ������ ���������� �� �����
void free_memory(int, char** str, word* ab);     //������� ������������ ������ �� ���������� �� ��������� �� ������, �� ��������� � �� ������
int offer();                                     //�������, ������� ���������� ���������� ���������
int length(FILE *f, char* name);                 //������� �������� ����� �����