#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_


#include <stdexcept>
#include "BinaryTree.h"

using namespace std;


template <typename T>
class BinarySearchTree : public BinaryTree<T>
{
public:
	const T& get_min();
	const T& get_max();

	virtual void insert(const T &d)  { insert(root, d); }
	virtual void erase(const T &d)   { erase(root, d); }
	virtual bool contain(const T &d) { return contain(root, d); }

protected:
	BinaryTreeNode<T>* get_min(BinaryTreeNode<T> *subtree) const;
	BinaryTreeNode<T>* get_max(BinaryTreeNode<T> *subtree) const;

	void insert(BinaryTreeNode<T>* &subtree, const T &d);
	void erase(BinaryTreeNode<T>* &subtree, const T &d);
	bool contain(BinaryTreeNode<T> *subtree, const T &d) const;
};


template <typename T>
const T& BinarySearchTree<T>::get_min()
{
	BinaryTreeNode<T> *min_node = get_min(root);

	if(min_node != NULL)
		return min_node->data;
	else
		throw runtime_error();
}

template <typename T>
const T& BinarySearchTree<T>::get_max()
{
	BinaryTreeNode<T> *max_node = get_max(root);
	
	if(max_node != NULL)
		return max_node->data;
	else
		throw runtime_error();
}

template <typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::get_min(BinaryTreeNode<T> *subtree) const
{
	if(subtree != NULL)
	{
		if(subtree->left != NULL)
			return get_min(subtree->left);
		else
			return subtree;
	}
	else
	{
		return NULL;
	}
}

template <typename T>
BinaryTreeNode<T>* BinarySearchTree<T>::get_max(BinaryTreeNode<T> *subtree) const
{
	if(subtree != NULL)
	{
		if(subtree->right != NULL)
			return get_max(subtree->right);
		else
			return subtree;
	}
	else
	{
		return NULL;
	}
}

template <typename T>
void BinarySearchTree<T>::insert(BinaryTreeNode<T>* &subtree, const T &d)
{
	if(subtree == NULL)
		subtree = new BinaryTreeNode<T>(d, NULL, NULL);
	else if(d < subtree->data)
		insert(subtree->left, d);
	else if(subtree->data < d)
		insert(subtree->right, d);
}

template <typename T>
void BinarySearchTree<T>::erase(BinaryTreeNode<T>* &subtree, const T &d)
{
	if(subtree != NULL)
	{
		if(d < subtree->data)
		{
			erase(subtree->left, d);
		}
		else if(subtree->data < d)
		{
			erase(subtree->right, d);
		}
		else
		{
			if(subtree->left != NULL && subtree->right != NULL)
			{
				subtree->data = get_min(subtree->right)->data;
				erase(subtree->right, subtree->data);
			}
			else
			{
				BinaryTreeNode<T> *t = subtree;
				subtree = (subtree->left != NULL) ? subtree->left : subtree->right;
				delete t;
			}
		}
	}
}

template <typename T>
bool BinarySearchTree<T>::contain(BinaryTreeNode<T> *subtree, const T &d) const
{
	if(subtree == NULL)
		return false;
	else if(d < subtree->data)
		return contain(subtree->left, d);
	else if(subtree->data < d)
		return contain(subtree->right, d);
	else
		return true;
}


#endif	// #ifndef _BINARY_SEARCH_TREE_H_
