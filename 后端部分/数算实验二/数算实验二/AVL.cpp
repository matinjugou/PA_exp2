
#include "stdafx.h"
#include "AVL.h"
template<class T>
int AVLTree<T>::getHeight(TreeNode<T>* node)
{
	if (node != NULL)
		return node->height;
	return -1;
}

template<class T>
int AVLTree<T>::Max(int cmpa, int cmpb)
{
	return cmpa > cmpb ? cmpa : cmpb; 
}

template<class T>
void AVLTree<T>::SingleRotateLeft(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	k1 = k2->leftChild;
	k2->leftChild = k1->rightChild;
	k1->rightChild = k2;

	k2->height = Max(getHeight(k2->leftChild), getHeight(k2->rightChild)) + 1;
	k1->height = Max(getHeight(k1->leftChild), k2->height) + 1;
	k2 = k1;
}

template<class T>
void AVLTree<T>::SingleRotateRight(TreeNode<T>* &k2)
{
	TreeNode<T>* k1;
	k1 = k2->rightChild;
	k2->rightChild = k1->leftChild;
	k1->leftChild = k2;

	k2->height = Max(getHeight(k2->leftChild), getHeight(k2->rightChild)) + 1;
	k1->height = Max(getHeight(k1->rightChild), k2->height) + 1;
	k2 = k1;
}

template<class T>
void AVLTree<T>::DoubleRotateLR(TreeNode<T>* &k3)
{
	SingleRotateRight(k3->leftChild);
	SingleRotateLeft(k3);
}

template<class T>
void AVLTree<T>::DoubleRotateRL(TreeNode<T>* &k3)
{
	SingleRotateLeft(k3->rightChild);
	SingleRotateRight(k3);
}

template<class T>
void AVLTree<T>::insertpri(TreeNode<T>* &node, T x)
{
	if (node == NULL)
	{
		node = new TreeNode<T>();
		node->data = x;
		return;
	}
	if (node->data > x)
	{
		insertpri(node->leftChild, x);
		if ((getHeight(node->leftChild) - getHeight(node->rightChild)) == 2)
			if (x < node->leftChild->data)
				SingleRotateLeft(node);
			else
				DoubleRotateLR(node);
	}
	else if (node->data < x)
	{
		insertpri(node->rightChild, x);
		if ((getHeight(node->rightChild) - getHeight(node->leftChild)) == 2)
			if (x > node->rightChild->data)
				SingleRotateRight(node);
			else
				DoubleRotateRL(node);
	}
	else node->freq++;
	node->height = Max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
}

template<class T>
AVLTree<T>::~AVLTree()
{
	if (root != NULL)
	{
		delete root;
	}
}

template<class T>
void AVLTree<T>::insert(T x)
{
	insertpri(root, x);
}

template<class T>
TreeNode<T>* AVLTree<T>::findpri(TreeNode<T>* node, T x)
{
	if (node == NULL)
		return NULL;
	if (node->data > x)
	{
		return findpri(node->leftChild, x);
	}
	else if (node->data < x)
	{
		return findpri(node->rightChild, x);
	}
	else
		return node;
}

template<class T>
TreeNode<T>* AVLTree<T>::search(T x)
{
	return findpri(root, x);
}

template<class T>
void AVLTree<T>::Deletepri(TreeNode<T>* &node, T x)
{
	if (node == NULL)
		return;
	if (x < node->data)
	{
		Deletepri(node->leftChild, x);
		if (getHeight(node->rightChild) - getHeight(node->leftChild) == 2)
		{
			if (node->rightChild->leftChild != NULL && (getHeight(node->rightChild->leftChild) > getHeight(node->rightChild->rightChild)))
			{
				DoubleRotateRL(node);
			}
			else
			{
				SingleRotateRight(node);
			}
		}
	}
	else if (x > node->data)
	{
		Deletepri(node->rightChild, x);
		if (getHeight(node->leftChild) - getHeight(node->rightChild) == 2)
		{
			if (node->leftChild->rightChild != NULL && (getHeight(node->leftChild->rightChild) > getHeight(node->leftChild->leftChild)))
			{
				DoubleRotateLR(node);
			}
			else
			{
				SingleRotateLeft(node);
			}
		}
	}
	else
	{
		if (node->leftChild && node->rightChild)
		{
			TreeNode<T>* temp = node->rightChild;
			while (temp->leftChild != NULL)
				temp = temp->leftChild;
			node->data = temp->data;
			node->freq = temp->freq;
			Deletepri(node->rightChild, temp->data);
			if (getHeight(node->leftChild) - getHeight(node->rightChild) == 2)
			{
				if (node->leftChild->rightChild != NULL && (getHeight(node->leftChild->rightChild) > getHeight(node->leftChild->leftChild)))
					DoubleRotateLR(node);
				else
					SingleRotateLeft(node);
			}
		}
		else
		{
			TreeNode<T>* temp = node;
			if (node->leftChild == NULL)
				node = node->rightChild;
			else if (node->rightChild == NULL)
				node = node->leftChild;
			delete(temp);
			temp = NULL;
		}
	}
	if (node == NULL)
		return;
	node->height = Max(getHeight(node->leftChild), getHeight(node->rightChild)) + 1;
	return;
}

template<class T>
void AVLTree<T>::Remove(T x)
{
	Deletepri(root, x);
}

template<class T>
void AVLTree<T>::insubtree(TreeNode<T>* node)
{
	if (node == NULL)
		return;
	insubtree(node->leftChild);
	cout << node->data << "";
	insubtree(node->rightChild);
}

template<class T>
void AVLTree<T>::Traversal()
{
	insubtree(root);
}