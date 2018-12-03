#include <iostream>
#include "HeapSort.h"

using namespace std;

int main()
{
	int a[] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };

	HeapSort(a, sizeof(a)/sizeof(int));

	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
		cout << a[i] << " ";
	cout << "\n";

	return 0;
}
