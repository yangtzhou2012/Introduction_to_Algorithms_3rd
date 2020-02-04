#include <iostream>
#include "RadixSortUnfixedLengthItems.h"

using namespace std;

template <typename T>
void print_array(T data[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << "0x" << hex << (unsigned long)data[i] << " ";
	cout << "\n";
}

int main()
{
	int array1[] ={ 0x1111, 0x329, 0x57, 0x657, 0x0, 0x8, 0x43, 0x720, 0x0, 0x355 };
	cout << "source array: ";
	print_array(array1, sizeof(array1)/sizeof(int));
	radix_sort_unfixed_length_items(array1, sizeof(array1)/sizeof(int), 16);
	cout << "sorted array: ";
	print_array(array1, sizeof(array1)/sizeof(int));

	return 0;
}
