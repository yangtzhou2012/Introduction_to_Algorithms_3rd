#ifndef _SORT_H_
#define _SORT_H_


template <typename T>
inline void exchange(T &x, T &y)
{
	T tmp = x;
	x = y;
	y = tmp;
}


/***** Insert Sort *****/
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


/***** Bubble Sort *****/
template <typename T>
void bubble_sort(T data[], int n)
{
	if(data != NULL)
	{
		for(int i = 0; i < n-1; ++i)
		{
			for(int j = n-1; j > i; --j)
			{
				if(data[j] < data[j-1])
				{
					//Swap(data[j], data[j-1]);
					T tmp = data[j];
					data[j] = data[j-1];
					data[j-1] = tmp;
				}
			}
		}
	}
}


/***** Merge Sort *****/
template <typename T>
void merge(T data[], T temp[], int left, int mid, int right)
{
	for(int i = left; i <= right; ++i)
		temp[i] = data[i];

	int i = left;
	int j = mid + 1;
	//int k = left;

	while(i <= mid)
	{
		if(j <= right)
		{
			if(temp[i] <= temp[j])
				data[left++] = temp[i++];
			else
				data[left++] = temp[j++];
		}
		else
		{
			data[left++] = temp[i++];
		}
	}

	while(j <= right)
		data[left++] = temp[j++];
}

template <typename T>
void merge_sort(T data[], T temp[], int left, int right)
{
	if(left < right)
	{
		int mid = ((left+right)>>1);
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


/***** Heap Sort *****/
inline int LEFT(int i)
{
	return (i<<1) + 1;
}

template<typename T>
void max_heapify(T data[], int n, int i)
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
void heap_sort(T data[], int n)
{
	if (data != NULL)
	{
		for (int i = n/2-1; i >= 0; --i)
			max_heapify(data, n, i);

		for (int i = n-1; i > 0; --i)
		{
			//Swap(data[0], data[i]);
			T tmp = data[0];
			data[0] = data[i];
			data[i] = tmp;
			max_heapify(data, i, 0);
		}
	}
}


/***** Quick Sort *****/
template <typename T>
int partition(T data[], int left, int right)
{
	int mid = ((left+right)>>1);

	if(data[right] < data[left])
		exchange(data[right], data[left]);
	if(data[mid] < data[left])
		exchange(data[mid], data[left]);
	if(data[mid] < data[right])
		exchange(data[mid], data[right]);

	for (int i = left; i < right; ++i)
	{
		if (data[i] <= data[right])
		{
			//Swap(data[left], data[i]);
			T tmp = data[left];
			data[left] = data[i];
			data[i] = tmp;
			left++;
		}
	}

	//Swap(data[left], data[right]);
	T tmp = data[left];
	data[left] = data[right];
	data[right] = tmp;

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


/***** Hoare Quick Sort *****/ 
template <typename T>
int hoare_partition(T data[], int left, int right)
{
	int mid = ((left+right)>>1);

	if(data[right] < data[mid])
		exchange(data[right], data[mid]);
	if(data[left] < data[mid])
		exchange(data[left], data[mid]);
	if(data[right] < data[left])
		exchange(data[left], data[right]);

         T pivot = data[left];
 
         while (true)
         {
                   while (data[left] < pivot) left++;
                   while (pivot < data[right]) right--;
                   if (left < right) exchange(data[left++], data[right--]);
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


/***** Improved Quick Sort *****/ 
#define QUICK_INSERT_SWITCH	50

template <typename T>
void improved_quick_sort(T data[], int left, int right)
{
	int len = right - left + 1;

	if(len > QUICK_INSERT_SWITCH)
	{
		int mid = partition(data, left, right);
		improved_quick_sort(data, left, mid-1);
		improved_quick_sort(data, mid+1, right);
	}
	else if(len > 1)
	{
		//insert_sort(data+left, len);
		for(int i = left+1; i <= right; ++i)
		{
			T key = data[i];

			int j;
			for(j = i-1; j >= left && data[j] > key; --j)
				data[j+1] = data[j];

			data[j+1] = key;
		}
	}
}

template <typename T>
void improved_quick_sort(T data[], int n)
{
	if (data != NULL)
		improved_quick_sort(data, 0, n-1);
}


#endif // #ifndef _SORT_H_

