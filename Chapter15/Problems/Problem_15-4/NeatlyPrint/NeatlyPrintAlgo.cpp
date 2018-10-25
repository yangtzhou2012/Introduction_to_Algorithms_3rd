#include "NeatlyPrintAlgo.h"
#include <fstream>
#include <vector>

using namespace std;

static bool GetWord(const string &inFileName, int lineCapacity,
					vector<string> &wordTable, vector<int> &wordLenTable)
{
	ifstream inFile(inFileName);
	string word;

	while (inFile >> word)
	{
		if (static_cast<int>(word.size()) > lineCapacity)
		{
			inFile.close();
			return false;
		}

		wordTable.push_back(word);
		wordLenTable.push_back(word.size());
	}

	inFile.close();
	return true;
}

static void OutputWord(vector<string> &wordTable, int lineStart[], int j, int lineCapacity, ostream &os)
{
	if (j <= 0)
		return;

	OutputWord(wordTable, lineStart, lineStart[j]-1, lineCapacity, os);

	int lineLen = 0;

	for (int i = lineStart[j]; i <= j; ++i)
	{
		os << wordTable[i];
		lineLen += wordTable[i].size();

		if (i < j)
		{
			os << " ";
			lineLen += 1;
		}
	}

	while (lineLen++ < lineCapacity)
		os << "|";

	os << "\n";
}

int NeatlyPrint(const string &inFileName, int lineCapacity, const string &outFileName)
{
	if (lineCapacity <= 0)
		return -1;

	vector<string> wordTable;
	vector<int> wordLenTable;

	if (!GetWord(inFileName, lineCapacity, wordTable, wordLenTable))
		return -1;

	int n = wordTable.size();
	if (n <= 0)
		return -1;
	
	vector<int> *lineCubes = new vector<int>[n];
	int *cubes = new int[n+1];
	int *lineStart = new int[n];

	for (int j = 0; j < n; ++j)
	{
		int lineExtra = lineCapacity;

		for (int i = j; i >= 0; --i)
		{
			lineExtra -= wordLenTable[i];
			if (i != j) lineExtra -= 1;

			if (lineExtra < 0) break;
			else if (j < n-1) lineCubes[j].push_back(lineExtra*lineExtra*lineExtra);
			else lineCubes[j].push_back(0);
		}
	}

	cubes[0] = 0;

	for (int j = 0; j < n; ++j)
	{
		cubes[j+1] = lineCubes[j][0] + cubes[j];
		lineStart[j] = j;
		int i = j - 1;

		for (vector<int>::iterator it = lineCubes[j].begin()+1; it != lineCubes[j].end(); ++it)
		{
			int curCubes = *it + cubes[i];
			if (curCubes < cubes[j+1])
			{
				cubes[j+1] = curCubes;
				lineStart[j] = i;
			}

			--i;
		}
	}

	int totalCubes = cubes[n];
	delete[] cubes;
	delete[] lineCubes;

	ofstream outFile(outFileName);

	OutputWord(wordTable, lineStart, n-1, lineCapacity, outFile);

	delete[] lineStart;
	outFile.close();

	return totalCubes;
}
