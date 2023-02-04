#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

template <typename T>
bool FindMinMaxSimple(T a[], int n, T &min, T &max)
{
	if (a == NULL || n < 1)
	{
		cout << "input invalid\n";
		return false;
	}

	min = a[0];
	for (int i = 1; i < n; i++)
	{
		if (a[i] < min)
			min = a[i];
	}

	max = a[0];
	for (int i = 1; i < n; i++)
	{
		if (max < a[i])
			max = a[i];
	}

	return true;
}

#define ALIGN_UP(a, b)	(((a + b - 1) / b) * b)

template <typename T>
bool FindMinMaxRandom(T a[], int n, T& min, T& max)
{
	if (a == NULL || n < 1)
	{
		cout << "input invalid\n";
		return false;
	}

	bool ret = true;

	if (n <= 1)
	{
		min = a[0];
		max = a[0];
	}
	else
	{
		int undeleted_elems = 2 * n;
		unsigned char* min_table = new unsigned char[n];
		unsigned char* max_table = new unsigned char[n];
		int compare_times = 0;

		for (int i = 0; i < n; i++)
		{
			min_table[i] = 1U;
			max_table[i] = 1U;
		}
/*
		cout << "max_table: ";
		for (int i = 0; i < n; i++)
			cout << (unsigned int)max_table[i] << " ";
		cout << "\n";

		cout << "min_table: ";
		for (int i = 0; i < n; i++)
			cout << (unsigned int)min_table[i] << " ";
		cout << "\n\n";
*/

		while (undeleted_elems > 2) {
			// assure that i < j
			int i = rand() % (n - 1);
			int j = rand() % (n - i - 1) + i + 1;

			if (a[i] < a[j])
			{
				undeleted_elems -= (min_table[j] & 1U);
				undeleted_elems -= (max_table[i] & 1U);
				min_table[j] = 0;
				max_table[i] = 0;
			}
			else
			{
				undeleted_elems -= (min_table[i] & 1U);
				undeleted_elems -= (max_table[j] & 1U);
				min_table[i] = 0;
				max_table[j] = 0;
			}

			compare_times++;
/*
			cout << "i = " << i << ",  j = " << j << ",  undeleted_elems = " << undeleted_elems << "\n";

			cout << "max_table: ";
			for (int k = 0; k < n; k++)
				cout << (unsigned int)max_table[k] << " ";
			cout << "\n";

			cout << "min_table: ";
			for (int k = 0; k < n; k++)
				cout << (unsigned int)min_table[k] << " ";
			cout << "\n\n";
*/
		}

		cout << "compare times: " << compare_times << "\n\n";

		int remain_min_elems = 0;
		int min_elem_idx = 0;
		int remain_max_elems = 0;
		int max_elem_idx = 0;

		for (int i = 0; i < n; i++)
		{
			if (min_table[i])
			{
				remain_min_elems++;
				min_elem_idx = i;
			}

			if (max_table[i])
			{
				remain_max_elems++;
				max_elem_idx = i;
			}
		}

		if (remain_min_elems != 1 || remain_max_elems != 1)
		{
			cout << "remained min elements's count[" << remain_min_elems << "] and remained max elements's count[" << remain_max_elems << "] ard invalide\n";
			ret = false;
		}
		else
		{
			min = a[min_elem_idx];
			max = a[max_elem_idx];
		}

		delete[] min_table;
		delete[] max_table;
	}

	return ret;
}

#define MAX_ARRAY_LEN				1024
#define MAX_RANGE					(MAX_ARRAY_LEN * 8)
#define TOTAL_TEST_CYCLE_CNT		1024
#define SINGLE_ARRAY_TEST_CNT		32

int main()
{
	int* a = new int[MAX_ARRAY_LEN];
	int min1 = 0;
	int max1 = 0;
	int min2 = 0;
	int max2 = 0;
	int ret = 0;

	srand(static_cast<unsigned int>(time(0)));

	for (int i = 0; i < TOTAL_TEST_CYCLE_CNT; i++)
	{
		int array_len = rand() % MAX_ARRAY_LEN + 1;
		int range = rand() % MAX_RANGE + 1;

		for (int j = 0; j < array_len; j++)
			a[j] = rand() % range;

		cout << "Array-" << i << ": len[" << array_len << "] range[" << range << "]\n";

		ret = FindMinMaxSimple(a, array_len, min1, max1);
		if (!ret) {
			cout << "Array-" << i << ": find min & max failed by the simple-method\n";
			return -1;
		}

		cout << "Array-" << i << ": min[" << min1 << "] max[" << max1 << "]\n\n";

		for (int j = 0; j < SINGLE_ARRAY_TEST_CNT; j++)
		{
			min2 = max2 = -1;

			ret = FindMinMaxRandom(a, array_len, min2, max2);
			if (!ret) {
				cout << "Array-" << i << " test_cycle-" << j << ": find min & max failed by the random-method\n";
				return -1;
			}

			if (min1 != min2 || max1 != max2)
			{
				cout << "Array-" << i << " test_cycle-" << j << ": find wrong min[" << min2 << "] or max[" << max2 << "]\n";
				return -1;
			}

			cout << "Array-" << i << " test_cycle-" << j << ": min[" << min2 << "] max[" << max2 << "]\n\n";
		}

		cout << "test success!\n\n";
	}

	return 0;
}
