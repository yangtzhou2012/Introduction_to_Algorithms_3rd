#include <iostream>
#include <string>

using namespace std;

enum OperationType
{
	OP_NONE = -1,
	OP_COPY = 0,
	OP_REPLACE,
	OP_DELETE,
	OP_INSERT,
};

void OutputAlignedDNA1(const string &dna1, int **opLast, int i, int j, ostream &os)
{
	if (opLast[i][j] == OP_COPY || opLast[i][j] == OP_REPLACE)
	{
		OutputAlignedDNA1(dna1, opLast, i-1, j-1, os);
		os << dna1[i-1];
	}
	else if (opLast[i][j] == OP_DELETE)
	{
		OutputAlignedDNA1(dna1, opLast, i-1, j, os);
		os << dna1[i-1];
	}
	else if (opLast[i][j] == OP_INSERT)
	{
		OutputAlignedDNA1(dna1, opLast, i, j-1, os);
		os << " ";
	}
}

void OutputAlignedDNA2(const string &dna2, int **opLast, int i, int j, ostream &os)
{
	if (opLast[i][j] == OP_COPY || opLast[i][j] == OP_REPLACE)
	{
		OutputAlignedDNA2(dna2, opLast, i-1, j-1, os);
		os << dna2[j-1];
	}
	else if (opLast[i][j] == OP_DELETE)
	{
		OutputAlignedDNA2(dna2, opLast, i-1, j, os);
		os << " ";
	}
	else if (opLast[i][j] == OP_INSERT)
	{
		OutputAlignedDNA2(dna2, opLast, i, j-1, os);
		os << dna2[j-1];
	}
}

int DNAAlign(const string &dna1, const string &dna2, const int score[4], ostream &os)
{
	unsigned int len1 = dna1.size();
	unsigned int len2 = dna2.size();

	if (len1 == 0 && len2 == 0)
		return 0;

	int d[4];
	int **alignScore = new int*[len1+1];
	int **opLast = new int*[len1+1];

	for (unsigned int i = 0; i <= len1; ++i)
	{
		alignScore[i] = new int[len2+1];
		opLast[i] = new int[len2+1];
	}

	alignScore[0][0] = 0;
	opLast[0][0] = OP_NONE;

	for (unsigned int j = 1; j <= len2; ++j)
	{
		alignScore[0][j] = alignScore[0][j-1] + score[OP_INSERT];
		opLast[0][j] = OP_INSERT;
	}

	for (unsigned int i = 1; i <= len1; ++i)
	{
		alignScore[i][0] = alignScore[i-1][0] + score[OP_DELETE];
		opLast[i][0] = OP_DELETE;
	}

	for (unsigned int i = 1; i <= len1; ++i)
	{
		for (unsigned int j = 1; j <= len2; ++j)
		{
			if (dna1[i-1] == dna2[j-1])
			{
				d[OP_COPY] = score[OP_COPY] + alignScore[i-1][j-1];
				d[OP_REPLACE] = INT_MIN;
			}
			else
			{
				d[OP_COPY] = INT_MIN;
				d[OP_REPLACE] = score[OP_REPLACE] + alignScore[i-1][j-1];
			}

			d[OP_DELETE] = score[OP_DELETE] + alignScore[i-1][j];
			d[OP_INSERT] = score[OP_INSERT] + alignScore[i][j-1];

			alignScore[i][j] = d[OP_COPY];
			opLast[i][j] = OP_COPY;

			for (int k = 1; k < 4; ++k)
			{
				if (d[k] > alignScore[i][j])
				{
					alignScore[i][j] = d[k];
					opLast[i][j] = k;
				}
			}
		}
	}

	OutputAlignedDNA1(dna1, opLast, len1, len2, os);
	os << "\n";
	OutputAlignedDNA2(dna2, opLast, len1, len2, os);
	os << "\n";

	int res = alignScore[len1][len2];

	for (unsigned int i = 0; i <= len1; ++i)
	{
		delete[] alignScore[i];
		delete[] opLast[i];
	}

	delete[] alignScore;
	delete[] opLast;

	return res;
}

int main()
{
	int score[4] = {1, -1, -2, -2};

	DNAAlign("GATCGGCAT", "CAATGTGAATC", score, cout);

	return 0;
}
