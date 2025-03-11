#include "Header.h"                //подключение библиотеки
 
void show_recursively(tree* root)  //рекурсивный вывод содержимого бинарного дерева
{
	if (root)
	{
		if (root->left) show_recursively(root->left);     //вывод левой ветви дерева
		printf("%d ", root->info);         //симметричный обход
		if (root->right) show_recursively(root->right);   //вывод правой ветви дерева
	}
}

//void show_recursively(tree* root)  //рекурсивный вывод содержимого бинарного дерева
//{
//	if (root)
//	{
//		printf("%d\n", root->info, root->meeting);        //прямой обход
//		if (root->left) show_recursively(root->left);     //вывод левой ветви дерева
//		if (root->right) show_recursively(root->right);   //вывод правой ветви дерева
//	}
//}
//
//void show_recursively(tree* root)  //рекурсивный вывод содержимого бинарного дерева
//{
//	if (root)
//	{
//		if (root->left) show_recursively(root->left);     //вывод левой ветви дерева
//		if (root->right) show_recursively(root->right);   // вывод правой ветви дерева
//		printf("%d\n", root->info, root->meeting);        //обратный обход
//	}
//}