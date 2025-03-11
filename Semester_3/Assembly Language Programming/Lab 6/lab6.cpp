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

	cout << "¬ведите элементы массива:" << endl;
	for (int i = 0; i < SIZE; i++)
		cin >> arr[i];

	cout << "ћассив float:" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << setw(10) << arr[i];
	cout << endl;


	_asm 
	{
		finit					//инициализаци€ сопроцессора
		xor eax, eax
		xor ebx, ebx
		xor ecx, ecx
		xor edx, edx			//edx - наибольшее число

		mov ecx, SIZE			//размер массива - в есх
		lea ebx, arr			//записываем массив в ebx
	
	    find_max:
		mov edx, ebx			//первый элемент массива - в edx
		fld[ebx]				//первый элемент массива загрузить в стек

		L1 :					//цикл по элементам массива
			add ebx, 4			//переход на следующий элемент массива
			fld[ebx]			//запись данного элемента в стек
			fcom				// сравнить ST(0) и ST(1)
			fstsw ax			// копировать регистр состо€ни€ в AX
			and ah, 01000101b	// проверить (биты: 08=—0, 10=C2, 14=C3) (это было в примере в методе)
			fstp[ebx]			//считать число из стека
			jg find_max			//если ST(1) > ST(0) - записываем его в edx
		loop L1

		mov n, edx				//найденное наибольшее число записываем в float n

		fwait					// синхронизировать
	};

	cout << "Ќаибольшее число: " << n << endl;

	__asm
	{
		finit					//инициализаци€ сопроцессора
		xor ebx, ebx
		xor ecx, ecx
		mov ecx, SIZE			//размер массива - в есх
		lea ebx, arr
		fld[n]					//заносим n в стек

		L2 :					//цикл по элементам массива
			fld[ebx]			//очередной элемент массива в стек
			fdiv				//делить ST(1) = ST(1) / ST(0)
			fstp[ebx]			//считать число из стека
			add ebx, 4			//переход на следующий элемент массива
		loop L2

		fwait					// синхронизировать
	}

	cout << "»змененный массив:" << endl;
	for (int i = 0; i < SIZE; i++)
		cout << setw(10) << arr[i];
	cout << endl;
}