#include <iostream>
#include "FindSecondMin.h"
#include <cstdlib>
#include <ctime>

using namespace std;

#define RANDOMIZED_TEST_EN	0

template <typename T>
static void exchange(T &x, T &y)
{
	T t = x;
	x = y;
	y = t;
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
	int a[] = { 3, 6, 1, -1, 0, 100, 58, 0 };
	int aSecondMinId = FindSecondMin(a, sizeof(a)/sizeof(int));
	cout << "aSecondMinId = " << aSecondMinId << "\n\n";

	int b[] = { 1, 2 };
	int bSecondMinId = FindSecondMin(b, sizeof(b)/sizeof(int));
	cout << "bSecondMinId = " << bSecondMinId << "\n\n";

	int c[] = { 14874,   27911,   10575,   20986,   26980,   12565,   10659,   9415,    18917,   2075 };
	int cSecondMinId = FindSecondMin(c, sizeof(c)/sizeof(int));
	cout << "cSecondMinId = " << cSecondMinId << "\n\n";

#if RANDOMIZED_TEST_EN
	cout << "start randomized test\n\n";
	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < 1000; ++i)
	{
		cout << "randomized test [" << i << "]" << ":\t";

		int n = rand()%10001;
		if (n < 2)
			n = 2;

		cout << "n = " << n << "\n";

		int *data = new int[n];
		for (int j = 0; j < n; ++j)
			data[j] = rand()%10000;

		for (int j = n - 1; j >= 0; --j)
			exchange(data[j], data[rand()%(j+1)]);

		int secondMinId1 = FindSecondMinSimple(data, n);
		int secondMinId2 = FindSecondMin(data, n);

		cout << "\tsecondMinId1 = " << secondMinId1 << "\n";
		cout << "\tsecondMinId2 = " << secondMinId2 << "\n";

		if (data[secondMinId2] != data[secondMinId1])
		{
			cout << "\tresult: fail data[secondMinId2] = " << data[secondMinId2];
			cout << "\tdata[secondMinId1] = " << data[secondMinId1] << "\n\n";
			break;
		}
		else
		{
			cout << "\tresult: success\n\n";
		}

		delete[] data;
	}
#endif

	return 0;
}
