#include <iostream>
#include "HoareQuickSort.h"

using namespace std;

int main()
{
	int a[] = { 2, 8, 7, 1, 3, 5, 6, 4 };
	int d[] = { 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11 };

	hoare_quick_sort(a, sizeof(a)/sizeof(int));
	for (int i = 0; i < sizeof(a)/sizeof(int); ++i)
		cout << a[i] << " ";
	cout << "\n";

	hoare_quick_sort(d, sizeof(d)/sizeof(int));
	for (int i = 0; i < sizeof(d)/sizeof(int); ++i)
		cout << d[i] << " ";
	cout << "\n";

	return 0;
}
