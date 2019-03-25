#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

template <typename T>
inline void swap(T &x, T &y)
{
	if(&x != &y)
	{
		T tmp = x;
		x = y;
		y = tmp;
	}
}

template <typename T>
void bubble_sort(T data[], int n)
{
	if(data != NULL)
	{
		for(int i = 0; i < n-1; ++i)
		{
			for(int j = n-1; j > i; --j)
				if(data[j] < data[j-1])
					swap(data[j], data[j-1]);
		}
	}
}

#endif // #ifndef _BUBBLE_SORT_H_
