#include <iostream>
#include <iomanip>
#include "StringSplitAlgo.h"

using namespace std;

int main()
{
	int splitPos[] = { 9, 1, 7 };
	StringSplit strSplit;
	
	strSplit.SetLengthPosition(20, sizeof(splitPos)/sizeof(int), splitPos);
	strSplit.GenerateSplitOrder();

	for (unsigned int i = 0; i < strSplit.GetsplitOrder().size(); ++i)
	{
		int sp = strSplit.GetsplitOrder()[i];
		cout << "step_" << setw(2) << setfill('0') << i << "\t\t";
		cout << "split_pos = " << sp+1 << "\n";
	}
}
