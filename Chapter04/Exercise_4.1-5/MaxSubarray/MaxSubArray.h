#ifndef _MAX_SUB_ARRAY_H_
#define _MAX_SUB_ARRAY_H_

template <typename T>
bool FindMaxSubarray(T data[], int n, int &maxLow, int &maxHigh, T &maxSum)
{
	if (data == NULL || n <= 0)
		return false;

	T curSum = data[0];
	T curLow = 0;

	maxSum = data[0];
	maxLow = 0;
	maxHigh = 0;

	for (int i = 1; i < n; ++i)
	{
		if (curSum > 0)
		{
			curSum += data[i];
		}
		else
		{
			curSum = data[i];
			curLow = i;
		}

		if (curSum > maxSum)
		{
			maxSum = curSum;
			maxLow = curLow;
			maxHigh = i;
		}
	}

	return true;
}

#endif // _MAX_SUB_ARRAY_H_
