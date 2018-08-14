#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_


#include <iostream>
#include <string>

using namespace std;


template <typename T>
struct BinaryTreeNode
{
	BinaryTreeNode() : data(), left(NULL), right(NULL) {}
	BinaryTreeNode(const T &d, BinaryTreeNode *l, BinaryTreeNode *r) : data(d), left(l), right(r) {}

	T data;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};


template <typename T>
class BinaryTree
{
public:
	BinaryTree(): root(NULL)			{}
	BinaryTree(const BinaryTree &rhs)	{ root = clone(rhs.root); }
	virtual ~BinaryTree()				{ clear(root); }
	BinaryTree& operator=(const BinaryTree &rhs);

	virtual void insert(const T &d) = 0;
	virtual void erase(const T &d) = 0;
	virtual bool contain(const T &d) = 0;

	const BinaryTreeNode<T>* get_root() const	{ return root; }
	int get_height() const						{ return get_height(root); }
	bool empty() const							{ return (root == NULL); }
	void clear()								{ clear(root); }

	void print_preorder(ostream &os, const string &separator = " ") const  { print_preorder(root, os, separator); }
	void print_inorder(ostream &os, const string &separator = " ") const   { print_inorder(root, os, separator); }
	void print_postorder(ostream &os, const string &separator = " ") const { print_postorder(root, os, separator); }

protected:
	BinaryTreeNode<T> *root;

private:
	BinaryTreeNode<T>* clone(BinaryTreeNode<T> *subtree);
	void clear(BinaryTreeNode<T>* &subtree);
	int get_height(BinaryTreeNode<T> *subtree) const;
	void print_preorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator = " ") const;
	void print_inorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator = " ") const;
	void print_postorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator = " ") const;
};


template <typename T>
BinaryTree<T>& BinaryTree<T>::operator=(const BinaryTree<T> &rhs)
{
	if(this != &rhs)
	{
		clear(root);
		root = clone(rhs.root);
	}

	return *this;
}

template <typename T>
BinaryTreeNode<T>* BinaryTree<T>::clone(BinaryTreeNode<T> *subtree)
{
	if(subtree != NULL)
		return new BinaryTreeNode<T>(subtree->data, clone(subtree->left), clone(subtree->right));
	else
		return NULL;
}

template <typename T>
void BinaryTree<T>::clear(BinaryTreeNode<T>* &subtree)
{
	if(subtree != NULL)
	{
		clear(subtree->left);
		clear(subtree->right);
		delete subtree;
		subtree = NULL;
	}
}

template <typename T>
int BinaryTree<T>::get_height(BinaryTreeNode<T> *subtree) const
{
	if(subtree == NULL)
		return -1;

	int lh = get_height(subtree->left);
	int rh = get_height(subtree->right);
	int h = (lh > rh) ? lh : rh;
	return (h+1);
}

template <typename T>
void BinaryTree<T>::print_preorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator) const
{
	if(subtree != NULL)
	{
		os << subtree->data << separator;
		print_preorder(subtree->left, os, separator);
		print_preorder(subtree->right, os, separator);
	}
}

template <typename T>
void BinaryTree<T>::print_inorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator) const
{
	if(subtree != NULL)
	{
		print_inorder(subtree->left, os, separator);
		os << subtree->data << separator;
		print_inorder(subtree->right, os, separator);
	}
}

template <typename T>
void BinaryTree<T>::print_postorder(BinaryTreeNode<T> *subtree, ostream &os, const string &separator) const
{
	if(subtree != NULL)
	{
		print_postorder(subtree->left, os, separator);
		print_postorder(subtree->right, os, separator);
		os << subtree->data << separator;
	}
}


#endif // #ifndef _BINARY_TREE_H_
