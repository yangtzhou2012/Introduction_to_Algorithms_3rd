#include <iostream>
#include "CountingSort.h"

using namespace std;

void print_array(int data[], int n)
{
	for (int i = 0; i < n; ++i)
		cout << data[i] << " ";
	cout << "\n";
}

int main()
{
	int array1[] = { 2, 5, 3, -1, 2, 3, -2, 3, -3, -7 };
	counting_sort(array1, sizeof(array1)/sizeof(int));
	print_array(array1, sizeof(array1)/sizeof(int));

	int array2[] = { 6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2 };
	counting_sort(array2, sizeof(array2)/sizeof(int));
	print_array(array2, sizeof(array2)/sizeof(int));

	int array3[] = { -1, -1, -1, -1 };
	counting_sort(array3, sizeof(array3)/sizeof(int));
	print_array(array3, sizeof(array3)/sizeof(int));

	int array4[] ={ -7, -7 };
	counting_sort(array4, sizeof(array4)/sizeof(int));
	print_array(array4, sizeof(array4)/sizeof(int));

	int array5[] ={ 20, -100 };
	counting_sort(array5, sizeof(array5)/sizeof(int));
	print_array(array5, sizeof(array5)/sizeof(int));

	int array6[] ={ 20 };
	counting_sort(array6, sizeof(array6)/sizeof(int));
	print_array(array6, sizeof(array6)/sizeof(int));

	return 0;
}
