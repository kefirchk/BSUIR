#pragma once
#include <vector>
#include <stack>

template <class T>
class BinaryTree;
//-------------------------------------------- ���� -----------------------------------------------------
template <class T>
class TreeNode
{
    friend class BinaryTree<T>;
private:
    T data;            //������
    TreeNode* left;    //��������� �� ����� ����
    TreeNode* right;   //��������� �� ������ ����
public:
    TreeNode(T data);  //�����������
    ~TreeNode();       //����������
    bool isLeaf();     //����� ��������, �������� �� �������� ���� ������
    T& getData();      //����� ��������� ������ �� �������
    TreeNode<T>* getLeft();            //����� ��������� ��������� �� ����� �������
    TreeNode<T>* getRight();           //����� ��������� ��������� �� ������ �������
    void setLeft(TreeNode<T>* left);   //����� ��������� �������� ��� ��������� �� ����� �������
    void setRight(TreeNode<T>* right); //����� ��������� �������� ��� ��������� �� ������ �������
};

//-------------------------------------------- �������� ������ ------------------------------------------
template <class T>
class BinaryTree
{
private:
    TreeNode<T>* root;                  //������ ������
public:
    BinaryTree();                       //�����������
    BinaryTree(const BinaryTree& tree); //����������� �����������
    BinaryTree<T>& operator=(const BinaryTree<T>& tree);  //�������� =
    ~BinaryTree();                      //����������

    void add(TreeNode<T>*& node, T& data);          //����� ���������� ���� � ������
    void addByParameter(TreeNode<T>*& node, T& data, T& parameter);  //����� ���������� �������� � ������ �� ���������
    void inorder(const TreeNode<T>* node);          //������������ �����(����� ����->������->������ ����)
    void preorder(const TreeNode<T>* node);         //������ ����� (������->����� ����->������ ����)
    void postorder(const TreeNode<T>* node);        //�������� ����� (����� ����->������ ����->������)
    TreeNode<T>* find(TreeNode<T>* node, T& data);  //����� ������ ����
    void findAll(TreeNode<T>* node, T& data, BinaryTree<T>& newTree);  //����� ������ ���� ����� � ������� ����������������
    bool deleteNode(TreeNode<T>*& node, T data);    //����� �������� ���� ������
    T findMinimum(TreeNode<T>* node); //����� ������ ������������(������ �������� ������ ���� ��� ������� ���� ���������), ������������ � ������ �������� ����
    void clean(TreeNode<T>*& node);   //����� ������� ������
    void setRoot(TreeNode<T>* root);  //����� ��������� �������� ��� ��������� �� ������ ������
    TreeNode<T>*& getRoot();          //����� ��������� ��������� �� ������ ������
    bool empty();                     //����� �������� ������ �� �������
    void treeToArray(TreeNode<T>*& node, std::vector<T>& v);
    void uniteTrees(BinaryTree<T>& anotherTree);
    int size(const TreeNode<T>* node);//����� ��������� ������� ������

    void getMaxRight(TreeNode<T>*& ptr, std::stack<TreeNode<T>*>& s); //��������� � ptr ������� �������� ������� ���� � ����������� ���� �� ���� � ���� s
    void getMaxLeft(TreeNode<T>*& ptr, std::stack<TreeNode<T>*>& s);  //��������� � ptr ������� �������� ������ ���� � ����������� ���� �� ���� � ���� s
    TreeNode<T>* getMaxRight();      //��������� ������ �������� ������� ���� ������
    TreeNode<T>* getMaxLeft();       //��������� ������ �������� ������ ���� ������
    void firmwareOfTree();           //�������� ������

    //====================================================================
    //��������� ������(� ��������) �������� ������ ��� ��������� ������!
    //====================================================================
    void clearFirmwareTree();        //������� ��������� ������
    TreeNode<T>* operator[](int index); //�������� []

    class Iterator
    {
        TreeNode<T>* _current;       //������� ���� ������
    public:
        Iterator(TreeNode<T>* current = nullptr); //����������� � �����������
        ~Iterator() {}

        Iterator operator++(int value);    //��������� ������ �� ������
        Iterator operator+(int value);     //��������� ������ �� ������ � �����
        Iterator operator+=(int value);    //��������� ������ �� ������ � �����
        TreeNode<T>* operator[](int index);    //�������� []
        T& operator*();              //�������� ������ �� ���������
        bool operator!=(BinaryTree<T>::Iterator);   //�������� !=
        bool operator==(Iterator);   //�������� ==
        Iterator operator=(const Iterator& it);
        Iterator(const Iterator& it) {
            _current = it._current;
        }
    };
    //====================================================================

    Iterator begin()                 //������� ������ ������
    {
        Iterator it(this->getMaxLeft());
        return it;
    }

    Iterator end()                   //������� ����� ������
    {
        Iterator it(this->getMaxRight());
        return it;
    }
};