#include "Header.h"                    //подключение библиотеки

tree* create(tree* &root, int element) //функция создания дерева нерекурсивно
{
	tree* newElement, *pointer = root; //указатель на новый добавляемый элемент в дерево
	if (!(newElement = (tree*)calloc(1, sizeof(tree))))  //выделение памяти под новый элемент
	{
		printf("%c[%d;%dm\nПамять не выделена!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	newElement->info = element;        //копирование информации в структуру
	newElement->meeting = 0;           //обнуление числа встреч элемента
	newElement->left = newElement->right = NULL;
	if (!root) return newElement;                   //если дерево пустое
	else
	{
		while (pointer)                             //указатель пробегает по дереву до искомого узла или до конца ветви
		{
			if (pointer->info == newElement->info)  //узел с такой информацией уже в дереве есть
			{ 
				pointer->meeting++;                 //увеличение числа встреч
				free(newElement);                   //освобождение памяти под новый элемент
				break;                              //прервать цикл
			}
			else
				if (newElement->info < pointer->info)  //новый элемент меньше анализируемого узла
					if (!pointer->left)                //из вершины нет движения влево 
					{
						pointer->left = newElement;    //вставка узла в дерево
						break;
					}
					else pointer = pointer->left;      //переход к следующей вершине дерева слева
				else 
					if (!pointer->right)               //из вершины нет движения вправо 
					{
						pointer->right = newElement;   //вставка узла в дерево
						break;
					}
					else pointer = pointer->right;     //переход к следующей вершине дерева справа
		}
	}
	return root;
}