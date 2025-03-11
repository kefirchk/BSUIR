#include "Header.h"               //подключение библиотеки

void Print(tree* root, int lvl) //псевдографический вывод содержимого бинарного дерева
{
	if(root)Print(root->right, lvl + 1); //вызов функции вывода дерева (правая ветка) с новым уровнем вывода
	if(root)for (int i = 0; i < lvl; i++) printf("   ");
	if(root)printf("%d\n", root->info);  //вывод узла
	if(root)Print(root->left, lvl + 1);  //вызов фукнции вывода дерева (левая ветка) с новым уровнем вывода
}