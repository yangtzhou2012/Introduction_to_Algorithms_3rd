#ifndef _HOARE_QUICK_SORT_H_
#define _HOARE_QUICK_SORT_H_

template <typename T>
inline void swap(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
int hoare_partition(T data[], int left, int right)
{
	T pivot = data[left];

	while (true)
	{
		while (data[left] < pivot) left++;
		while (pivot < data[right]) right--;
		if (left < right) swap(data[left++], data[right--]);
		else return right;
	}
}

template <typename T>
void hoare_quick_sort(T data[], int left, int right)
{
	if (left < right)
	{
		int mid = hoare_partition(data, left, right);
		hoare_quick_sort(data, left, mid);
		hoare_quick_sort(data, mid+1, right);
	}
}

template <typename T>
void hoare_quick_sort(T data[], int n)
{
	if (data != NULL)
		hoare_quick_sort(data, 0, n-1);
}

#endif // #ifndef _HOARE_QUICK_SORT_H_
