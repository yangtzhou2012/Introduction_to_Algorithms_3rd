#ifndef _INSERT_SORT_H_
#define _INSERT_SORT_H_

template <typename T>
void insert_sort(T data[], int n)
{
	if(data != NULL && n > 1)
	{
		for(int i = 1; i < n; ++i)
		{
			T key = data[i];

			int j;
			for(j = i-1; j >= 0 && data[j] > key; --j)
				data[j+1] = data[j];

			data[j+1] = key;
		}
	}
}

#endif // #ifndef _INSERT_SORT_H_
