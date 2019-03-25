#ifndef _MERGE_SORT_H_
#define _MERGE_SORT_H_

template <typename T>
void merge(T data[], T temp[], int left, int mid, int right)
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

template <typename T>
void merge_sort(T data[], T temp[], int left, int right)
{
	if(left < right)
	{
		int mid = (left+right)/2;
		merge_sort(data, temp, left, mid);
		merge_sort(data, temp, mid+1, right);
		merge(data, temp, left, mid, right);
	}
}

template <typename T>
void merge_sort(T data[], int n)
{
	if(data != NULL && n > 1)
	{
		T *temp = new T[n];
		merge_sort(data, temp, 0, n-1);
		delete[] temp;
	}
}

#endif // #ifndef _MERGE_SORT_H_
