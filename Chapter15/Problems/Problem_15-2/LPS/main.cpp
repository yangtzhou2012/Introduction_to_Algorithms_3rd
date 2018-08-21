#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;


#define _DEBUG_EN_


enum LPSDirType
{
	LPS_DIR_BOTTOM		= 0,
	LPS_DIR_LEFT		= 1,
	LPS_DIR_LEFT_BOTTOM	= 2,
	LPS_DIR_SINGLE_CHAR	= 3,
};

#ifdef _DEBUG_EN_
void PrintDebugInfo(int **lpsLen, unsigned char **pDir, int n, ostream &os)
{
	os << "c:\n";

	for(int i = 0; i <= n; ++i)
	{
		for(int j = 0; j < i; ++j)
			os << "\t";

		os << "0" << "\t";

		for(int j = 0; j < n-i; ++j)
			os << lpsLen[i][j] << "\t";

		os << "\n";
	}

	os << "\n" << "b:\n";

	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < i; ++j)
			os << "\t";

		for(int j = 0; j < n-i; ++j)
		{
			if(pDir[i][j] == LPS_DIR_BOTTOM)
				os << "B" << "\t";
			else if(pDir[i][j] == LPS_DIR_LEFT)
				os << "L" << "\t";
			else if(pDir[i][j] == LPS_DIR_LEFT_BOTTOM)
				os << "LB" << "\t";
			else
				os << "S" << "\t";
		}

		os << "\n";
	}
}
#endif // #ifdef _DEBUG_EN_

void PrintLPS(unsigned char **pDir, const char *s, int i, int j, ostream &os)
{
	if(i <= j)
	{
		if(pDir[i][j-i] == LPS_DIR_LEFT_BOTTOM)
		{
			os << s[i];
			PrintLPS(pDir, s, i+1, j-1, os);
			os << s[j];
		}
		else
		{
			if(pDir[i][j-i] == LPS_DIR_BOTTOM)
				PrintLPS(pDir, s, i+1, j, os);
			else if(pDir[i][j-i] == LPS_DIR_LEFT)
				PrintLPS(pDir, s, i, j-1, os);
			else
				os << s[i];
		}
	}
}

void LPS(const char *s)
{
	if(s == NULL)
		return;

	int n = strlen(s);
	if(n <= 0)
		return;

	int **lpsLen = new int*[n];
	unsigned char **pDir = new unsigned char*[n];
	for(int i = 0; i < n; ++i)
	{
		lpsLen[i] = new int[n-i];
		lpsLen[i][0] = 1;
		pDir[i] = new unsigned char[n-i];
	}

	for(int l = 2; l <= n; ++l)
	{
		for(int i = 0; i <= n-l; ++i)
		{
			int j = i+l-1;

			if(s[i] == s[j])
			{
				lpsLen[i][l-1] = (l >= 3 ? lpsLen[i+1][l-3] : 0) + 2;
				pDir[i][l-1] = LPS_DIR_LEFT_BOTTOM;
			}
			else
			{
				int leftLen = lpsLen[i][l-2];
				int bottomLen = lpsLen[i+1][l-2];

				if(leftLen <= bottomLen)
				{
					lpsLen[i][l-1] = bottomLen;
					pDir[i][l-1] = LPS_DIR_BOTTOM;
				}
				else
				{
					lpsLen[i][l-1] = leftLen;
					pDir[i][l-1] = LPS_DIR_LEFT;
				}
			}
		}
	}

#ifdef _DEBUG_EN_
	ofstream out_file("DebugInfo.txt");
	PrintDebugInfo(lpsLen, pDir, n, out_file);
	out_file.close();
#endif // #ifdef _DEBUG_EN_

	PrintLPS(pDir, s, 0, n-1, cout);

	for(int i = 0; i < n; ++i)
	{
		delete[] lpsLen[i];
		delete[] pDir[i];
	}

	delete[] lpsLen;
	delete[] pDir;
}

int main()
{
	const char *s = "character";
	//const char *s = "aibohphobia";

	LPS(s);
}
