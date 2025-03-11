#include "Header.h"                                  //подлкючение библиотеки

tree* create_recursively(tree* &root, int element)   //функция создания бинарного дерева рекурсивно
{
	if (!root)
	{
		if (!(root = (tree *)malloc(sizeof(tree))))  //выделение памяти под новый элемент дерева
		{
			printf("%c[%d;%dm\nПамять не выделена!%c[%dm\n", 27, 1, 31, 27, 0);
			return NULL;
		}
		root->info = element;                        //копирование введенной информации в структуру
		root->meeting = 0;                           //обнуление числа повторов
		root->left = root->right = NULL;
	}
	else 
		if (root->info == element) root->meeting++; //информация уже есть в дереве
		else 
			if (element < root->info) root->left = create_recursively(root->left, element); //иначе движение влево
			else root->right = create_recursively(root->right, element);                         //движение вправо
	return root;
}