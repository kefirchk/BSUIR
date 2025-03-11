#include "Header.h"                           //подключение библиотеки

tree* delete_node(tree* &root, int element)   //функция удаления узла бинарного дерева
{
	tree *run_ptr, *prev_ptr, *deleted_node;  //бегущий указатель по дереву, указатель на предыдущий узел, указатель на удаляемый элемент 
	if (!root)                                //если дерево не создано
	{
		printf("%c[%d;%dm\nДерево пустое!%c[%dm\n", 27, 1, 31, 27, 0);
		return NULL;
	}
	int flag = 0;
	//printf("Введите удаляемую информацию: ");
	//int element = input_int();                //вызов функции ввода информации
	prev_ptr = run_ptr = root;                //устанавливаются начальные адреса указателей
	do                                        //цикл поиска удаляемого элемента из дерева
	{
		if (run_ptr && element == run_ptr->info)
		{
			flag = 1;
			break;  //удаляемый узел найден
		}
		if (element < run_ptr->info)          //удаляемый элемент < анализируемого узла
		{
			if (run_ptr->left)                //движение налево из узла run_ptr существует
			{
				prev_ptr = run_ptr;           //запоминаем текущий узел
				run_ptr = run_ptr->left;      //считываем новый левый узел дерева
			}
			else break; 
		}
		if (element > run_ptr->info)          //удаляемый элемент > анализирумего узла
		{
			if (run_ptr->right)               //есть движение направо
			{
				prev_ptr = run_ptr;           //запоминаем текущий узел
				run_ptr = run_ptr->right;     //считываем новый правый узел дерева
			}
			else break;
		}
	} while (run_ptr);

	if (flag == 0)                            //элемент отсутствует в дереве
	{
		printf("%c[%d;%dmТребуемый элемент не найден!%c[%dm\n\n", 27, 1, 31, 27, 0);
		return root;
	}
	else                                      //элемент найден
	{
		deleted_node = run_ptr;               //запоминаем удаляемый узел дерева
		if (run_ptr == prev_ptr)              //удаляемый узел - это корень дерева
		{
			if (run_ptr->right)               //есть движение направо
			{
				deleted_node = run_ptr->right;//перемещаемя на правую ветку дерева
				while (deleted_node->left)    //цикл по спуску вниз по дереву, пока не найдем позицию, куда нужно вставить левую ветку
					deleted_node = deleted_node->left; //переход к новому элементу слева
				root = run_ptr->right;        //изменяем корень дерева
				deleted_node->left = run_ptr->left;    //вставляем левую ветку под правой
			}
			else root = run_ptr->left;        //иначе просто изменяем указатель на корень дерева
		}
		else if (run_ptr < prev_ptr)          //удаляемая вершина < предыдущей
		{
			if (run_ptr->right)               //у вершины run_ptr есть ветвь вправо
			{
				deleted_node = run_ptr->right;// переход на вершину вправо от удаляемой и далее
				while (deleted_node->left)    //цикл по поиску позицию вставки ветки элементов после удаляемого узла
					deleted_node = deleted_node->left; //переход к новому элементу слева
				prev_ptr->left = run_ptr->right;       //обход удаляемой вершины run_ptr
				deleted_node->left = run_ptr->left;    //вставка ветки, идущей после удаляемого элемента
			}
			else prev_ptr->left = run_ptr->left;       //просто обход удаляемой вершины
		}
		else                                  //удаляемая вершина > предыдущей
		{
			if (run_ptr->left)                //удаляемая вершина имеет ветвь вправо
			{
				deleted_node = run_ptr->left; //переход на вершину влево от удаляемой и далее
				while (deleted_node->right)   //цикл по поиску позицию вставки ветки элементов после удаляемого узла
					deleted_node = deleted_node->right; //переход к следующему элементу
				prev_ptr->right = run_ptr->left;        //обход удаляемой вершины run_ptr
				deleted_node->right = run_ptr->right;   //вставка ветки, идущей после удаляемого узла
			}
			else prev_ptr->right = run_ptr->right;      //просто обход удаляемой вершины, не имеющей левой связи
		}
		free(run_ptr);                        //освобождение памяти от удаляемого узла
	}
	printf("\n%c[%d;%dmЭлемент удален!%c[%dm\n", 27, 1, 32, 27, 0);
}