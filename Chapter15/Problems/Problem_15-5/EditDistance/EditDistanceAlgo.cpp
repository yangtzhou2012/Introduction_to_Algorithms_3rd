#include "stdafx.h"
#include "EditDistanceAlgo.h"

static void GetOperatorChain(OperationType **opLast, int killPos, int i, int j, vector<OperationType> &opChain)
{
	if (opLast[i][j] == OP_NONE)
		return;

	if (opLast[i][j] == OP_COPY || opLast[i][j] == OP_REPLACE)
		GetOperatorChain(opLast, killPos, i-1, j-1, opChain);
	else if (opLast[i][j] == OP_DELETE)
		GetOperatorChain(opLast, killPos, i-1, j, opChain);
	else if (opLast[i][j] == OP_INSERT)
		GetOperatorChain(opLast, killPos, i, j-1, opChain);
	else if (opLast[i][j] == OP_TWIDDLE)
		GetOperatorChain(opLast, killPos, i-2, j-2, opChain);
	else
		GetOperatorChain(opLast, killPos, killPos, j, opChain);

	opChain.push_back(opLast[i][j]);
}

double EditDistance::GetEditDistance(const string &str1, const string &str2, const double opCost[6])
{
	opChain.clear();
	originalStr = str1;
	targetStr = str2;

	int originalStrLen = originalStr.size();
	int targetStrLen = targetStr.size();

	if (originalStrLen == 0 && targetStrLen == 0)
		return 0;

	double **transferCost = new double*[originalStrLen+1];
	OperationType **opLast = new OperationType*[originalStrLen+1];

	for (int i = 0; i <= originalStrLen; ++i)
	{
		transferCost[i] = new double[targetStrLen+1];
		opLast[i] = new OperationType[targetStrLen+1];
	}

	double d[5];
	int killPos = -1;

	opLast[0][0] = OP_NONE;
	transferCost[0][0] = 0;

	for (int j = 1; j <= targetStrLen; ++j)
	{
		opLast[0][j] = OP_INSERT;
		transferCost[0][j] = j*opCost[OP_INSERT];
	}

	for (int i = 1; i <= originalStrLen; ++i)
	{
		opLast[i][0] = OP_DELETE;
		transferCost[i][0] = i*opCost[OP_DELETE];
	}

	if (targetStrLen == 0 && opCost[OP_KILL] < transferCost[originalStrLen][0])
	{
		opLast[originalStrLen][0] = OP_KILL;
		transferCost[originalStrLen][0] = opCost[OP_KILL];
		killPos = 0;
	}

	for (int i = 1; i <= originalStrLen; ++i)
	{
		for (int j = 1; j <= targetStrLen; ++j)
		{
			if (originalStr[i-1] == targetStr[j-1])
			{
				d[OP_COPY] = opCost[OP_COPY] + transferCost[i-1][j-1];
				d[OP_REPLACE] = DBL_MAX;
			}
			else
			{
				d[OP_COPY] = DBL_MAX;
				d[OP_REPLACE] = opCost[OP_REPLACE] + transferCost[i-1][j-1];
			}

			d[OP_DELETE] = opCost[OP_DELETE] + transferCost[i-1][j];
			d[OP_INSERT] = opCost[OP_INSERT] + transferCost[i][j-1];

			if (i > 1 && j > 1 && originalStr[i-2] == targetStr[j-1] && originalStr[i-1] == targetStr[j-2])
				d[OP_TWIDDLE] = opCost[OP_TWIDDLE] + transferCost[i-2][j-2];
			else
				d[OP_TWIDDLE] = DBL_MAX;

			transferCost[i][j] = d[OP_COPY];
			opLast[i][j] = OP_COPY;
			for (int k = OP_REPLACE; k <= OP_TWIDDLE; ++k)
			{
				if (d[k] < transferCost[i][j])
				{
					transferCost[i][j] = d[k];
					opLast[i][j] = static_cast<OperationType>(k);
				}
			}
		}
	}

	d[0] = DBL_MAX;
	for (int k = 0; k < originalStrLen; ++k)
	{
		if (opCost[OP_KILL] + transferCost[k][targetStrLen] < d[0])
		{
			d[0] = opCost[OP_KILL] + transferCost[k][targetStrLen];
			killPos = k;
		}
	}

	if (d[0] < transferCost[originalStrLen][targetStrLen])
	{
		transferCost[originalStrLen][targetStrLen] = d[0];
		opLast[originalStrLen][targetStrLen] = OP_KILL;
	}

	GetOperatorChain(opLast, killPos, originalStrLen, targetStrLen, opChain);

	double res = transferCost[originalStrLen][targetStrLen];

	for (int i = 0; i <= originalStrLen; ++i)
	{
		delete[] transferCost[i];
		delete[] opLast[i];
	}

	delete[] transferCost;
	delete[] opLast;

	return res;
}

void EditDistance::Clear()
{
	originalStr.clear();
	targetStr.clear();
	opChain.clear();
}
