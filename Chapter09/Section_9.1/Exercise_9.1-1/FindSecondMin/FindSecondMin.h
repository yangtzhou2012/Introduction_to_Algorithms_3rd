#ifndef _FIND_SECOND_MIN_H_
#define _FIND_SECOND_MIN_H_

#include <list>
#include <iostream>

using namespace std;

//#define _DEBUG_INFO_ENABLE_
#define _DEBUG_COMPARE_TIMES_ENABLE_

struct CompareTable
{
	int num;
	int *table;
	bool *leftLess;
};

template <typename T>
int FindSecondMin(const T data[], int n
#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
				  , int &compareTimes
#endif
)
{
	if (data == NULL || n < 2)
		return -1;

	list<CompareTable*> cmpTableList;

	CompareTable *cur = new CompareTable;

	cur->num = n;
	cur->table = new int[cur->num];
	cur->leftLess = NULL;
	for (int i = 0; i < n; ++i)
		cur->table[i] = i;

	cmpTableList.push_back(cur);

#ifdef _DEBUG_INFO_ENABLE_
	cout << "Array:\t";
	for (int i = 0; i < n; ++i)
		cout << data[i] << "\t";
	cout << "\n";

	int round = 0;
	cout << "Round " << round << ":\t";
	round++;
	for (int i = 0; i < cur->num; ++i)
		cout << cur->table[i] << "\t";
	cout << "\n";
#endif

#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
	compareTimes = 0;
#endif

	while (cur->num > 1)
	{
		CompareTable *next = new CompareTable;

		next->num = cur->num / 2;
		if ((cur->num & 1) == 1)
			next->num++;

		next->leftLess = new bool[next->num];
		next->table = new int[next->num];

		int k = 0;
		for (int i = 0; i < cur->num - 1; i += 2)
		{
#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
			compareTimes++;
#endif
			if (data[cur->table[i]] <= data[cur->table[i+1]])
			{
				next->table[k] = cur->table[i];
				next->leftLess[k++] = true;
			}
			else
			{
				next->table[k] = cur->table[i+1];
				next->leftLess[k++] = false;
			}
		}

		if ((cur->num & 1) == 1)
		{
			next->table[k] = cur->table[cur->num-1];
			next->leftLess[k] = true;
		}

		cur = next;
		cmpTableList.push_back(cur);

#ifdef _DEBUG_INFO_ENABLE_
		cout << "Round " << round << ":\t";
		round++;
		for (int i = 0; i < cur->num; ++i)
			cout << cur->table[i] << "\t";
		cout << "\n";
#endif
	}

	list<CompareTable*>::reverse_iterator it = cmpTableList.rbegin();
	cur = *it++;

	int curMinId;
	int secondMinId;
	int tempId;

	if (cur->leftLess[0])
	{
		curMinId = 0;
		secondMinId = (*it)->table[1];
	}
	else
	{
		curMinId = 1;
		secondMinId = (*it)->table[0];
	}

	cur = *it++;

	while (it != cmpTableList.rend())
	{
		if (cur->leftLess[curMinId])
		{
			curMinId = curMinId * 2;

			if (curMinId < (*it)->num - 1)
				tempId = (*it)->table[curMinId+1];
			else
				tempId = -1;
		}
		else
		{
			curMinId = curMinId * 2 + 1;
			tempId = (*it)->table[curMinId-1];
		}

		if (tempId >= 0)
		{
#ifdef _DEBUG_COMPARE_TIMES_ENABLE_
			compareTimes++;
#endif
			if (data[tempId] < data[secondMinId])
				secondMinId = tempId;
		}

		cur = *it++;
	}

	for (it = cmpTableList.rbegin(); it != cmpTableList.rend(); ++it)
	{
		delete[] (*it)->table;
		delete[] (*it)->leftLess;
		delete (*it);
		*it = NULL;
	}

	return secondMinId;
}

#endif // #ifndef _FIND_SECOND_MIN_H_
