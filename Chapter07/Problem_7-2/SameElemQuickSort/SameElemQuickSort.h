#ifndef _SAME_ELEM_QUICK_SORT_H_
#define _SAME_ELEM_QUICK_SORT_H_

struct SplitPosType
{
	SplitPosType(int p1, int p2) : pos1(p1), pos2(p2) {}

	int pos1;
	int pos2;
};

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
SplitPosType same_elem_partition(T data[], int left, int right)
{
	int q = left - 1;
	int t = left - 1;

	for(int k = left; k < right; ++k)
	{
		if(data[k] < data[right])
		{
			q++;
			t++;
			swap(data[q], data[k]);
			swap(data[t], data[k]);
		}
		else if(data[k] == data[right])
		{
			t++;
			swap(data[t], data[k]);
		}
	}

	q++;
	t++;
	swap(data[t], data[right]);

	return SplitPosType(q, t);
}

template <typename T>
void same_elem_quick_sort(T data[], int left, int right)
{
	if (left < right)
	{
		SplitPosType splitPos = same_elem_partition(data, left, right);
		same_elem_quick_sort(data, left, splitPos.pos1-1);
		same_elem_quick_sort(data, splitPos.pos2+1, right);
	}
}

template <typename T>
void same_elem_quick_sort(T data[], int n)
{
	if (data != NULL)
		same_elem_quick_sort(data, 0, n-1);
}

#endif // #ifndef _SAME_ELEM_QUICK_SORT_H_
