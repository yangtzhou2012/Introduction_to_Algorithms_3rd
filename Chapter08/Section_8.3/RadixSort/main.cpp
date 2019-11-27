#include <iostream>
#include "RadixSort.h"

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
	int array1[] ={ 0x329, 0x457, 0x657, 0x839, 0x436, 0x720, 0x355 };
	radix_sort(array1, sizeof(array1)/sizeof(int), 8);
	print_array(array1, sizeof(array1)/sizeof(int));

	unsigned char array2[] ={ 0x29, 0x57, 0x57, 0x39, 0x36, 0x20, 0x55 };
	radix_sort(array2, sizeof(array2)/sizeof(unsigned char), 2);
	print_array(array2, sizeof(array2)/sizeof(unsigned char));

	int array3[] ={ 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x02 };
	radix_sort(array3, sizeof(array3)/sizeof(int), 16);
	print_array(array3, sizeof(array3)/sizeof(int));

	return 0;
}
