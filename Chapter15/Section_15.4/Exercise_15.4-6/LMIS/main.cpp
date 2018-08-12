#include <iostream>

using namespace std;


//#define _DEBUG_EN_


int FindPos(int x, int temp[], int last_index)
{
	int left = 0;
	int right = last_index;

	while(left < right)
	{
		int mid = (left+right)/2;

		if(temp[mid] >= x)
			right = mid;
		else
			left = mid + 1;
	}

	if(temp[right] >= x)
		return right;
	else
		return right+1;
}

void PrintLMIS(int s[], int len[], int i, int last_index, ostream &os)
{
	if(last_index < 0)
		return;

	for( ; i >= 0; --i)
	{
		if(len[i] == last_index)
		{
			PrintLMIS(s, len, i-1, last_index-1, os);
			os << s[i] << " ";
			break;
		}
	}
}

#ifdef _DEBUG_EN_
void PrintTemp(int i, int temp[], int last_index, ostream &os)
{
	os << i << ":\t";
	for(int i = 0; i <= last_index; ++i)
		os << temp[i] << "\t";
	os << "\n";
}

void PrintLen(int len[], int n, ostream &os)
{
	for(int i = 0; i < n; ++i)
		os << len[i] << "\t";
	os << "\n";
}
#endif

void LMIS(int s[], int n)
{
	if(s == NULL || n == 0)
		return;

	int *temp = new int[n];
	int *len = new int[n];

	temp[0] = s[0];
	len[0] = 0;
	int last_index = 0;
#ifdef _DEBUG_EN_
	PrintTemp(0, temp, last_index, cout);
#endif

	for(int i = 1; i < n; ++i)
	{
		int pos = FindPos(s[i], temp, last_index);
		temp[pos] = s[i];
		len[i] = pos;
		if(pos > last_index) last_index = pos;

#ifdef _DEBUG_EN_
		PrintTemp(i, temp, last_index, cout);
#endif
	}

#ifdef _DEBUG_EN_
	PrintLen(len, n, cout);
#endif

	PrintLMIS(s, len, n-1, last_index, cout);
	cout << "\n";

	delete[] temp;
	delete[] len;
}

int main()
{
	int s[] = {9, 1, 2, 4, 6, 3, 5, 0};

	LMIS(s, sizeof(s)/sizeof(int));

	return 0;
}
