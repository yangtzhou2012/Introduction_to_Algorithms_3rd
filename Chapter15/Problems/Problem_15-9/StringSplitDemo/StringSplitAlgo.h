#ifndef _STRING_SPLIT_ALGO_H_
#define _STRING_SPLIT_ALGO_H_

#include <vector>

using namespace std;

class StringSplit
{
public:
	StringSplit();
	~StringSplit();

	bool SetLengthPosition(int strLen, int splitPosNum, int splitPos[]);
	void Clear();
	bool GenerateSplitOrder();
	const int GetStrLength() const { return strLength; }
	const vector<int>& GetsplitOrder() const { return splitOrder; }

private:
	int strLength;
	int splitPositionNumber;
	int *splitPosition;
	vector<int> splitOrder;

	void SaveSplitOrder(const int *splitPos, int **sp, int i, int j, vector<int> &spOrder);
};

#endif // #ifndef _STRING_SPLIT_ALGO_H_
