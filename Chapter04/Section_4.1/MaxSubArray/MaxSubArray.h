#ifndef _MAX_SUB_ARRAY_H_
#define _MAX_SUB_ARRAY_H_

template <typename T>
static void FindMaxCrossSubarray(T data[], int low, int mid, int high,
								 int &maxLow, int &maxHigh, T &maxSum)
{
	T leftSum = data[mid];
	T sum = leftSum;
	maxLow = mid;

	for (int i = mid-1; i >= low; --i)
	{
		sum += data[i];
		if (sum > leftSum)
		{
			leftSum = sum;
			maxLow = i;
		}
	}

	T rightSum = data[mid+1];
	sum = rightSum;
	maxHigh = mid+1;

	for (int i = mid+2; i <= high; ++i)
	{
		sum += data[i];
		if (sum > rightSum)
		{
			rightSum = sum;
			maxHigh = i;
		}
	}

	maxSum = leftSum + rightSum;
}

template <typename T>
static void FindMaxSubarray(T data[], int low, int high,
							int &maxLow, int &maxHigh, T &maxSum)
{
	if (low == high)
	{
		maxLow = low;
		maxHigh = high;
		maxSum = data[low];
	}
	else
	{
		int leftLow, leftHigh, leftSum;
		int rightLow, rightHigh, rightSum;
		int crossLow, crossHigh, crossSum;
		int mid = ((low + high) >> 1);

		FindMaxSubarray(data, low, mid, leftLow, leftHigh, leftSum);
		FindMaxSubarray(data, mid+1, high, rightLow, rightHigh, rightSum);
		FindMaxCrossSubarray(data, low, mid, high, crossLow, crossHigh, crossSum);

		if (leftSum >= rightSum && leftSum >= crossSum)
		{
			maxLow = leftLow;
			maxHigh = leftHigh;
			maxSum = leftSum;
		}
		else if (rightSum >= leftSum && rightSum >= crossSum)
		{
			maxLow = rightLow;
			maxHigh = rightHigh;
			maxSum = rightSum;
		}
		else
		{
			maxLow = crossLow;
			maxHigh = crossHigh;
			maxSum = crossSum;
		}
	}
}

template <typename T>
bool FindMaxSubarray(T data[], int n, int &maxLow, int &maxHigh, T &maxSum)
{
	if (data == NULL || n <= 0)
		return false;

	FindMaxSubarray(data, 0, n-1, maxLow, maxHigh, maxSum);

	return true;
}

#endif // _MAX_SUB_ARRAY_H_
