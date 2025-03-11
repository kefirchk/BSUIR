#include "BinaryTree.h"
#include <iostream>
using namespace std;

//----------------------------------------------- Методы для Узла дерева ------------------------------------------
template <class T>
TreeNode<T>::TreeNode(T data) :                //конструктор
	left(nullptr), right(nullptr), data(data)
{}

template <class T>
TreeNode<T>::~TreeNode()                       //деструктор
{}

template <class T>
bool TreeNode<T>::isLeaf() {                   //метод проверки, это ли конечный лист
	return !left && !right ? true : false;
}

template <class T>
T& TreeNode<T>::getData() {                    //метод получения основных данных об объекте
	return data;
}

template <class T>
TreeNode<T>* TreeNode<T>::getLeft() {           //метод получения указателя на левый подузел
	return this->left;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRight() {          //метод получения указателя на правый подузел
	return this->right;
}

template <class T>
void TreeNode<T>::setLeft(TreeNode<T>* left) {  //метод установки значения для указателя на левый подузел
	this->left = left;
}

template <class T>
void TreeNode<T>::setRight(TreeNode<T>* right) {//метод установки значения для указателя на правый подузел
	this->right = right;
}

//---------------------------------------- Методы для Бинарного дерево ---------------------------------------------
template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr)    //конструктор
{}

template <class T>
BinaryTree<T>::~BinaryTree()                   //деструктор
{
	clean(root);
}

template <class T>                             //метод проверки дерева на пустоту
bool BinaryTree<T>::empty() {
	return root == nullptr ? true : false;
}

template <class T>
TreeNode<T>* copyTree(TreeNode<T>* node)       //функция копирования деревьев
{
	if (node == NULL)
		return NULL;
	TreeNode<T>* newNode = new TreeNode<T>(node->getData());
	newNode->setLeft(copyTree(node->getLeft()));
	newNode->setRight(copyTree(node->getRight()));
	return newNode;
}

template <class T>
void BinaryTree<T>::setRoot(TreeNode<T>* root) //метод установки значения для указателя на корень дерева
{
	this->root = root;
}

template <class T>
TreeNode<T>*& BinaryTree<T>::getRoot()         //метод получения указателя на корень дерева
{
	return this->root;
}

template <class T>
void BinaryTree<T>::add(TreeNode<T>*& node, T& data)  //метод добавления элемента в дерево
{
	if (!node)
		node = new TreeNode<T>(data);
	else
		data.getWeight() < node->data.getWeight() ? add(node->left, data) : add(node->right, data);
}

template <class T>
void BinaryTree<T>::inorder(const TreeNode<T>* node)  //метод симметричного обхода по дереву
{
	if (node->left)              //левый узел
		inorder(node->left);
	cout << endl << node->data;  //родительский узел
	if (node->right)             //правый узел
		inorder(node->right);
}

template <class T>
void BinaryTree<T>::preorder(const TreeNode<T>* node) //метод прямого обхода по дереву
{
	cout << endl << node->data;  //родительский узел
	if (node->left)              //левый узел
		preorder(node->left);
	if (node->right)             //правый узел
		preorder(node->right);
}

template <class T>
void BinaryTree<T>::postorder(const TreeNode<T>* node) //метод обратного обхода по дереву
{
	if (node->left)              //левый узел
		postorder(node->left);
	if (node->right)             //правый узел
		postorder(node->right);
	cout << endl << node->data;  //родительский узел
}

template <class T>
TreeNode<T>* BinaryTree<T>::find(TreeNode<T>* node, T& data) //метод поиска первого требуемого элемента в дереве
{
	if (!node)
		return nullptr; //false;
	else {
		if (node->data == data)
			return node;
		//return find(node->left, data) || find(node->right, data);
		else if (node->left) return find(node->left, data);
		else if (node->right) return find(node->right, data);
		else return nullptr;
	}
}

template <class T>
void BinaryTree<T>::findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree) //метод поиска всех элементов в дереве, подходящих под условие поиска
{
	if (!node)
		return; //false;
	else
	{
		if (node->data == data)
			newTree.add(newTree.getRoot(), node->data);
		if (node->left)
			findAll(node->left, data, newTree);
		else if (node->right)
			findAll(node->right, data, newTree);
		else
			return;
	}
}

template <class T>
void BinaryTree<T>::clean(TreeNode<T>*& node)     //метод очистки дерева
{
	if (!this->root) return;
	if (node->left)   //левый узел
		clean(node->left);
	if (node->right)  //правый узел
		clean(node->right);
	delete node;      //родительский узел
}

template <class T>
T BinaryTree<T>::findMinimum(TreeNode<T>* node)   //метод поиска минимального листа на правой ветке от удаляемого элемента
{
	if (node->isLeaf())
		return node->data;
	return node->left ? findMinimum(node->left) : findMinimum(node->right);
}

template <class T>
bool BinaryTree<T>::deleteNode(TreeNode<T>*& node, T data) //метода удаления элемента из дерева
{
	if (!node)
		return false;
	else {
		if (node->data == data) { //нашелся требуемый узел
			if (node->isLeaf()) { //если это лист
				delete node;
				node = nullptr;
			}
			else {
				if (node->left && node->right) { //есть два ответвления
					T dataReplace = findMinimum(node->right);
					this->deleteNode(this->root, dataReplace);
					node->data = dataReplace;
				}
				else {
					TreeNode<T>* tempPtr; //есть одно ответвление
					node->left ? tempPtr = node->left : tempPtr = node->right;
					delete node;
					node = tempPtr;
				}
			}
			return true;
		}
		return deleteNode(node->left, data) || deleteNode(node->right, data);
	}
}