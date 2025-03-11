#include "BinaryTree.h"
#include <iostream>
using namespace std;

//----------------------------------------------- ������ ��� ���� ������ ------------------------------------------
template <class T>
TreeNode<T>::TreeNode(T data) :                //�����������
	left(nullptr), right(nullptr), data(data)
{}

template <class T>
TreeNode<T>::~TreeNode()                       //����������
{}

template <class T>
bool TreeNode<T>::isLeaf() {                   //����� ��������, ��� �� �������� ����
	return !left && !right ? true : false;
}

template <class T>
T& TreeNode<T>::getData() {                    //����� ��������� �������� ������ �� �������
	return data;
}

template <class T>
TreeNode<T>* TreeNode<T>::getLeft() {           //����� ��������� ��������� �� ����� �������
	return this->left;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRight() {          //����� ��������� ��������� �� ������ �������
	return this->right;
}

template <class T>
void TreeNode<T>::setLeft(TreeNode<T>* left) {  //����� ��������� �������� ��� ��������� �� ����� �������
	this->left = left;
}

template <class T>
void TreeNode<T>::setRight(TreeNode<T>* right) {//����� ��������� �������� ��� ��������� �� ������ �������
	this->right = right;
}

//---------------------------------------- ������ ��� ��������� ������ ---------------------------------------------
template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr)    //�����������
{}

template <class T>
BinaryTree<T>::~BinaryTree()                   //����������
{
	clean(root);
}

template <class T>                             //����� �������� ������ �� �������
bool BinaryTree<T>::empty() {
	return root == nullptr ? true : false;
}

template <class T>
TreeNode<T>* copyTree(TreeNode<T>* node)       //������� ����������� ��������
{
	if (node == NULL)
		return NULL;
	TreeNode<T>* newNode = new TreeNode<T>(node->getData());
	newNode->setLeft(copyTree(node->getLeft()));
	newNode->setRight(copyTree(node->getRight()));
	return newNode;
}

template <class T>
void BinaryTree<T>::setRoot(TreeNode<T>* root) //����� ��������� �������� ��� ��������� �� ������ ������
{
	this->root = root;
}

template <class T>
TreeNode<T>*& BinaryTree<T>::getRoot()         //����� ��������� ��������� �� ������ ������
{
	return this->root;
}

template <class T>
void BinaryTree<T>::add(TreeNode<T>*& node, T& data)  //����� ���������� �������� � ������
{
	if (!node)
		node = new TreeNode<T>(data);
	else
		data.getWeight() < node->data.getWeight() ? add(node->left, data) : add(node->right, data);
}

template <class T>
void BinaryTree<T>::inorder(const TreeNode<T>* node)  //����� ������������� ������ �� ������
{
	if (node->left)              //����� ����
		inorder(node->left);
	cout << endl << node->data;  //������������ ����
	if (node->right)             //������ ����
		inorder(node->right);
}

template <class T>
void BinaryTree<T>::preorder(const TreeNode<T>* node) //����� ������� ������ �� ������
{
	cout << endl << node->data;  //������������ ����
	if (node->left)              //����� ����
		preorder(node->left);
	if (node->right)             //������ ����
		preorder(node->right);
}

template <class T>
void BinaryTree<T>::postorder(const TreeNode<T>* node) //����� ��������� ������ �� ������
{
	if (node->left)              //����� ����
		postorder(node->left);
	if (node->right)             //������ ����
		postorder(node->right);
	cout << endl << node->data;  //������������ ����
}

template <class T>
TreeNode<T>* BinaryTree<T>::find(TreeNode<T>* node, T& data) //����� ������ ������� ���������� �������� � ������
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
void BinaryTree<T>::findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree) //����� ������ ���� ��������� � ������, ���������� ��� ������� ������
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
void BinaryTree<T>::clean(TreeNode<T>*& node)     //����� ������� ������
{
	if (!this->root) return;
	if (node->left)   //����� ����
		clean(node->left);
	if (node->right)  //������ ����
		clean(node->right);
	delete node;      //������������ ����
}

template <class T>
T BinaryTree<T>::findMinimum(TreeNode<T>* node)   //����� ������ ������������ ����� �� ������ ����� �� ���������� ��������
{
	if (node->isLeaf())
		return node->data;
	return node->left ? findMinimum(node->left) : findMinimum(node->right);
}

template <class T>
bool BinaryTree<T>::deleteNode(TreeNode<T>*& node, T data) //������ �������� �������� �� ������
{
	if (!node)
		return false;
	else {
		if (node->data == data) { //������� ��������� ����
			if (node->isLeaf()) { //���� ��� ����
				delete node;
				node = nullptr;
			}
			else {
				if (node->left && node->right) { //���� ��� �����������
					T dataReplace = findMinimum(node->right);
					this->deleteNode(this->root, dataReplace);
					node->data = dataReplace;
				}
				else {
					TreeNode<T>* tempPtr; //���� ���� �����������
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