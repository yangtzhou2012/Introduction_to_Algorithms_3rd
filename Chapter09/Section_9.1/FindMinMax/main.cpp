#include <iostream>

#include "FindMinMax.h"

using namespace std;

int main()
{
	int a[] = { 3, 6, 1, -1, 0, 100, 58 };
	int aMinId, aMaxId;
	FindMinMax(a, sizeof(a)/sizeof(int), aMinId, aMaxId);
	cout << "aMinId = " << aMinId << ", aMaxId = " << aMaxId << "\n";

	int b[] ={ 3, 6, 1, -1, 0, 100, 58, -32 };
	int bMinId, bMaxId;
	FindMinMax(b, sizeof(b)/sizeof(int), bMinId, bMaxId);
	cout << "bMinId = " << bMinId << ", bMaxId = " << bMaxId << "\n";

	return 0;
}
