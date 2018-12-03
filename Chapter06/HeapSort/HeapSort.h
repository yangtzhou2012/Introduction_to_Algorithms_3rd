#ifndef _HEAP_SORT_H_
#define _HEAP_SORT_H_

inline int LEFT(int i)
{
	return (i<<1) + 1;
}

template<typename T>
void MaxHeapify(T data[], int n, int i)
{
	T tmp = data[i];
	int left = LEFT(i);

	while (left < n)
	{
		int right = left + 1;
		int maxChild = (right < n && data[left] < data[right]) ? right : left;

		if (tmp < data[maxChild])
		{
			data[i] = data[maxChild];
			i = maxChild;
			left = LEFT(i);
		}
		else
			break;
	}

	data[i] = tmp;
}

template<typename T>
inline void exchange(T& x, T& y)
{
	T t = x;
	x = y;
	y = t;
}

template<typename T>
void HeapSort(T data[], int n)
{
	if (data != NULL)
	{
		for (int i = n/2-1; i >= 0; --i)
			MaxHeapify(data, n, i);

		for (int i = n-1; i > 0; --i)
		{
			exchange(data[0], data[i]);
			MaxHeapify(data, i, 0);
		}
	}
}

#endif // #ifndef _HEAP_SORT_H_

