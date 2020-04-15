#ifndef _FIND_MIN_MAX_
#define _FIND_MIN_MAX_

template <typename T>
void FindMinMax(T data[], int n, int &minId, int &maxId)
{
	if (data == NULL || n < 1)
	{
		minId = -1;
		maxId = -1;
	}
	else
	{
		int i = 0;

		if ((n & 1) == 1)
		{
			minId = 0;
			maxId = 0;
			i = 1;
		}
		else
		{
			if (data[0] <= data[1])
			{
				minId = 0;
				maxId = 1;
			}
			else
			{
				minId = 1;
				maxId = 0;
			}

			i = 2;
		}

		while (i < n)
		{
			if (data[i] <= data[i+1])
			{
				if (data[i] < data[minId])
					minId = i;
				if (data[i+1] > data[maxId])
					maxId = i+1;
			}
			else
			{
				if (data[i+1] < data[minId])
					minId = i+1;
				if (data[i] > data[maxId])
					maxId = i;
			}

			i += 2;
		}
	}
}

#endif // #ifndef _FIND_MIN_MAX_
