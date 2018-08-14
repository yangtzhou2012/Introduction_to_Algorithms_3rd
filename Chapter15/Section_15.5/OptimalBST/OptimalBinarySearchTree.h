#ifndef _OPTIMAL_BINARY_SEARCH_TREE_H_
#define _OPTIMAL_BINARY_SEARCH_TREE_H_


#include <iostream>
#include <fstream>
#include <string>
#include "BinarySearchTree.h"

using namespace std;


#define _DEBUG_EN_


class OptimalBinarySearchTree: public BinarySearchTree<string>
{
public:
	template <typename T> bool build(const T keyPR[], const T dummyPR[], int n);

private:
	void generate(int **root_index, int n);
	void generate(BinaryTreeNode<string>* &node, int **root_index, int i, int j);
};


#ifdef _DEBUG_EN_
template <typename T>
void PrintDebugInfo(const T dummyPR[], T **cost, T **w, int **root, int n, ostream &os)
{
	os << "cost:\n";

	for(int l = n-1; l >= 0; --l)
	{
		for(int i = 0; i < n-l; ++i)
			os << cost[i][l] << "\t";
		os << "\n";
	}

	for(int i = 0; i <= n; ++i)
		os << dummyPR[i] << "\t";

	os << "\n\n" << "w:\n";

	for(int l = n-1; l >= 0; --l)
	{
		for(int i = 0; i < n-l; ++i)
			os << w[i][l] << "\t";
		os << "\n";
	}

	for(int i = 0; i <= n; ++i)
		os << dummyPR[i] << "\t";

	os << "\n\n" << "root:\n";

	for(int l = n-1; l >= 0; --l)
	{
		for(int i = 0; i < n-l; ++i)
			os << root[i][l] << "\t";
		os << "\n";
	}

	os << "\n";
}
#endif // #ifdef _DEBUG_EN_

template <typename T>
bool OptimalBinarySearchTree::build(const T keyPR[], const T dummyPR[], int n)
{
	clear();

	if(dummyPR == NULL || n < 0 || (keyPR == NULL && n > 0))
		return false;

	// cost[0] -- { e[1,1] e[1,2] e[1,3] ... e[1,n] }
	// cost[1] -- { e[2,2] e[2,3] ... e[2,n] }
	// ... ...
	// cost[n] -- { e[n,n] }
	T **cost = NULL;
	T **w = NULL;
	int **root_index = NULL;

	if(n > 0)
	{
		cost = new T*[n];
		w = new T*[n];
		root_index = new int*[n];

		for(int i = 0; i < n; ++i)
		{
			cost[i] = new T[n-i];
			w[i] = new T[n-i];
			root_index[i] = new int[n-i];
		}
	}

	for(int l = 0; l < n; ++l)
	{
		for(int i = 0; i < n-l; ++i)
		{
			int j = i+l;

			w[i][l] = (l > 0 ? w[i][l-1] : dummyPR[i]) + keyPR[j] + dummyPR[j+1];

			T minCost = dummyPR[i] + (l > 0 ? cost[i+1][l-1] : dummyPR[i+1]) + w[i][l];
			int optimalRoot = i;

			for(int r = i+1; r <= j; ++r)
			{
				T curCost = cost[i][r-i-1] + (r < j ? cost[r+1][j-r-1] : dummyPR[r+1]) + w[i][l];
				if(curCost < minCost)
				{
					minCost = curCost;
					optimalRoot = r;
				}
			}

			cost[i][l] = minCost;
			root_index[i][l] = optimalRoot;
		}
	}

#ifdef _DEBUG_EN_
	ofstream out_file("DebugInfo.txt");
	PrintDebugInfo(dummyPR, cost, w, root_index, n, out_file);
	out_file.close();
#endif // #ifdef _DEBUG_EN_

	generate(root_index, n);

	if(n > 0)
	{
		for(int i = 0; i < n; ++i)
		{
			delete[] cost[i];
			delete[] w[i];
			delete[] root_index[i];
		}
		delete[] cost;
		delete[] w;
		delete[] root_index;
	}

	return true;
}


#endif // #ifndef _OPTIMAL_BINARY_SEARCH_TREE_H_
