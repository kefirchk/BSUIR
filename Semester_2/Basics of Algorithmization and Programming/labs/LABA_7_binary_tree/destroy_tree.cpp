#include "Header.h"                //подключение библиотеки

void destroy_tree(tree* &root)     //рекурсивная функция удаления дерева
{ 
	if (root) {
		destroy_tree(root->left);  //вызов функции удаления дерева (левого узла)
		destroy_tree(root->right); //вызов функции удаления дерева (правого узла)
		free(root);                //освобождение памяти от удаляемого элемента
		root = NULL;
	}
}