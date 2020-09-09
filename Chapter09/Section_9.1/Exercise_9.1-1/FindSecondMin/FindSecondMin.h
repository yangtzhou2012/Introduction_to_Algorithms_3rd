#ifndef _FIND_SECOND_MIN_H_
#define _FIND_SECOND_MIN_H_

#define DEBUG_INFO_EN	0

#if DEBUG_INFO_EN
#include <fstream>
using namespace std;
#endif

struct TreeNode
{
	int idx;
	TreeNode *left;
	TreeNode *right;
};

static void DestroyTree(TreeNode *root)
{
	if (root)
	{
		TreeNode *l = root->left;
		TreeNode *r = root->right;

		delete root;
		DestroyTree(l);
		DestroyTree(r);
	}
}

// return value: the index of the second minimal element
template <typename T>
int FindSecondMin(const T data[], int n)
{
	if (data == NULL || n < 2)
		return -1;

	TreeNode **curLayer = new TreeNode*[n];
	TreeNode **nextLayer = new TreeNode*[(n+1)/2];
	int curLayerNodeCnt = n;
	int nextLayerNodeCnt = 0;
	int i = 0;

#if DEBUG_INFO_EN
	ofstream os("debug.txt");
#endif

	for (i = 0; i < n; ++i)
	{
		TreeNode *node = new TreeNode;
		node->idx = i;
		node->left = node->right = NULL;
		curLayer[i] = node;
#if DEBUG_INFO_EN
		os << node->idx << "[" << data[node->idx] << "]\t";
#endif
	}

#if DEBUG_INFO_EN
	os << "\n";
#endif

	while (curLayerNodeCnt > 1)
	{
		nextLayerNodeCnt = 0;

		for (i = 0; i < curLayerNodeCnt-1; i += 2)
		{
			TreeNode *node = new TreeNode;
			int idx1 = curLayer[i]->idx;
			int idx2 = curLayer[i+1]->idx;

			if (data[idx1] < data[idx2])
			{
				node->idx = idx1;
				node->left = curLayer[i];
				node->right = curLayer[i+1];
			}
			else
			{
				node->idx = idx2;
				node->left = curLayer[i+1];
				node->right = curLayer[i];
			}

			nextLayer[nextLayerNodeCnt] = node;
			nextLayerNodeCnt++;
#if DEBUG_INFO_EN
			os << node->idx << "[" << data[node->idx] << "]\t";
#endif
		}

		if (i == curLayerNodeCnt-1)
		{
			TreeNode *node = new TreeNode;
			node->idx = curLayer[i]->idx;
			node->left = curLayer[i]->left;
			node->right = curLayer[i]->right;

			nextLayer[nextLayerNodeCnt] = node;
			nextLayerNodeCnt++;
#if DEBUG_INFO_EN
			os << node->idx << "[" << data[node->idx] << "]\t";
#endif
		}

#if DEBUG_INFO_EN
		os << "\n";
#endif

		TreeNode **temp = curLayer;
		curLayer = nextLayer;
		nextLayer = temp;
		curLayerNodeCnt = nextLayerNodeCnt;
	}

	TreeNode *node = *curLayer;
	int secondMinIdx = node->right->idx;
	node = node->left;

	while (node->left)
	{
		if (data[node->right->idx] < data[secondMinIdx])
			secondMinIdx = node->right->idx;

		node = node->left;
	}

	DestroyTree(*curLayer);
	delete[] curLayer;
	delete[] nextLayer;
	return secondMinIdx;
}

#endif // #ifndef _FIND_SECOND_MIN_H_
