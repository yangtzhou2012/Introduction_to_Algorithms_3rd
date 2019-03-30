#include <ctime>
#include <cstring>
#include <iostream>
#include <fstream>
#include <vector>
#include "Sort.h"

using namespace std;

const int m_MinLength = 2;
const int m_MaxLength = 770;
const int m_LengthStep = 16;
const int m_Loop = 50;

int main()
{
	clock_t start, end;
	vector<int> x;
	vector<long> y_insert;
	vector<long> y_bubble;
	vector<long> y_merge;
	vector<long> y_heap;
	vector<long> y_quick;
	vector<long> y_improved_quick;

	for(int len = m_MinLength; len <= m_MaxLength; len += m_LengthStep)
	{
		x.push_back(len);

		int *data = new int[len*m_Loop];
		int *insert_temp = new int[len*m_Loop];
		int *bubble_temp = new int[len*m_Loop];
		int *merge_temp = new int[len*m_Loop];
		int *heap_temp = new int[len*m_Loop];
		int *quick_temp = new int[len*m_Loop];
		int *improved_quick_temp = new int[len*m_Loop];

		srand((unsigned)time(NULL));
		for(int i = 0; i < len*m_Loop; ++i)
			data[i] = rand();

		memcpy(insert_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			insert_sort(insert_temp+i*len, len);
		end = clock();
		y_insert.push_back(end-start);

		memcpy(bubble_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			bubble_sort(bubble_temp+i*len, len);
		end = clock();
		y_bubble.push_back(end-start);

		memcpy(merge_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			merge_sort(merge_temp+i*len, len);
		end = clock();
		y_merge.push_back(end-start);

		memcpy(heap_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			heap_sort(heap_temp+i*len, len);
		end = clock();
		y_heap.push_back(end-start);

		memcpy(quick_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			quick_sort(quick_temp+i*len, len);
		end = clock();
		y_quick.push_back(end-start);

		memcpy(improved_quick_temp, data, len*m_Loop*sizeof(int));
		start = clock();
		for(int i = 0; i < m_Loop; ++i)
			improved_quick_sort(improved_quick_temp+i*len, len);
		end = clock();
		y_improved_quick.push_back(end-start);

		for(int i = 0; i < len*m_Loop; ++i)
		{
			if(insert_temp[i] != bubble_temp[i]
			   || insert_temp[i] != merge_temp[i]
			   || insert_temp[i] != heap_temp[i]
			   || insert_temp[i] != quick_temp[i]
			   || insert_temp[i] != improved_quick_temp[i])
			{
				cout << "Sort Fail!\n";

				delete[] data;
				delete[] insert_temp;
				delete[] bubble_temp;
				delete[] merge_temp;
				delete[] heap_temp;
				delete[] quick_temp;
				delete[] improved_quick_temp;
				return 0;
			}
		}

		delete[] data;
		delete[] insert_temp;
		delete[] bubble_temp;
		delete[] merge_temp;
		delete[] heap_temp;
		delete[] quick_temp;
		delete[] improved_quick_temp;
	}

	ofstream os("result.txt");
	
	os << "len = [";
	for(size_t i = 0; i < x.size(); ++i)
	{
		os << x[i];
		if(i < x.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_insert = [";
	for(size_t i = 0; i < y_insert.size(); ++i)
	{
		os << y_insert[i];
		if(i < y_insert.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_bubble = [";
	for(size_t i = 0; i < y_bubble.size(); ++i)
	{
		os << y_bubble[i];
		if(i < y_bubble.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_merge = [";
	for(size_t i = 0; i < y_merge.size(); ++i)
	{
		os << y_merge[i];
		if(i < y_merge.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_heap = [";
	for(size_t i = 0; i < y_heap.size(); ++i)
	{
		os << y_heap[i];
		if(i < y_heap.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_quick = [";
	for(size_t i = 0; i < y_quick.size(); ++i)
	{
		os << y_quick[i];
		if(i < y_quick.size()-1) os << ", ";
	}
	os << "];\n";

	os << "y_improved_quick = [";
	for(size_t i = 0; i < y_improved_quick.size(); ++i)
	{
		os << y_improved_quick[i];
		if(i < y_improved_quick.size()-1) os << ", ";
	}
	os << "];\n";

	os << "\n";

	return 0;
}


