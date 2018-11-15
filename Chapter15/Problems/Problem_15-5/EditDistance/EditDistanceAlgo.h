#ifndef _EDIT_DISTANCE_ALGO_H_
#define _EDIT_DISTANCE_ALGO_H_

#include <string>
#include <vector>

using namespace std;

enum OperationType
{
	OP_NONE = -1,
	OP_COPY = 0,
	OP_REPLACE,
	OP_DELETE,
	OP_INSERT,
	OP_TWIDDLE,
	OP_KILL
};

class EditDistance
{
public:
	const string& GetOriginalString() const { return originalStr; }
	const string& GetTargetString() const { return targetStr; }
	const vector<OperationType>& GetOPChain() const { return opChain; }
	double GetEditDistance(const string &str1, const string &str2, const double opCost[6]);
	void Clear();

private:
	string originalStr;
	string targetStr;
	vector<OperationType> opChain;
};

#endif // _EDIT_DISTANCE_ALGO_H_
