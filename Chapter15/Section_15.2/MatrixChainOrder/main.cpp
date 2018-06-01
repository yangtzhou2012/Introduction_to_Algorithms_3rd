#include <iostream>

using namespace std;

void PrintOptimalParens(int **dividePos, int i, int j)
{
	if(i == j)
		cout << " A" << i << " ";
	else
	{
		cout << "(";

		int optimalDividePos = dividePos[i-1][j-i-1];
		PrintOptimalParens(dividePos, i, optimalDividePos);
		PrintOptimalParens(dividePos, optimalDividePos+1, j);

		cout << ")";
	}
}

void MatrixChainOrder(const int matrixDim[], int matrixDimCount)
{
	if(matrixDim == NULL || matrixDimCount < 2)
	{
		cout << "Invalidate parameter!\n";
		return;
	}

	int matrixCount = matrixDimCount-1;

	if(matrixCount == 1)
	{
		cout << "Order: A1\n";
		cout << "Multiply Times: 0\n";
		return;
	}

	// If there are n matrices
	// multiplyTimes[0] -- { m[1,2] m[1,3] m[1,4] ... m[1,n] }
	// multiplyTimes[1] -- { m[2,3] m[2,4] ... m[2,n] }
	// ... ...
	// multiplyTimes[n-1] -- { m[n,n] }
	int **multiplyTimes = new int*[matrixCount-1];
	int **dividePos = new int*[matrixCount-1];
	for(int i = 0; i < matrixCount-1; ++i)
	{
		multiplyTimes[i] = new int[matrixCount-1-i];
		dividePos[i] = new int[matrixCount-1-i];
	}

	for(int chainLen = 2; chainLen <= matrixCount; ++chainLen)
	{
		for(int i = 1; i <= matrixCount-chainLen+1; ++i)
		{
			int j = i+chainLen-1;
			int minMultiplyTimes = INT_MAX;
			int optimalDividePos;

			for(int k = i; k < j; ++k)
			{
				int leftMultiplyTimes, rightMultiplyTimes;

				if(i == k) leftMultiplyTimes = 0;
				else leftMultiplyTimes = multiplyTimes[i-1][k-i-1];

				if(k+1 == j) rightMultiplyTimes = 0;
				else rightMultiplyTimes = multiplyTimes[k][j-k-2];

				int curMultiplyTimes = leftMultiplyTimes + rightMultiplyTimes + matrixDim[i-1]*matrixDim[k]*matrixDim[j];
				if(curMultiplyTimes < minMultiplyTimes)
				{
					minMultiplyTimes = curMultiplyTimes;
					optimalDividePos = k;
				}
			}

			multiplyTimes[i-1][chainLen-2] = minMultiplyTimes;
			dividePos[i-1][chainLen-2] = optimalDividePos;
		}
	}
	
	cout << "Optimal parens: ";
	PrintOptimalParens(dividePos, 1, matrixCount);
	cout << "\n";

	cout << "Total multiply times: " << multiplyTimes[0][matrixCount-2] << "\n";

	for(int i = 0; i < matrixCount-1; ++i)
	{
		delete[] multiplyTimes[i];
		delete[] dividePos[i];
	}
}

int main()
{
	//const int matrixDimTable[7] ={5, 10, 3, 12, 5, 50, 6};
	const int matrixDimTable[] ={30, 35, 15, 5, 10, 20, 25};
	//const int matrixDimTable[] ={2, 3, 4, 4};

	MatrixChainOrder(matrixDimTable, sizeof(matrixDimTable)/sizeof(int));

	return 0;
}
