#pragma once
#include "BinaryTree.h"
#include "Exception.h"
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
BinaryTree<T>::BinaryTree() : root(nullptr)    //�����������
{}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree& tree) //����������� �����������
{
    this->root = copyTree(tree.root);
}

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
void BinaryTree<T>::addByParameter(TreeNode<T>*& node, T& data, T& parameter)  //����� ���������� �������� � ������
{
    if (!node)
        node = new TreeNode<T>(data);
    else
    {
        T dataCopy = data;
        T nodeInfo = node->data;
        dataCopy.cleanSomeFields(parameter);
        nodeInfo.cleanSomeFields(parameter);
        dataCopy < nodeInfo ? addByParameter(node->left, data, parameter) : addByParameter(node->right, data, parameter);
    }
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
        return nullptr;
    else {
        if (node->data == data)  //������ �������
            return node;
        else if (node->left) return find(node->left, data);
        else if (node->right) return find(node->right, data);
        else return nullptr;
    }
}

template <class T>
void BinaryTree<T>::findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree) //����� ������ ���� ��������� � ������, ���������� ��� ������� ������
{
    if (!node)  //���� ������
        return;
    else
    {
        if (node->data == data)  //������� �������
            newTree.add(newTree.getRoot(), node->data);
        if (node->left)          //���� ������
            findAll(node->left, data, newTree);
        if (node->right)         //���� �������
            findAll(node->right, data, newTree);
        else
            return;
    }
}

