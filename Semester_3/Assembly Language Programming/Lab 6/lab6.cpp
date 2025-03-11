#include <iostream>
#include <iomanip>
#include <Windows.h>
#define SIZE 5
using namespace std;
//#pragma inline


int main(void)
{
	setlocale(LC_ALL, "Rus");
	float arr[SIZE];
	float n;

	cout << "������� �������� �������:" << endl;
	for (int i = 0; i < SIZE; i++)
		cin >> arr[i];

	cout << "������ float:" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << setw(10) << arr[i];
	cout << endl;


	_asm 
	{
		finit					//������������� ������������
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx			//edx - ���������� �����

		mov ecx, SIZE			//������ ������� - � ���
		lea ebx, arr			//���������� ������ � ebx
	
	    find_max:
		mov edx, ebx			//������ ������� ������� - � edx
		fld[ebx]				//������ ������� ������� ��������� � ����

		L1 :					//���� �� ��������� �������
			add ebx, 4			//������� �� ��������� ������� �������
			fld[ebx]			//������ ������� �������� � ����
			fcom				// �������� ST(0) � ST(1)
			fstsw ax			// ���������� ������� ��������� � AX
			and ah, 01000101b	// ��������� (����: 08=�0, 10=C2, 14=C3) (��� ���� � ������� � ������)
			fstp[ebx]			//������� ����� �� �����
			jg find_max			//���� ST(1) > ST(0) - ���������� ��� � edx
		loop L1

		mov n, edx				//��������� ���������� ����� ���������� � float n

		fwait					// ����������������
	};

	cout << "���������� �����: " << n << endl;

	__asm
	{
		finit					//������������� ������������
		xor ebx, ebx
		xor ecx, ecx
		mov ecx, SIZE			//������ ������� - � ���
		lea ebx, arr
		fld[n]					//������� n � ����

		L2 :					//���� �� ��������� �������
			fld[ebx]			//��������� ������� ������� � ����
			fdiv				//������ ST(1) = ST(1) / ST(0)
			fstp[ebx]			//������� ����� �� �����
			add ebx, 4			//������� �� ��������� ������� �������
		loop L2

		fwait					// ����������������
	}

	cout << "���������� ������:" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << setw(10) << arr[i];
	cout << endl;
}