#include "StringSplitAlgo.h"
#include <algorithm>

using namespace std;

StringSplit::StringSplit() : strLength(0), splitPositionNumber(0), splitPosition(NULL)
{

}

StringSplit::~StringSplit()
{
	Clear();
}

bool StringSplit::SetLengthPosition(int strLen, int splitPosNum, int splitPos[])
{
	if (strLen > 1 && splitPosNum > 0 && splitPosNum < strLen && splitPos != NULL)
	{
		int minPos = splitPos[0];
		int maxPos = splitPos[0];

		for (int i = 1; i < splitPosNum; ++i)
		{
			if (splitPos[i] < minPos) minPos = splitPos[i];
			else if (splitPos[i] > maxPos) maxPos = splitPos[i];
		}

		if (minPos >= 0 && maxPos < strLen-1)
		{
			Clear();
			strLength = strLen;
			splitPositionNumber = splitPosNum;
			splitPosition = new int[splitPosNum];
			memcpy(splitPosition, splitPos, splitPosNum*sizeof(int));
			sort(splitPosition, splitPosition+splitPosNum);
		}
	}

	return false;
}

void StringSplit::Clear()
{
	strLength = 0;
	splitPositionNumber = 0;
	if (splitPosition != NULL) delete[] splitPosition;
	splitOrder.clear();
}

bool StringSplit::GenerateSplitOrder()
{
	if (strLength > 1 && splitPositionNumber > 0 && splitPositionNumber < strLength && splitPosition != NULL)
	{
		int **cost = new int*[splitPositionNumber+1];
		int **sp = new int*[splitPositionNumber+1];

		for (int j = 0; j <= splitPositionNumber; ++j)
		{
			cost[j] = new int[j+1];
			sp[j] = new int[j+1];
		}

		for (int i = 0; i <= splitPositionNumber; ++i)
			cost[i][i] = 0;

		for (int l = 1; l <= splitPositionNumber; ++l)
		{
			for (int i = 0; i <= splitPositionNumber-l; ++i)
			{
				int j = i + l;
				int subStrRight = j < splitPositionNumber ? splitPosition[j]+1 : strLength;
				int subStrLen = i > 0 ? subStrRight-(splitPosition[i-1]+1) : subStrRight;

				cost[j][i] = cost[i][i] + cost[j][i+1];
				sp[j][i] = i;

				for (int k = i+1; k <= j-1; ++k)
				{
					int c = cost[k][i] + cost[j][k+1];
					if (c < cost[j][i])
					{
						cost[j][i] = c;
						sp[j][i] = k;
					}
				}

				cost[j][i] += subStrLen;
			}
		}

		splitOrder.clear();
		SaveSplitOrder(splitPosition, sp, 0, splitPositionNumber, splitOrder);

		for (int j = 0; j <= splitPositionNumber; ++j)
		{
			delete[] cost[j];
			delete[] sp[j];
		}

		delete[] cost;
		delete[] sp;
	}

	return false;
}

void StringSplit::SaveSplitOrder(const int *splitPos, int **sp, int i, int j, vector<int> &spOrder)
{
	if (j > i)
	{
		spOrder.push_back(splitPos[sp[j][i]]);
		SaveSplitOrder(splitPos, sp, i, sp[j][i], spOrder);
		SaveSplitOrder(splitPos, sp, sp[j][i]+1, j, spOrder);
	}
}
