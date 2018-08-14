#include "stdafx.h"
#include <string>
#include "OptimalBinarySearchTree.h"


void OptimalBinarySearchTree::generate(int **root_index, int n)
{
	clear();
	generate(root, root_index, 0, n-1);
}

void OptimalBinarySearchTree::generate(BinaryTreeNode<string>* &node, int **root_index, int i, int j)
{
	int l = j-i;
	string str;
	char temp[10];

	if(l >= 0)
	{
		str += "k";
		_itoa_s(root_index[i][l]+1, temp, 10);
		str += temp;
	}
	else
	{
		str += "d";
		_itoa_s(j+1, temp, 10);
		str += temp;
	}

	node = new BinaryTreeNode<string>(str, NULL, NULL);

	if(l >= 0)
	{
		generate(node->left, root_index, i, root_index[i][l]-1);
		generate(node->right, root_index, root_index[i][l]+1, j);
	}
	else
	{
		return;
	}
}
