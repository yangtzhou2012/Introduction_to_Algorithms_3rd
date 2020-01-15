#ifndef _BUCKET_SORT_H_
#define _BUCKET_SORT_H_

#define _BUCKET_SORT_DEBUG_INFO_

#include "LinkedList.h"
#ifdef _BUCKET_SORT_DEBUG_INFO_
#include <iostream>
using namespace std;
#endif

#ifdef _BUCKET_SORT_DEBUG_INFO_
template <typename T>
void bucket_sort_debug_output_list(ostream &os, const LinkedList<T> &list)
{
	const LinkedListNode<T> *h = list.get_head();

	while (h != NULL)
	{
		os << h->element << " ";
		h = h->next;
	}

	os << "\n";
}
#endif

template <typename T>
void find_min_max(T data[], int n, T &min, T &max)
{
	if (data[0] < data[1])
	{
		min = data[0];
		max = data[1];
	}
	else
	{
		min = data[1];
		max = data[0];
	}

	int i;

	for (i = 2; i < n-1; i += 2)
	{
		if (data[i] < data[i+1])
		{
			if (data[i] < min) min = data[i];
			if (max < data[i+1]) max = data[i+1];
		}
		else
		{
			if (data[i+1] < min) min = data[i+1];
			if (max < data[i]) max = data[i];
		}
	}

	if (i == n-1)
	{
		if (data[i] < min) min = data[i];
		else if (max < data[i]) max = data[i];
	}
}

template <typename T>
void bucket_sort(T data[], int n, int bucket_cnt, T min, T max)
{
	if (min == max)
		return;

	LinkedList<T> *bucket = new LinkedList<T>[bucket_cnt];

	for (int i = 0; i < n; ++i)
	{
		int j = static_cast<int>((data[i]-min) * bucket_cnt / (max-min));
		if (j >= bucket_cnt)
			j = bucket_cnt - 1;
		bucket[j].push_back(data[i]);
	}

#ifdef _BUCKET_SORT_DEBUG_INFO_
	for (int j = 0; j < bucket_cnt; ++j)
	{
		cout << "bucket " << j << " before sort: ";
		bucket_sort_debug_output_list(cout, bucket[j]);
	}

	cout << "\n";
#endif

	int i = 0;

	for (int j = 0; j < bucket_cnt; ++j)
	{
		bucket[j].insertion_sort();

		const LinkedListNode<T> *h = bucket[j].get_head();
		while (h != NULL)
		{
			data[i++] = h->element;
			h = h->next;
		}

#ifdef _BUCKET_SORT_DEBUG_INFO_
		cout << "bucket " << j << " after sort: ";
		bucket_sort_debug_output_list(cout, bucket[j]);
#endif
	}

#ifdef _BUCKET_SORT_DEBUG_INFO_
	cout << "\n";
#endif

	delete[] bucket;
}

template <typename T>
void bucket_sort(T data[], int n, int bucket_cnt)
{
	if (data == NULL || n < 2 || bucket_cnt < 1)
		return;

	T min, max;
	find_min_max(data, n, min, max);

	bucket_sort(data, n, bucket_cnt, min, max);
}

#endif // #ifndef _BUCKET_SORT_H_
