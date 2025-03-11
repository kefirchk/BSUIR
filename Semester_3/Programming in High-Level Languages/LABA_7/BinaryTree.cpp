#pragma once
#include "BinaryTree.h"
#include "Exception.h"
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
BinaryTree<T>::BinaryTree() : root(nullptr)    //конструктор
{}

template<class T>
BinaryTree<T>::BinaryTree(const BinaryTree& tree) //конструктор копирования
{
    this->root = copyTree(tree.root);
}

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
void BinaryTree<T>::addByParameter(TreeNode<T>*& node, T& data, T& parameter)  //метод добавления элемента в дерево
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
        return nullptr;
    else {
        if (node->data == data)  //объект нашелся
            return node;
        else if (node->left) return find(node->left, data);
        else if (node->right) return find(node->right, data);
        else return nullptr;
    }
}

template <class T>
void BinaryTree<T>::findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree) //метод поиска всех элементов в дереве, подходящих под условие поиска
{
    if (!node)  //узел пустой
        return;
    else
    {
        if (node->data == data)  //элемент нашелся
            newTree.add(newTree.getRoot(), node->data);
        if (node->left)          //идем налево
            findAll(node->left, data, newTree);
        if (node->right)         //идем направо
            findAll(node->right, data, newTree);
        else
            return;
    }
}

template <class T>
void BinaryTree<T>::clean(TreeNode<T>*& node)     //метод очистки дерева
{
    if (!node) return;
    if (node->left)   //левый узел
        clean(node->left);
    if (node->right)  //правый узел
        clean(node->right);
    delete node;      //родительский узел
    node = nullptr;
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
    if (!node)           //узел пустой
        return false;
    else {
        if (node->data == data) { //нашелся требуемый узел
            if (node->isLeaf()) { //если это лист
                delete node;      //удалить узел
                node = nullptr;   //обнуление указателя
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

template <class T>
void BinaryTree<T>::treeToArray(TreeNode<T>*& node, std::vector<T>& v) //метод перезаписи дерева в вектор
{
    if (node)                      //если узел не пустой
        v.push_back(node->data);   //добавить узел в вектор методом push_back класса vector
    else
        return;
    if (node->left) treeToArray(node->left, v);   //если указатель на левый подъузел не нулевой
    if (node->right) treeToArray(node->right, v); //если указатель на правый подъузел не нулевой
}

template<class T>
void BinaryTree<T>::uniteTrees(BinaryTree<T>& anotherTree)  //метод объединения деревьев
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
int BinaryTree<T>::size(const TreeNode<T>* node)  //метод получения размера дерева
{
    if (!node)
        return 0;
    return size(node->left) + size(node->right) + 1;
}


template<class T>
void BinaryTree<T>::getMaxLeft(TreeNode<T>*& ptr, stack<TreeNode<T>*>& s) //метод получения самого крайнего левого элемента дерева с сохранением пути до него в стеке
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
void BinaryTree<T>::getMaxRight(TreeNode<T>*& ptr, stack<TreeNode<T>*>& s) //метод получения самого крайнего правого элемента дерева с сохранением пути до него в стеке
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
TreeNode<T>* BinaryTree<T>::getMaxRight() //метод получения самого крайнего правого элемента дерева
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
TreeNode<T>* BinaryTree<T>::getMaxLeft() //метод получения самого крайнего левого элемента дерева
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
void BinaryTree<T>::firmwareOfTree() //метод прошивки дерева
{
    if (this->empty()) return; //если дерево пустое
    TreeNode<T>* ptr = this->root, * temp; //ptr - указатель для обхода по дереву, temp - временный указатель на узел дерева
    stack <TreeNode<T>*> s;    //стек для хранения пройденных узлов дерева, при "спуске вниз" по дереву
    this->getMaxLeft(ptr, s);  //ptr - самый крайний левый элемент, s хранит путь до этого узла
    this->root = ptr;          //установка корня дерева на элемент, на который указывает ptr
    while (ptr || !s.empty())
    {
        while (!s.empty() && !ptr->right)
        {
            ptr->right = s.top(); //запись адреса элемента вершины стека в адрес указателя на правый узел дерева
            ptr = s.top();        //передвинуть указатель на элемент дерева, который является вершиной стека
            s.pop();              //удаление вершины стека
        }
        temp = ptr;               //запоминаем текущие положение указателя ptr в дереве
        ptr = ptr->right;         //передвигаем указатель
        getMaxLeft(ptr, s);       //получение самого крайнего левого элемента в ptr, s - путь до него
        temp->right = ptr;        //изменение указателя на правый лист узла дерева, на который указывает temp
    }
}

template<class T>
void BinaryTree<T>::clearFirmwareTree()  //метод очистки прошитого дерева
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
TreeNode<T>* BinaryTree<T>::operator[](int index)  //оператор []
{
    try
    {
        if (index < 0 || index > this->size(this->getRoot()))
            throw Exception(this, "Ошибка ипользования контейнера!", "Выход за границы контейнера!");
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
BinaryTree<T>::Iterator::Iterator(TreeNode<T>* current) //конструктор итератора с параметрами
    : _current(current)
{}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator++(int) //оператор постинкремента, чтобы сдвинуться вперед по дереву
{
    if (_current)
        _current = _current->right;
    return _current;
}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator+(int value) //оператор +, чтобы сдвинуться вперед по дереву с шагом
{
    for (; _current && value; value--)
        _current = _current->right;
    return _current;
}

template<typename T>
typename BinaryTree<T>::Iterator BinaryTree<T>::Iterator::operator+=(int value)//оператор +=, чтобы сдвинуться вперед по дереву с шагом
{
    for (int i = 0; i < value; ++i)
        _current = _current->_next;
    return _current;
}

template<class T>
T& BinaryTree<T>::Iterator::operator*() //оператор *, чтобы получить данные в узле
{
    return _current->data;
}

template<typename T>
bool BinaryTree<T>::Iterator::operator!=(BinaryTree<T>::Iterator other) //оператор !=
{
    return _current != other._current ? true : false;
}

template<typename T>
bool BinaryTree<T>::Iterator::operator==(Iterator other) //оператор ==
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
typename TreeNode<T>* BinaryTree<T>::Iterator::operator[](int index)  //оператор []
{
    for (; index && this; --index)
        (*this)++;
    return this->_current;
}

template<class T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T>& tree)  //оператор =
{
    if (this != &tree)
    {
        this->root = copyTree(tree.root);
    }
    return *this;
}