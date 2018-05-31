#include <iostream>

using namespace std;

// rod_length: [ 1   2   3   4   5   6   7   8   9  10]
// rod_price:  [ 1   5   8   9  10  17  17  20  24  30]
const int priceTable[10] = {1, 3, 8, 9, 10, 17, 17, 20, 24, 30};

void RodCut(const int price[], int priceTableSize, int rodLen)
{
	if(price == NULL || priceTableSize <= 0 || rodLen <= 0)
		cout << "Invalidate parameter!\n";

	int *profit = new int[rodLen];
	int *cutPos = new int[rodLen];

	for(int i = 0; i < rodLen; ++i)
	{
		int maxProfit = INT_MIN;
		int optimalCutPos;

		for(int j = 0; j <= i && j < priceTableSize; ++j)
		{
			int curProfit;
			if(j == i) curProfit = price[j];
			else curProfit = price[j] + profit[i-j-1];

			if(maxProfit < curProfit)
			{
				maxProfit = curProfit;
				optimalCutPos = j;
			}
		}

		profit[i] = maxProfit;
		cutPos[i] = optimalCutPos+1;
	}

	cout << "Cutting Strategy: ";
	for(int i = rodLen-1; i >= 0; i -= cutPos[i])
		cout << cutPos[i] << " ";
	cout << "\n";

	cout << "Total profit: " << profit[rodLen-1] << "\n";

	delete[] profit;
	delete[] cutPos;
}

int main()
{
	while(1)
	{
		int rodLen;
		cout << "Please input a rod length: ";
		cin >> rodLen;
		RodCut(priceTable, sizeof(priceTable)/sizeof(int), rodLen);
		cout << "\n";
	}

	return 0;
}
