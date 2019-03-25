#include <iostream>

using namespace std;

#define _PRINT_INVERSION_

void merge(int data[], int temp[], int left, int mid, int right)
{
	for(int i = left; i <= right; ++i)
		temp[i] = data[i];

	int i = left;
	int j = mid + 1;
	int k = left;

	while(i <= mid)
	{
		if(j <= right)
		{
			if(temp[i] <= temp[j])
				data[k++] = temp[i++];
			else
				data[k++] = temp[j++];
		}
		else
		{
			data[k++] = temp[i++];
		}
	}

	while(j <= right)
		data[k++] = temp[j++];
}

int CrossInversionCount(int data[], int left, int mid, int right)
{
	int i = left;
	int j = mid + 1;
	int count = 0;

	while(i <= mid && j <= right)
	{
		if(data[i] > data[j])
		{
#ifdef _PRINT_INVERSION_
			for(int k = i; k <= mid; ++k)
				cout << "(" << data[k] << ", " << data[j] << ")\n";
#endif // #ifdef _PRINT_INVERSION_

			count += (mid-i+1);
			j++;
		}
		else
		{
			i++;
		}
	}

	return count;
}

int InversionCount(int data[], int temp[], int left, int right)
{
	int count = 0;

	if(left < right)
	{
		int mid = (left+right)/2;
		count += InversionCount(data, temp, left, mid);
		count += InversionCount(data, temp, mid+1, right);
		count += CrossInversionCount(data, left, mid, right);
		merge(data, temp, left, mid, right);
	}

	return count;
}

int InversionCount(int data[], int n)
{
	int count = 0;

	if(data != NULL && n > 1)
	{
		int *temp = new int[n];
		count = InversionCount(data, temp, 0, n-1);
		delete[] temp;
	}

	return count;
}

int main()
{
	int a1[] = {2, 3, 8, 6, 1};
	cout << "Inversion Count: " << InversionCount(a1, sizeof(a1)/sizeof(int)) << "\n";
}
