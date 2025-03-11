#include "Header.h"

tree* create_example(tree* &root) //  рекурсивное создание бинарного дерева
{
	int ms[18] = { 8, 5, 3, 2, 1, 4, 7, 6, 12, 10, 9, 11, 13, 14, 16, 15, 17, 666 };
	int element; int i = 0;
	do
	{
		element = ms[i++];
		if (element != 666) root = create_recursively(root, element);
		else break;
	} while (1);
	printf("\n%c[%d;%dmДерево создано!%c[%dm\n", 27, 1, 32, 27, 0);
	return root;
}