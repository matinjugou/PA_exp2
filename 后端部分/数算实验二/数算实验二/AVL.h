#pragma once
#include "newCharStringLink.h"

template <class T>
class TreeNode
{
public:
	T data;
	int height;
	int freq;
	TreeNode* leftChild;
	TreeNode* rightChild;
public:
	TreeNode():leftChild(NULL), rightChild(NULL),freq(1), height(0){}
	~TreeNode();
};

template<class T>
class AVLTree
{
private:
	TreeNode<T> *root;
private:
	void insertpri(TreeNode<T>* &node, T x);
	TreeNode<T>* findpri(TreeNode<T>* node,T x);
	void insubtree(TreeNode<T>* node);
	void Deletepri(TreeNode<T>* &node, T x);
	int getHeight(TreeNode<T>* node);
	void SingleRotateLeft(TreeNode<T>* &k2);
	void SingleRotateRight(TreeNode<T>* &k2);
	void DoubleRotateLR(TreeNode<T>* &k3);
	void DoubleRotateRL(TreeNode<T>* &k3);
	int Max(int cmpa, int cmpb);
public:
	AVLTree():root(NULL){}
	~AVLTree();
	void insert(T x);
	TreeNode<T>* search(T x);
	void Remove(T x);
	void Traversal();
};

template<class T>
inline TreeNode<T>::~TreeNode()
{
	if (leftChild != NULL)
	{
		delete leftChild;
		leftChild = NULL;
	}
	if (rightChild != NULL)
	{
		delete rightChild;
		rightChild = NULL;
	}
}
