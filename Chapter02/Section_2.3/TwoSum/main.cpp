#include <iostream>
#include "MergeSort.h"

using namespace std;

bool TwoSum(int data[], int n, int sum)
{
	if(data != NULL || n > 1)
	{
		merge_sort(data, n);

		int i = 0;
		int j = n-1;

		while(i < j)
		{
			if(data[i] + data[j] < sum)
			{
				i++;
			}
			else if(data[i] + data[j] > sum)
			{
				j--;
			}
			else
			{
				cout << data[i] << " + " << data[j] << " = " << sum << "\n";
				return true;
			}
		}
	}

	cout << "No 2 elements whose sum is equle to " << sum << "\n";
	return false;
}

int main()
{
	int a1[] = {5, 4, 2, 1, 5, 7, 4, 5};
	TwoSum(a1, sizeof(a1)/sizeof(int), 10);

	int a2[] = {2, 1};
	TwoSum(a2, sizeof(a2)/sizeof(int), 3);
}
