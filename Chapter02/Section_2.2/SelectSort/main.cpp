#include <iostream>
#include "SelectSort.h"

using namespace std;

template <typename T>
void PrintArray(T data[], int n)
{
	if(data != NULL)
	{
		for(int i = 0; i < n; ++i)
			cout << data[i] << "\t";
	}
}

int main()
{
	int a1[] = {3, 2};
	select_sort(a1, sizeof(a1)/sizeof(int));
	PrintArray(a1, sizeof(a1)/sizeof(int));
	cout << "\n";

	int a2[] = {5, 4, 3, 2, 1};
	select_sort(a2, sizeof(a2)/sizeof(int));
	PrintArray(a2, sizeof(a2)/sizeof(int));
	cout << "\n";

	int a3[] = {5, 4, 3, 2, 1, 5, 7, 4, 3, 5};
	select_sort(a3, sizeof(a3)/sizeof(int));
	PrintArray(a3, sizeof(a3)/sizeof(int));
	cout << "\n";

	return 0;
}
