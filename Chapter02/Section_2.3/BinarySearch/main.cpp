#include <iostream>
#include "BinarySearch.h"

using namespace std;

int main()
{
	int a1[] = {1, 3, 5, 7, 9, 11};
	cout << binary_search(a1, sizeof(a1)/sizeof(int), 3) << "\n";
}
