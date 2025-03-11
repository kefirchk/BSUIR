#include "Header.h"                        //подключение библиотеки

int transfer_fun(int sum, info* &pointer1, info* &pointer2, int k);  //функция изменения сумм на счете отправителя и получателя

void transfer_money(info* head, info* tail, char* fileName, FILE* f) //функция перевода денег со счета на счет
{
	char name2[len], surname2[len];        //строки для имени и фамилии получателя
	file_in_str(tail, head, fileName, f);  //вызов функции переписи информации из файла в очередь
	info* pointer1, *pointer2 = tail;      //указатель на отправителя и получателя соответственно
	printf("\nВведите данные отправителя перевода\n");
	if (pointer1 = input_PIN(tail))        //вызов функции входа в учетную запись
	{
		while (1)
		{
			printf("\nВведите данные получателя перевода");
			printf("%c[%d;%dm\nВведите имя:%c[%dm\n", 27, 1, 33, 27, 0);
			strcpy_s(name2, input_str());  //вызов функции ввода имени получателя
			printf("%c[%d;%dm\nВведите фамилию:%c[%dm\n", 27, 1, 33, 27, 0);
			strcpy_s(surname2, input_str()); //вызов функции ввода фамилии
			while (pointer2)               //цикл по очереди, пока не найден структура получателя
			{
				if (!strcmp(pointer2->name, name2) && !strcmp(pointer2->surname, surname2)) break; //если требуемый элемент нашелся
				pointer2 = pointer2->next; //переход к следующему элементу очереди
			}
			if (pointer2)                  //если требуемый элемент нашелся
			{
				int temp = 0, k = currency_choice(); //временная переменная; вызов функции выбора валюты
				temp = transfer_fun(sum_choice(), pointer1, pointer2, k); //вызов функции изменения сумм на счете отправителя и получателя
				if (!temp)                 //если на счете отправителя недостаточно денежных средств для перевода необходимой суммы
				{
					printf("%c[%d;%dmНедостаточно денежных средств на балансе!%c[%dm\n", 27, 1, 31, 27, 0);
					return;
				}
				else replace_file(tail, fileName, f); //вызов функции замены файла
				return;
			}
			printf("%c[%d;%dm\nНе удалось найти такого человека!\nПовторите ввод%c[%dm\n", 27, 1, 31, 27, 0);
		}
	}
	else return;
}

int transfer_fun(int sum, info* &pointer1, info* &pointer2, int k) //функция изменения сумм на счете отправителя и получателя
{
	if ((pointer1->cash[k].BYN -= sum)>=0) //если на счете отправителя достаточно денежных средств
	{
		pointer2->cash[k].BYN += sum;      //изменение суммы счета получателя
		return 1;
	}
	else pointer1->cash[k].BYN += sum;     //возвращение к начальной сумме денег на счете отправителя
	return 0;
}