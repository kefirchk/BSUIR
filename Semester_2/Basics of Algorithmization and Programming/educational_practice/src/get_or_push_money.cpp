#include "Header.h" //подключение библиотеки

int get_push_fun(int choice, int sum, info* &pointer, int k); //функция изменения суммы денег на счете 

void get_or_push_money(info* tail, info* head, char* fileName, FILE* &f, int choice)//функция пополнения/снятия денег 
{
	info* pointer = tail;                   //указатель на искомый элемент
	file_in_str(tail, head, fileName, f);   //вызов функции переписи информации из файла в очередь
	if (pointer = input_PIN(tail))          //вызов функции входа в учетную запись
	{
		int temp = 0, k = currency_choice();//временная переменная; вызов функции выбора валюты
		temp = get_push_fun(choice, sum_choice(), pointer, k); //вызов функции изменения суммы денег на счете
		if (!temp && !choice)               //если недостаточно денежных средств на счете (операция снятия денег со счета)
			printf("%c[%d;%dmНедостаточно денежных средств на балансе!%c[%dm\n", 27, 1, 31, 27, 0);
		else replace_file(tail, fileName, f); //вызов фукнции замены файла
		return;
	}
	else return;
}

int get_push_fun(int choice, int sum, info* &pointer, int k) //функция изменения суммы денег на счете 
{
	if (choice)                                       //пополнение счета
		pointer->cash[k].dollar += sum;               //изменение суммы на счете
	else                                              //снятие денег со счета
	{
		if (pointer->cash[k].dollar -= sum) return 1; //если денег достаточно на счете для снятия требуемой суммы
		else pointer->cash[k].dollar += sum;          //если денег недостаточно
	}
	return 0;
}