#include <windows.h>                                   //����������� ���������
#include <stdlib.h>
#include <stdio.h> 
#include <locale.h>

void del_dynamic(float** matrix, int* array);
void output(int* result);
int* input_size(char choice, int* array);              //������� ����� ������� �������
float** memory_for_matrix(int* array, float** matrix); //������� ��������� ������ ��� ������
float** input_matrix(int* array, float **matrix);      //������� ����� ��������� �������
float* algo_with_output(int* array, float **matrix, float* result);     //������� ��������� ��������� ��� ������� ������ � ������� ���������� �� �����
void additional_offer(char choice);                    //������� ������, ������� ������ ���������� �� ���������� ���������         