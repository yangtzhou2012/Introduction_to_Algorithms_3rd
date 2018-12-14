#ifndef _QUICK_SORT_H_
#define _QUICK_SORT_H_

template <typename T>
inline void swap(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
int partition(T data[], int left, int right)
{
	for (int i = left; i < right; ++i)
	{
		if (data[i] <= data[right])
		{
			swap(data[left], data[i]);
			left++;
		}
	}

	swap(data[left], data[right]);
	return left;
}

template <typename T>
void quick_sort(T data[], int left, int right)
{
	if (left < right)
	{
		int mid = partition(data, left, right);
		quick_sort(data, left, mid-1);
		quick_sort(data, mid+1, right);
	}
}

template <typename T>
void quick_sort(T data[], int n)
{
	if (data != NULL)
		quick_sort(data, 0, n-1);
}

#endif // #ifndef _QUICK_SORT_H_
