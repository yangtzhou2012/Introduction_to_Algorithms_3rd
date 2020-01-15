#include <iostream>
#include "BucketSort.h"

using namespace std;

template <typename T>
void output_list(ostream &os, const LinkedList<T> &list)
{
	const LinkedListNode<T> *h = list.get_head();

	while (h != NULL)
	{
		os << h->element << " ";
		h = h->next;
	}

	os << "\n";
}

template <typename T>
void output_array(ostream &os, const T data[], int n)
{
	if (data != NULL)
	{
		for (int i = 0; i < n; ++i)
			os << data[i] << " ";
	}

	os << "\n";
}

int main()
{
	double a1[] = {0.78, 0.17, 0.39, 0.26, 0.72, 0.94, 0.21, 0.12, 0.23, 0.68};
	cout << "a1[] before sort: ";
	output_array(cout, a1, sizeof(a1)/sizeof(double));
	cout << "\n";

	bucket_sort(a1, sizeof(a1)/sizeof(double), sizeof(a1)/sizeof(double), 0.0, 1.0);

	cout << "a1[] after sort: ";
	output_array(cout, a1, sizeof(a1)/sizeof(double));
	cout << "\n";


	double a2[] ={ 0.79, 0.13, 0.16, 0.64, 0.39, 0.20, 0.89, 0.53, 0.71, 0.42 };
	cout << "a2[] before sort: ";
	output_array(cout, a2, sizeof(a2)/sizeof(double));
	cout << "\n";

	bucket_sort(a2, sizeof(a2)/sizeof(double), sizeof(a2)/sizeof(double), 0.0, 1.0);

	cout << "a2[] after sort: ";
	output_array(cout, a2, sizeof(a2)/sizeof(double));
	cout << "\n";


	double a3[] ={ 0.79 };
	cout << "a3[] before sort: ";
	output_array(cout, a3, sizeof(a3)/sizeof(double));
	cout << "\n";

	bucket_sort(a3, sizeof(a3)/sizeof(double), sizeof(a3)/sizeof(double));

	cout << "a3[] after sort: ";
	output_array(cout, a3, sizeof(a3)/sizeof(double));
	cout << "\n";


	double a4[] ={ 0.79, 0.1, 0.78, 0.3 };
	cout << "a4[] before sort: ";
	output_array(cout, a4, sizeof(a4)/sizeof(double));
	cout << "\n";

	bucket_sort(a4, sizeof(a4)/sizeof(double), sizeof(a4)/sizeof(double));

	cout << "a4[] after sort: ";
	output_array(cout, a4, sizeof(a4)/sizeof(double));
	cout << "\n";

	return 0;
}

