#include <windows.h>                                           //����������� ���������
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>
#include <conio.h>

char add_offer(char choice);
int lenght_strok(int n, char** str);      //������� ���������� ������ ����� ��� ������ new_str  
void revers_new(char *&new_str, int begin, int end);     //������� ������� ���� (������������ ����)
char recurs_stroki(char* &new_str);