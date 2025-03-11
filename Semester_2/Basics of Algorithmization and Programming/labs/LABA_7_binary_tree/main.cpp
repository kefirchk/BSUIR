//Лабораторная работа №7. Бинарные деревья.

#include "Header.h"            //подключение библиотеки

int main()
{
	SetConsoleCP(1251);        //русификация консоли
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Rus");
	tree* root = NULL; char c; //указатель на корень дерева и временная переменная
	int element;               //добавляемый элемент в дерево
	do
	{
		while (1)
		{
			instructions();    //вызов функции вывода инструкций работы программы
			switch (c = _getch()) {
			case '0': create_example(root); break;           //вызов функции создания дерева по готовому примеру
			case '1': create_menu(root); break;              //вызов функции меню создания дерева
			case '2': create_recursively_menu(root); break;  //вызов функции меню создания дерева рекурсивно
			case '3': show_menu(root); break;                //вызов функции меню просмотра дерева
			case '4': printf("\n");                          //переход на нoвую строку
				if (root) show_recursively(root);            //вызов функции просмотра дерева рекурсивно(симметрично)
			    else printf("%c[%d;%dm\nДерево пустое!%c[%dm\n", 27, 1, 31, 27, 0);
				printf("\n\n"); break;                       //переход на новую строку
			case '5': if (root) Print(root, 0); 
					  else puts("\nДерево пустоe!\n"); break; //вызов функции псевдографического вывода информации дерева
 			case '6': 
				if (root)
				{
					printf("Введите удаляемую информацию: ");
					element = input_int();                   //вызов функции ввода информации
				}
				delete_node(root, element); break;           //вызов функции удаления узла дерева
			case '7': destroy_tree(root);                    //вызов функции удаления дерева
				printf("\n%c[%d;%dmДерево удалено!%c[%dm\n", 27, 1, 32, 27, 0);
				break; 
			case '8': destroy_tree(root); return 0;          //выход из программы
			default: printf("%c[%d;%dmОшибка выбора режима работы! Пожалуйста, повторите снова%c[%dm\n", 27, 1, 31, 27, 0);
				continue;
			} break;
		}
	} while (1);
}