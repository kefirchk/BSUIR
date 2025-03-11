#pragma once
//-------------------------------------------- Узел ----------------------------------------------------- 
template <class T>
class TreeNode
{
	template <class T>
	friend class BinaryTree;
private:
	T data;
	TreeNode* left;    //указатель на левый узел
	TreeNode* right;   //указатель на правый узел
public:
	TreeNode(T data);  //конструктор
	~TreeNode();       //деструктор
	bool isLeaf();     //метод проверки, является ли текующий узел листом
	T& getData();      //метод получения данных об объекте
	TreeNode<T>* getLeft();            //метод получения указателя на левый подузел
	TreeNode<T>* getRight();           //метод получения указателя на правый подузел
	void setLeft(TreeNode<T>* left);   //метод установки значения для указателя на левый подузел 
	void setRight(TreeNode<T>* right); //метод установки значений для указателя на правый подузел
};

//-------------------------------------------- Бинарное дерево ------------------------------------------  
template <class T>
class BinaryTree
{
private:
	TreeNode<T>* root;
public:
	BinaryTree();      //конструктор
	~BinaryTree();     //деструктор

	void add(TreeNode<T>*& node, T& data);          //метод добавления узла в дерево
	void inorder(const TreeNode<T>* node);          //симметричный обход(левый узел->корень->правый узел)
	void preorder(const TreeNode<T>* node);         //прямой обход (корень->левый узел->правый узел)
	void postorder(const TreeNode<T>* node);        //обратный обход (левый узел->правый узел->корень)
	TreeNode<T>* find(TreeNode<T>* node, T& data);  //метод поиска узла
	void findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree);  //метод поиска всех узлов с данными характеристиками
	bool deleteNode(TreeNode<T>*& node, T data);    //метод удаления узла дерева
	T findMinimum(TreeNode<T>* node); //метод поиска минимального(самого крайнего левого узла для вставки туда поддерева), используется в методе удаления узла
	void clean(TreeNode<T>*& node);   //метод очистки дерева
	void setRoot(TreeNode<T>* root);  //метод установки значения для указателя на корень дерева
	TreeNode<T>*& getRoot();          //метод получения указателя на корень дерева
	bool empty();                     //метод проверки дерева на пустоту
};