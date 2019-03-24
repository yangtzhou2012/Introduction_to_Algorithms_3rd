#ifndef _TAIL_RECURSIVE_QUICKSORT_H_
#define _TAIL_RECURSIVE_QUICKSORT_H_

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
void tail_recursive_quick_sort(T data[], int left, int right)
{
	while (left < right)
	{
		int mid = partition(data, left, right);

		if(mid-left <= right-mid)
		{
			tail_recursive_quick_sort(data, left, mid-1);
			left = mid + 1;
		}
		else
		{
			tail_recursive_quick_sort(data, mid+1, right);
			right = mid - 1;
		}
	}
}

template <typename T>
void tail_recursive_quick_sort(T data[], int n)
{
	if (data != NULL)
		tail_recursive_quick_sort(data, 0, n-1);
}

#endif // #ifndef _TAIL_RECURSIVE_QUICKSORT_H_
