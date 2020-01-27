#ifndef _COUNTING_SORT_H_
#define _COUNTING_SORT_H_

template <typename T>
static void exchange(T &x, T &y)
{
	T t = x;
	x = y;
	y = t;
}

template <typename T>
void counting_sort_in_place(T src[], int n, int min, int max)
{
	int range = max - min + 1;
	int *count = new int[range];

	for (int i = 0; i < range; ++i)
		count[i] = 0;

	for (int i = 0; i < n; ++i)
		count[src[i]-min]++;

	for (int i = 1; i < range; ++i)
		count[i] += count[i-1];

	for (int i = n-1; i >= 0; --i) {
		int p = count[src[i]-min] - 1;		
		while (p > i)
		{
			count[src[i]-min]--;
			exchange(src[i], src[p]);
			p = count[src[i]-min] - 1;
		}
	}

	delete[] count;
}

template <typename T>
void counting_sort_in_place(T data[], int n)
{
	if (data == NULL || n <= 1)
		return;

	int i;
	T min, max;
	T *temp = new T[n];

	min = max = data[0];

	for (i = 1; i < n-1; i += 2)
	{
		if (data[i] <= data[i+1]) {
			if (data[i] < min) min = data[i];
			if (data[i+1] > max) max = data[i+1];
		}
		else {
			if (data[i+1] < min) min = data[i+1];
			if (data[i] > max) max = data[i];
		}
	}

	if (i < n) {
		if (data[i] < min) min = data[i];
		else if (data[i] > max) max = data[i];
	}

	counting_sort_in_place(data, n, min, max);

	delete[] temp;
}

#endif // #ifndef _COUNTING_SORT_H_
