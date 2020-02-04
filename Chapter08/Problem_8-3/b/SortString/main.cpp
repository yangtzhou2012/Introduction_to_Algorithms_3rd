#include <iostream>
#include "SortString.h"

using namespace std;

void print_array(const char *data[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << data[i] << "    ";
	cout << "\n";
}

int main()
{
	const char *array1[] ={ "ab", "b", "a" };
	cout << "original array: ";
	print_array(array1, sizeof(array1)/sizeof(char*));
	sort_string(array1, sizeof(array1)/sizeof(char*));
	cout << "sorted array: ";
	print_array(array1, sizeof(array1)/sizeof(char*));

	const char *array2[] ={ "fix", "fox", "box", "I", "at", "fit", "bat", "a" };
	cout << "original array: ";
	print_array(array2, sizeof(array2)/sizeof(char*));
	sort_string(array2, sizeof(array2)/sizeof(char*));
	cout << "sorted array: ";
	print_array(array2, sizeof(array2)/sizeof(char*));

	return 0;
}
