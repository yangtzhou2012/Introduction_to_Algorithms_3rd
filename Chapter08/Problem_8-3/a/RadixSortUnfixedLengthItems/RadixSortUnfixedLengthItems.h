#ifndef _RADIX_SORT_UNFIXED_LENGTH_ITEMS_H_
#define _RADIX_SORT_UNFIXED_LENGTH_ITEMS_H_

#define _DEBUG_INFO_EN_

#ifdef _DEBUG_INFO_EN_
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
void counting_sort_by_significant(T src[], int significant[], int n, int sigMax, int sigCount[])
{
	for (int i = 0; i <= sigMax; ++i)
		sigCount[i] = 0;

	for (int i = 0; i < n; ++i)
		sigCount[significant[i]]++;

	for (int i = 1; i <= sigMax; ++i)
		sigCount[i] += sigCount[i-1];

	int *sigCountTemp = new int[sigMax+1];

	for (int i = 0; i <= sigMax; ++i)
		sigCountTemp[i] = sigCount[i];

	T *dst = new T[n];

	for (int i = n-1; i >= 0; --i) {
		dst[sigCountTemp[significant[i]]-1] = src[i];
		sigCountTemp[significant[i]]--;
	}

	for (int i = 0; i < n; ++i)
		src[i] = dst[i];

	delete[] sigCountTemp;
	delete[] dst;
}

template <typename T>
void radix_counting_sort(T src[], T dst[], int n, int count[], int radix, int mask, int shift)
{
	if (n > 1) {
		memset(count, 0, radix*sizeof(int));

		for (int i = 0; i < n; ++i)
			count[(src[i]>>shift)&mask]++;

		for (int i = 1; i < radix; ++i)
			count[i] += count[i-1];

		for (int i = n-1; i >= 0; --i) {
			T digit = (src[i]>>shift) & mask;
			dst[count[digit]-1] = src[i];
			count[digit]--;
		}
	}
	else if (n == 1) {
		*dst = *src;
	}
}

template <typename T>
bool radix_sort_unfixed_length_items(T data[], int n, int radix)
{
	if (data == NULL || n <= 1 || radix < 2)
		return false;

	// determine whether radix is power of 2
	// we only process the case that radix is power of 2
	int mask = radix - 1;
	if ((radix & mask) != 0)
		return false;

	int step = 0;
	while ((mask>>step) != 0)
		step++;

	int *significant = new int[n];
	int sigMax = 0;

	for (int i = 0; i < n; ++i) {
		significant[i] = 0;
		T t = data[i];

		while (t != 0) {
			significant[i]++;
			t >>= step;
		}

		if (sigMax < significant[i])
			sigMax = significant[i];
	}

	int *sigCount = new int[sigMax+1];

	counting_sort_by_significant(data, significant, n, sigMax, sigCount);

#ifdef _DEBUG_INFO_EN_
	cout << "sorted by significant: ";
	for (int i = 0; i < n; ++i)
		cout << "0x" << hex << data[i] << "\t";
	cout << "\n";

	cout << "significant cout: ";
	for (int i = 0; i <= sigMax; ++i)
		cout << dec << sigCount[i] << "\t";
	cout << "\n";
#endif

	int *count = new int[radix];
	T *temp = new T[n];

	for (int i = 1; i <= sigMax; ++i) {
		T *src = data + sigCount[i-1];
		T *dst = temp + sigCount[i-1];
		int shift = 0;

		for (int j = 0; j < i; ++j) {
			radix_counting_sort(src, dst, sigCount[i]-sigCount[i-1], count, radix, mask, shift);
			exchange(src, dst);
			shift += step;
		}

		if (src == temp + sigCount[i-1]) {
			for (int j = 0; j < sigCount[i]-sigCount[i-1]; ++j)
				dst[j] = src[j];
		}
	}

	delete[] significant;
	delete[] sigCount;
	delete[] count;
	delete[] temp;
	return true;
}

#endif // #ifndef _RADIX_SORT_UNFIXED_LENGTH_ITEMS_H_
