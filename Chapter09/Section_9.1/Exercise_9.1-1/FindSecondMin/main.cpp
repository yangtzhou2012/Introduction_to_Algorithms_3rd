#include <iostream>
#include "FindSecondMin.h"
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
static void exchange(T &x, T &y)
{
	T t = x;
	x = y;
	y = t;
}

static int log2_ceil(unsigned int x)
{
	if (x == 0)
		return -1;

	int temp = x;
	int res = 0;
	
	while (temp > 1)
	{
		temp >>= 1;
		res++;
	}

	if ((x & ((1<<res) - 1)) != 0)
		res++;

	return res;
}

template <typename T>
int FindSecondMinSimple(const T data[], int n)
{
	if (data == NULL || n < 2)
		return -1;

	int minId = 0;

	for (int i = 1; i < n; ++i)
	{
		if (data[i] < data[minId])
			minId = i;
	}

	int secondMinId = (minId != 0 ? 0 : 1);

	for (int i = 0; i < n; ++i)
	{
		if (i != minId)
		{
			if (data[i] < data[secondMinId])
				secondMinId = i;
		}
	}

	return secondMinId;
}

int main()
{
	int a[] ={ 3, 6, 1, -1, 0, 100, 58 };
	//int aSecondMinId = FindSecondMinSimple(a, sizeof(a)/sizeof(int));
	//cout << "aSecondMinId = " << aSecondMinId << "\n\n";

	int b[] ={ 1, 2 };
	//int bSecondMinId = FindSecondMinSimple(b, sizeof(b)/sizeof(int));
	//cout << "bSecondMinId = " << bSecondMinId << "\n\n";

	int c[] ={ 14874,   27911,   10575,   20986,   26980,   12565,   10659,   9415,    18917,   2075 };
	//int cSecondMinId = FindSecondMin(c, sizeof(c)/sizeof(int));
	//cout << "cSecondMinId = " << cSecondMinId << "\n\n";

	cout << "start randomized test\n\n";
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < 10000; ++i)
	{
		cout << "randomized test " << i << ":\t";

		int n = rand();

		if (n < 2)
			n = 2;
		else if (n > 10000)
			n = 10000;

		cout << "n = " << n << "\n";

		int *data = new int[n];

		for (int j = 0; j < n; ++j)
			data[j] = j;

		for (int j = n - 1; j >= 0; --j)
			exchange(data[j], data[rand()%(j+1)]);

#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
		int compareTimes = 0;
#endif
		int secondMinId1 = FindSecondMinSimple(data, n);
		int secondMinId2 = FindSecondMin(data, n
#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
										 , compareTimes);
#endif

		cout << "secondMinId1 = " << secondMinId1 << "\n";
		cout << "secondMinId2 = " << secondMinId2 << "\tcompareTimes = " << compareTimes;
#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
		cout << "\tmaxCmpTimes = " << n - 2 + log2_ceil(n) << "\n";
#else
		cout << "\n";
#endif

#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
		if (compareTimes > n - 2 + log2_ceil(n))
		{
			cout << "result: comparation times fail\n\n";
			break;
		}
#endif

		if (secondMinId1 != secondMinId2)
		{
			cout << "result: fail\n\n";
			break;
		}
		else
		{
			cout << "result: success\n\n";
		}

		delete[] data;
	}

	return 0;
}
