#ifndef _SELECT_SORT_H_
#define _SELECT_SORT_H_

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
void select_sort(T data[], int n)
{
	if(data != NULL && n > 1)
	{
		for(int i = 0; i < n-1; ++i)
		{
			int minIndex = i;

			for(int j = i+1; j < n; ++j)
				if(data[j] < data[minIndex])
					minIndex = j;

			swap(data[i], data[minIndex]);
		}
	}
}

#endif // #ifndef _SELECT_SORT_H_
