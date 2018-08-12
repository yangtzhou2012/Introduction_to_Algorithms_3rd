#include <iostream>

using namespace std;

#define LCS_DIR_UP			0
#define LCS_DIR_LEFT		1
#define LCS_DIR_LEFT_UP		2

void PrintLCS(unsigned char *pDir, int s2[], int n2, int i, int j, ostream &os)
{
	if(i == 0 || j == 0)
		return;

	if(*pDir == LCS_DIR_LEFT_UP)
	{
		PrintLCS(pDir-n2-1, s2, n2, i-1, j-1, os);
		os << s2[j-1] << " ";
	}
	else
	{
		if(*pDir == LCS_DIR_UP)
			PrintLCS(pDir-n2, s2, n2, i-1, j, os);
		else
			PrintLCS(pDir-1, s2, n2, i, j-1, os);
	}
}

void LCS(int s1[], int n1, int s2[], int n2)
{
	if(s1 == NULL || n1 <= 0 || s2 == NULL || n2 <= 0)
		return;

	int *lcsLen = new int[(n1+1)*(n2+1)];
	unsigned char *lcsDir = new unsigned char[n1*n2];

	for(int i = 0; i < n2+1; ++i)
		lcsLen[i] = 0;

	for(int i = n2+1; i < (n1+1)*(n2+1); i += (n2+1))
		lcsLen[i] = 0;

	int *pLen = lcsLen + n2 + 2;
	unsigned char *pDir = lcsDir;

	for(int i = 0; i < n1; ++i)
	{
		for(int j = 0; j < n2; ++j)
		{
			if(s1[i] == s2[j])
			{
				*pLen = *(pLen-n2-2) + 1;
				*pDir = LCS_DIR_LEFT_UP;
			}
			else
			{
				int leftLen = *(pLen-1);
				int upLen = *(pLen-n2-1);

				if(leftLen <= upLen)
				{
					*pLen = upLen;
					*pDir = LCS_DIR_UP;
				}
				else
				{
					*pLen = leftLen;
					*pDir = LCS_DIR_LEFT;
				}
			}

			++pLen;
			++pDir;
		}

		++pLen;
	}

	PrintLCS(lcsDir+n1*n2-1, s2, n2, n1, n2, cout);

	delete[] lcsLen;
	delete[] lcsDir;
}

int main()
{
	int s1[] = {1, 2, 3, 2, 4, 1, 2};
	int s2[] = {2, 4, 3, 1, 2, 1};

	LCS(s1, sizeof(s1)/sizeof(int), s2, sizeof(s2)/sizeof(int));
}
