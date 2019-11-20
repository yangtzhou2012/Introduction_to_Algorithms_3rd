#ifndef _COUNTING_SORT_H_
#define _COUNTING_SORT_H_

template <typename T>
void counting_sort(T src[], T dst[], int n, int min, int max)
{
	int range = max - min + 1;
	T *count = new T[range];

	for (int i = 0; i < range; ++i)
		count[i] = 0;

	for (int i = 0; i < n; ++i)
		count[src[i]-min]++;

	for (int i = 1; i < range; ++i)
		count[i] += count[i-1];

	for (int i = n-1; i >= 0; --i) {
		dst[count[src[i]-min]-1] = src[i];
		count[src[i]-min]--;
	}

	delete[] count;
}

template <typename T>
void counting_sort(T data[], int n)
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

	for (i = 0; i < n; ++i)
		temp[i] = data[i];

	counting_sort(temp, data, n, min, max);

	delete[] temp;
}

#endif // #ifndef _COUNTING_SORT_H_
