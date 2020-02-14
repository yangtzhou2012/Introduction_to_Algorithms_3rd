#include <iostream>
#include "MaxSubArray.h"

using namespace std;

int main()
{
	int a1[] = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7};
	int maxLow1, maxHigh1, maxSum1;
	FindMaxSubarray(a1, sizeof(a1)/sizeof(int), maxLow1, maxHigh1, maxSum1);
	cout << "maxLow1 = " << maxLow1 << "\tmaxHigh1 = " << maxHigh1 << "\tmaxSum1 = " << maxSum1 << "\n";

	int a2[] ={ 1, -4, 3, -4 };
	int maxLow2, maxHigh2, maxSum2;
	FindMaxSubarray(a2, sizeof(a2)/sizeof(int), maxLow2, maxHigh2, maxSum2);
	cout << "maxLow2 = " << maxLow2 << "\tmaxHigh2 = " << maxHigh2 << "\tmaxSum2 = " << maxSum2 << "\n";

	int a3[] ={ 1, 2, 7, 1 };
	int maxLow3, maxHigh3, maxSum3;
	FindMaxSubarray(a3, sizeof(a3)/sizeof(int), maxLow3, maxHigh3, maxSum3);
	cout << "maxLow3 = " << maxLow3 << "\tmaxHigh3 = " << maxHigh3 << "\tmaxSum3 = " << maxSum3 << "\n";

	return 0;
}
