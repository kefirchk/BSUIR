//Задание по учебной практике (ознакомительной)
//Тема: "Услуги банка"
/*
Основные услуги по обслуживанию в банкоматах банка:
- просмотр остатка денежных средств на счете
- получение наличных денежных средств
- пополнение счета наличными денежными средствами
- перевод денежных средств со счета на счет
- смена ПИН-кода дебетовой карточки
*/

#include "Header.h"                  //подключение библиотеки

int main()
{
	SetConsoleCP(1251);              //русификация консоли
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	info* head = NULL, *tail = NULL;
	FILE* f = NULL; char c, fileName[len+1];
	printf("%c[%d;%dmВведите название файла:%c[%dm\n", 27, 1, 34, 27, 0);
	strcpy_s(fileName, input_str()); //вызов функции ввода имени файла
	while (1)
	{
		instructions();                                          //вызов функции вывода иструкций по работе программы
		c = _getch();                                            //ввод значения 
		//system("cls");                                           //очистка консоли
		switch (c) {
		case '1': add_person(&head, &tail, fileName, f); break;  //вызов функции добавления человека из файла и очереди
		case '2': del_in_file(f, tail, head, fileName); break;   //вызов функции удаления человека из файла и очереди
		case '3': show_balance(tail, head, f, fileName); break;  //вызов функции просмотра остатка денежных средств на счете
		case '4': show_file(f, fileName, head, tail); break;     //вызов функции просмотра информации файла
		case '5': get_or_push_money(tail, head, fileName, f, 0); break;   //вызов функции получения наличных денежных средств
		case '6': get_or_push_money(tail, head, fileName, f, 1); break;   //вызов функции пополнения счета наличными денежными средствами
		case '7': transfer_money(head, tail, fileName, f); break;//вызов функции перевода денежных средств со счета на счет
		case '8': changePIN(head, tail, fileName, f); break;     //вызов функции смены ПИН - кода дебетовой карточки
		case '9': printf("%c[%d;%dmВведите название файла:%c[%dm\n", 27, 1, 34, 27, 0);
			strcpy_s(fileName, input_str()); break;              //вызов функции смены файл
		case '0': clean(&tail); return 0;                        //вызов функции очистки очереди и выход из программы
		default: printf("%c[%d;%dmОшибка выбора операции! Пожалуйста, повторите снова%c[%dm\n", 27, 1, 31, 27, 0);
			continue;
		}
	}
}