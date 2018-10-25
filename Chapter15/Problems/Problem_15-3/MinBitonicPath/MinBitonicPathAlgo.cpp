#include "stdafx.h"
#include "MinBitonicPathAlgo.h"
#include <cmath>


static double distance(CPoint &point1, CPoint &point2)
{
	int dx = point1.x - point2.x;
	int dy = point1.y - point2.y;
	return sqrt(dx*dx + dy*dy);
}

static void GetPointChain(int **left, int i, int j, int* &pointChain)
{
	if(i >= j)
	{
		if (i == 1 && j == 0)
			return;

		*pointChain++ = left[i-1][j];
		GetPointChain(left, left[i-1][j], j, pointChain);
	}
	else
	{
		if (i == 0 || j == 1)
			return;

		GetPointChain(left, i, left[j-1][i], pointChain);
		*pointChain++ = left[j-1][i];
	}
}

double GetMinBitonicPath(CPoint sortedPoint[], int n, int pointChain[])
{
	if (n < 2 || sortedPoint == NULL || pointChain == NULL)
		return 0;

	double **length = new double*[n-1];
	int **left = new int*[n-1];

	for (int j = 0; j < n-1; ++j)
	{
		if (j < n-2)
		{
			length[j] = new double[j+1];
			left[j] = new int[j+1];
		}
		else
		{
			length[j] = new double[n];
			left[j] = new int[n];
		}
	}

	length[0][0] = distance(sortedPoint[0], sortedPoint[1]);
	left[0][0] = 0;

	for (int j = 1; j < n-1; ++j)
	{
		for (int i = 0; i < j; ++i)
		{
			length[j][i] = length[j-1][i] + distance(sortedPoint[j], sortedPoint[j+1]);
			left[j][i] = j;
		}

		length[j][j] = length[j-1][0] + distance(sortedPoint[0], sortedPoint[j+1]);
		left[j][j] = 0;

		for (int k = 1; k < j; ++k)
		{
			double d = length[j-1][k] + distance(sortedPoint[k], sortedPoint[j+1]);
			if (d < length[j][j])
			{
				length[j][j] = d;
				left[j][j] = k;
			}
		}
	}

	length[n-2][n-1] = length[n-2][n-2] + distance(sortedPoint[n-2], sortedPoint[n-1]);
	left[n-2][n-1] = n - 2;

	double res = length[n-2][n-1];
	int *pointChainTemp = pointChain;
	GetPointChain(left, n-1, n-1, pointChainTemp);

	for (int i = 0; i < n-1; ++i)
	{
		delete[] length[i];
		delete[] left[i];
	}

	delete[] length;
	delete[] left;

	return res;
}
