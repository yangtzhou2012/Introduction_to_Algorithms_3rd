#ifndef _BINARY_SEARCH_H_
#define _BINARY_SEARCH_H_

template <typename T>
int binary_search(T data[], int n, const T &v)
{
	if(data != NULL && n > 0)
	{
		int left = 0;
		int right = n-1;

		while(left <= right)
		{
			int mid = (left+right)/2;

			if(v < data[mid])
				right = mid - 1;
			else if(v > data[mid])
				left = mid + 1;
			else
				return mid;
		}
	}

	return -1;
}

#endif // #ifndef _BINARY_SEARCH_H_
