#pragma once
#include <vector>
#include <stack>

template <class T>
class BinaryTree;
//-------------------------------------------- Узел -----------------------------------------------------
template <class T>
class TreeNode
{
    friend class BinaryTree<T>;
private:
    T data;            //данные
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
    TreeNode<T>* root;                  //корень дерева
public:
    BinaryTree();                       //конструктор
    BinaryTree(const BinaryTree& tree); //конструктор копирования
    BinaryTree<T>& operator=(const BinaryTree<T>& tree);  //оператор =
    ~BinaryTree();                      //деструктор

    void add(TreeNode<T>*& node, T& data);          //метод добавления узла в дерево
    void addByParameter(TreeNode<T>*& node, T& data, T& parameter);  //метод добавления элемента в дерево по параметру
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
    void treeToArray(TreeNode<T>*& node, std::vector<T>& v);
    void uniteTrees(BinaryTree<T>& anotherTree);
    int size(const TreeNode<T>* node);//метод получения размера дерева

    void getMaxRight(TreeNode<T>*& ptr, std::stack<TreeNode<T>*>& s); //получение в ptr нижнего крайнего правого узла с сохранением пути до него в стек s
    void getMaxLeft(TreeNode<T>*& ptr, std::stack<TreeNode<T>*>& s);  //получение в ptr нижнего крайнего левого узла с сохранением пути до него в стек s
    TreeNode<T>* getMaxRight();      //получение самого крайнего правого узла дерева
    TreeNode<T>* getMaxLeft();       //получение самого крайнего левого узла дерева
    void firmwareOfTree();           //прошивка дерева

    //====================================================================
    //Следующие методы(и итератор) работают только для прошитого дерева!
    //====================================================================
    void clearFirmwareTree();        //очистка прошитого дерева
    TreeNode<T>* operator[](int index); //оператор []

    class Iterator
    {
        TreeNode<T>* _current;       //текущий узел дерева
    public:
        Iterator(TreeNode<T>* current = nullptr); //конструктор с параметрами
        ~Iterator() {}

        Iterator operator++(int value);    //двигаться вперед по дереву
        Iterator operator+(int value);     //двигаться вперед по дереву с шагом
        Iterator operator+=(int value);    //двигаться вперед по дереву с шагом
        TreeNode<T>* operator[](int index);    //оператор []
        T& operator*();              //получить данные по указателю
        bool operator!=(BinaryTree<T>::Iterator);   //оператор !=
        bool operator==(Iterator);   //оператор ==
        Iterator operator=(const Iterator& it);
        Iterator(const Iterator& it) {
            _current = it._current;
        }
    };
    //====================================================================

    Iterator begin()                 //вернуть начало дерева
    {
        Iterator it(this->getMaxLeft());
        return it;
    }

    Iterator end()                   //вернуть конец дерева
    {
        Iterator it(this->getMaxRight());
        return it;
    }
};