template <class T>
void BinaryTree<T>::clean(TreeNode<T>*& node)     //����� ������� ������
{
    if (!node) return;
    if (node->left)   //����� ����
        clean(node->left);
    if (node->right)  //������ ����
        clean(node->right);
    delete node;      //������������ ����
    node = nullptr;
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
    if (!node)           //���� ������
        return false;
    else {
        if (node->data == data) { //������� ��������� ����
            if (node->isLeaf()) { //���� ��� ����
                delete node;      //������� ����
                node = nullptr;   //��������� ���������
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

template <class T>
void BinaryTree<T>::treeToArray(TreeNode<T>*& node, std::vector<T>& v) //����� ���������� ������ � ������
{
    if (node)                      //���� ���� �� ������
        v.push_back(node->data);   //�������� ���� � ������ ������� push_back ������ vector
    else
        return;
    if (node->left) treeToArray(node->left, v);   //���� ��������� �� ����� �������� �� �������
    if (node->right) treeToArray(node->right, v); //���� ��������� �� ������ �������� �� �������
}

template<class T>
void BinaryTree<T>::uniteTrees(BinaryTree<T>& anotherTree)  //����� ����������� ��������
{
    if (!anotherTree.empty())
    {
        vector <T> v;
        anotherTree.treeToArray(anotherTree.getRoot(), v);
        for (unsigned int i = 0; i < v.size(); i++)
            this->add(root, v[i]);
    }
}

template <class T>
int BinaryTree<T>::size(const TreeNode<T>* node)  //����� ��������� ������� ������
{
    if (!node)
        return 0;
    return size(node->left) + size(node->right) + 1;
}


template<class T>
void BinaryTree<T>::getMaxLeft(TreeNode<T>*& ptr, stack<TreeNode<T>*>& s) //����� ��������� ������ �������� ������ �������� ������ � ����������� ���� �� ���� � �����
{
    while (ptr)
    {
        if (ptr->left)
        {
            s.push(ptr);
            ptr = ptr->left;
        }
        else
            return;
    }
}

template<class T>
void BinaryTree<T>::getMaxRight(TreeNode<T>*& ptr, stack<TreeNode<T>*>& s) //����� ��������� ������ �������� ������� �������� ������ � ����������� ���� �� ���� � �����
{
    while (ptr)
    {
        if (ptr->right)
        {
            s.push(ptr);
            ptr = ptr->right;
        }
        else
            return;
    }
}

template<class T>
TreeNode<T>* BinaryTree<T>::getMaxRight() //����� ��������� ������ �������� ������� �������� ������
{
    TreeNode<T>* ptr = this->getRoot();
    while (ptr)
    {
        if (ptr->right)
            ptr = ptr->right;
        else
            return ptr;
    }
    return ptr;
}

template<class T>
TreeNode<T>* BinaryTree<T>::getMaxLeft() //����� ��������� ������ �������� ������ �������� ������
{
    TreeNode<T>* ptr = this->getRoot();
    while (ptr)
    {
        if (ptr->left)
            ptr = ptr->left;
        else
            return ptr;
    }
    return ptr;
}

template<class T>
void BinaryTree<T>::firmwareOfTree() //����� �������� ������
{
    if (this->empty()) return; //���� ������ ������
    TreeNode<T>* ptr = this->root, * temp; //ptr - ��������� ��� ������ �� ������, temp - ��������� ��������� �� ���� ������
    stack <TreeNode<T>*> s;    //���� ��� �������� ���������� ����� ������, ��� "������ ����" �� ������
    this->getMaxLeft(ptr, s);  //ptr - ����� ������� ����� �������, s ������ ���� �� ����� ����
    this->root = ptr;          //��������� ����� ������ �� �������, �� ������� ��������� ptr
    while (ptr || !s.empty())
    {
        while (!s.empty() && !ptr->right)
        {
            ptr->right = s.top(); //������ ������ �������� ������� ����� � ����� ��������� �� ������ ���� ������
            ptr = s.top();        //����������� ��������� �� ������� ������, ������� �������� �������� �����
            s.pop();              //�������� ������� �����
        }
        temp = ptr;               //���������� ������� ��������� ��������� ptr � ������
        ptr = ptr->right;         //����������� ���������
        getMaxLeft(ptr, s);       //��������� ������ �������� ������ �������� � ptr, s - ���� �� ����
        temp->right = ptr;        //��������� ��������� �� ������ ���� ���� ������, �� ������� ��������� temp
    }
}

template<class T>
void BinaryTree<T>::clearFirmwareTree()  //����� ������� ��������� ������
{
    TreeNode<T>* ptr = this->root, * temp;
    while (ptr)
    {
        temp = ptr;
        ptr = ptr->right;
        delete temp;
    }
    this->root = nullptr;
}

template<class T>
TreeNode<T>* BinaryTree<T>::operator[](int index)  //�������� []
{
    try
    {
        if (index < 0 || index > this->size(this->getRoot()))
            throw Exception(this, "������ ������������ ����������!", "����� �� ������� ����������!");
        TreeNode<T>* ptr = this->root, * rez = nullptr;
        for (int i = 0; i != index && ptr; i++)
            ptr = ptr->right;

        if (ptr)
            rez = new TreeNode<T>(ptr->getData());
        this->clearFirmwareTree();
        return rez;
    }
    catch (Exception& err)
    {
        err.what();
        return nullptr;
    }
}

template<typename T>
BinaryTree<T>::Iterator::Iterator(TreeNode<T>* current) //����������� ��������� � �����������
    : _current(current)
{}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator++(int) //�������� ��������������, ����� ���������� ������ �� ������
{
    if (_current)
        _current = _current->right;
    return _current;
}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator+(int value) //�������� +, ����� ���������� ������ �� ������ � �����
{
    for (; _current && value; value--)
        _current = _current->right;
    return _current;
}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator+=(int value)//�������� +=, ����� ���������� ������ �� ������ � �����
{
    for (int i = 0; i < value; ++i)
        _current = _current->_next;
    return _current;
}

template<class T>
T& BinaryTree<T>::Iterator::operator*() //�������� *, ����� �������� ������ � ����
{
    return _current->data;
}

template<typename T>
bool BinaryTree<T>::Iterator::operator!=(BinaryTree<T>::Iterator other) //�������� !=
{
    return _current != other._current ? true : false;
}

template<typename T>
bool BinaryTree<T>::Iterator::operator==(Iterator other) //�������� ==
{
    return !(*this == other);
}

template<class T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator=(const typename BinaryTree<T>::Iterator& it)
{
    _current = it._current;
    return *this;
}

template<class T>
typename TreeNode<T>* BinaryTree<T>::Iterator::operator[](int index)  //�������� []
{
    for (; index && this; --index)
        (*this)++;
    return this->_current;
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)  //�������� =
{
    if (this != &tree)
    {
        this->root = copyTree(tree.root);
    }
    return *this;
}