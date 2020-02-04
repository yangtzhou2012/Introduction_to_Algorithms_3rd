#include <cstdio>
#include "SortString.h"

static void sort_string(const char *data[], const char *temp[], int index[], int count[], int start, int end, int round)
{
	if (start >= end)
		return;

	for (int i = 0; i < 27; ++i)
		count[i] = 0;

	for (int i = start; i <= end; ++i)
	{
		temp[i] = data[i];
		int t;

		if (temp[i][round] == '\0') t = 0;
		else if (temp[i][round] >= 'a' && temp[i][round] <= 'z') t = temp[i][round]-'a'+1;
		else t = t = temp[i][round]-'A'+1;

		index[i] = t;
		count[t]++;
	}

	for (int i = 1; i < 27; ++i)
		count[i] += count[i-1];

	int *countTemp = new int[27];

	for (int i = 0; i < 27; ++i)
		countTemp[i] = count[i];

	for (int i = end; i >= start; --i)
	{
		data[count[index[i]] + start - 1] = temp[i];
		count[index[i]]--;
	}

	for (int i = 1; i < 27; ++i)
		sort_string(data, temp, index, count, start + countTemp[i-1],
					start + countTemp[i] - 1, round + 1);

	delete[] countTemp;
}

bool sort_string(const char *data[], int n)
{
	if (data == NULL || n <= 1)
		return false;

	const char **temp = new const char*[n];
	int *count = new int[27];
	int *index = new int[n];

	sort_string(data, temp, index, count, 0, n-1, 0);

	delete[] temp;
	delete[] count;
	delete[] index;

	return true;
}
