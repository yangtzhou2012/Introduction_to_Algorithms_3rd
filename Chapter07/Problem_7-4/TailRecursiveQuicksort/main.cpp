#include <iostream>
#include "TailRecursiveQuicksort.h"

using namespace std;

template <typename T>
void PrintArray(T data[], int n)
{
	if(data != NULL)
		for(int i = 0; i < n; ++i)
			cout << data[i] << "\t";
}

int main()
{
	int a1[] = { 1, 2 };
	tail_recursive_quick_sort(a1, sizeof(a1)/sizeof(int));
	PrintArray(a1, sizeof(a1)/sizeof(int));
	cout << "\n\n";

	int a2[] = { 2, 1 };
	tail_recursive_quick_sort(a2, sizeof(a2)/sizeof(int));
	PrintArray(a2, sizeof(a2)/sizeof(int));
	cout << "\n\n";

	int a3[] = { 2, 2, 2 };
	tail_recursive_quick_sort(a3, sizeof(a3)/sizeof(int));
	PrintArray(a3, sizeof(a3)/sizeof(int));
	cout << "\n\n";

	int a4[] = { 6, 4, 7, 9, 6, 7, 10, 6 };
	tail_recursive_quick_sort(a4, sizeof(a4)/sizeof(int));
	PrintArray(a4, sizeof(a4)/sizeof(int));
	cout << "\n\n";

	int a5[] = { 3, 7, 4, 5, 7 };
	tail_recursive_quick_sort(a5, sizeof(a5)/sizeof(int));
	PrintArray(a5, sizeof(a5)/sizeof(int));
	cout << "\n\n";

	int a6[] = { 2, 6, 4, 3, 5, 2 };
	tail_recursive_quick_sort(a6, sizeof(a6)/sizeof(int));
	PrintArray(a6, sizeof(a6)/sizeof(int));
	cout << "\n\n";

	return 0;
}
