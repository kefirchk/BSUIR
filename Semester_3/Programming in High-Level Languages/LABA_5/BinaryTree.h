#pragma once
//-------------------------------------------- ���� ----------------------------------------------------- 
template <class T>
class TreeNode
{
	template <class T>
	friend class BinaryTree;
private:
	T data;
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
	TreeNode<T>* root;
public:
	BinaryTree();      //�����������
	~BinaryTree();     //����������

	void add(TreeNode<T>*& node, T& data);          //����� ���������� ���� � ������
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
};