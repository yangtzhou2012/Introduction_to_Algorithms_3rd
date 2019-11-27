#ifndef _RADIX_SORT_H_
#define _RADIX_SORT_H_

//#define _RADIX_SORT_DEBUG_INFO_

#ifdef _RADIX_SORT_DEBUG_INFO_
#include <iostream>
using namespace std;
#endif

template <typename T>
void exchange(T &x, T &y)
{
	T t = x;
	x = y;
	y = t;
}

template <typename T>
bool radix_counting_sort(T src[], T dst[], int n, int count[], int radix, int mask, int shift)
{
	memset(count, 0, radix*sizeof(int));

	bool completed = true;

	for (int i = 0; i < n; ++i) {
		T digit = src[i] >> shift;
		if (digit != 0)
			completed = false;

		count[digit&mask]++;
	}

	if (completed)
		return false;

	for (int i = 1; i < radix; ++i)
		count[i] += count[i-1];

	for (int i = n-1; i >= 0; --i) {
		T digit = (src[i]>>shift) & mask;
		dst[count[digit]-1] = src[i];
		count[digit]--;
	}

	return true;
}

template <typename T>
void radix_sort(T data[], int n, int radix)
{
	if (data == NULL || n <= 1 || radix < 2)
		return;

	// determine whether radix is power of 2
	// we only process the case that radix is power of 2
	int mask = radix - 1;
	if ((radix & mask) != 0)
		return;

	int step = 0;
	while ((mask>>step) != 0)
		step++;

	T *temp = new T[n];
	int *count = new int[radix];

	T *src = data;
	T *dst = temp;
	int shift = 0;

#ifdef _RADIX_SORT_DEBUG_INFO_
	for (int i = 0; i < n; ++i)
		cout << "0x" << hex << (unsigned long)src[i] << " ";
	cout << "\n";
#endif

	while (shift < 8*sizeof(T) && radix_counting_sort(src, dst, n, count, radix, mask, shift)) {
#ifdef _RADIX_SORT_DEBUG_INFO_
		for (int i = 0; i < n; ++i)
			cout << "0x" << hex << (unsigned long)dst[i] << " ";
		cout << "\n";
#endif
		shift += step;
		exchange(src, dst);
	}

	if (src == temp) {
		for (int i = 0; i < n; ++i)
			data[i] = temp[i];
	}

	delete[] temp;
	delete[] count;
}

#endif // #ifndef _RADIX_SORT_H_
