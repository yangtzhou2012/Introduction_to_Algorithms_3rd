#ifndef _D_MAX_HEAP_H_
#define _D_MAX_HEAP_H_

#include <stdexcept>

using namespace std;

template <typename T>
class DMaxHeap
{
public:
	explicit DMaxHeap(int d = 2);
	DMaxHeap(const DMaxHeap &rhs);
	~DMaxHeap();

	const DMaxHeap& operator=(const DMaxHeap &rhs);

	bool empty() const { return theSize == 0; }
	int branches() const { return theBranches; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }
	const T& operator[](int i) const;

	bool set_branches(int d);
	void clear();
	void insert(const T &x);
	const T extract_max();
	void increase_key(int i, const T &key);

private:
	static const int SPARE_CAPACITY = 8;
	int theBranches;
	T *data;
	int theCapacity;	// queue capacity
	int theSize;		// number of queue valid elements

	void reserve(int newCapacity);
	void max_heapify(int i);
	int PARENT(int i) const { return (i-1)/theBranches; }
	int LEFT(int i) const { return i*theBranches + 1; }
};

template <typename T>
DMaxHeap<T>::DMaxHeap(int d) : theBranches(d), theSize(0), theCapacity(SPARE_CAPACITY)
{
	data = new T[SPARE_CAPACITY];
	if (theBranches < 2) theBranches = 2;
}

template <typename T>
DMaxHeap<T>::DMaxHeap(const DMaxHeap<T> &rhs) : data(NULL)
{
	operator=(rhs);
}

template <typename T>
DMaxHeap<T>::~DMaxHeap()
{
	if (data != NULL)
		delete[] data;
}

template <typename T>
const DMaxHeap<T>& DMaxHeap<T>::operator=(const DMaxHeap<T> &rhs)
{
	if (this != &rhs)
	{
		if (data != NULL) delete[] data;
		theBranches = rhs.branches();
		theSize = rhs.size();
		theCapacity = rhs.capacity();

		data = new T[theCapacity];
		for (int i = 0; i < theSize; ++i)
			data[i] = rhs[i];
	}

	return *this;
}

template <typename T>
const T& DMaxHeap<T>::operator[](int i) const
{
	if (i >= 0 && i < theSize)
		return data[i];
	else
		throw runtime_error("invalid index error");
}

template <typename T>
bool DMaxHeap<T>::set_branches(int d)
{
	if (d < 2)
		return false;

	theBranches = d;
	clear();
	return true;
}

template <typename T>
void DMaxHeap<T>::clear()
{
	if (data != NULL)
		delete[] data;

	theSize = 0;
	theCapacity = SPARE_CAPACITY;
	data = new T[SPARE_CAPACITY];
}

template <typename T>
void DMaxHeap<T>::insert(const T &x)
{
	if (theSize == theCapacity)
		reserve(theCapacity*2);

	int i = theSize;
	int parent = PARENT(i);

	while (i > 0 && data[parent] < x)
	{
		data[i] = data[parent];
		i = parent;
		parent = PARENT(i);
	}

	data[i] = x;
	theSize++;
}

template <typename T>
const T DMaxHeap<T>::extract_max()
{
	if (theSize < 1)
		throw runtime_error("queue empty error");

	T max = data[0];
	data[0] = data[--theSize];
	max_heapify(0);

	if (theSize <= theCapacity/4)
		reserve(theCapacity/2);

	return max;
}

template <typename T>
void DMaxHeap<T>::increase_key(int i, const T &key)
{
	if (i < theSize && data[i] <= key)
	{
		int parent = PARENT(i);

		while (i > 0 && data[parent] < key)
		{
			data[i] = data[parent];
			i = parent;
			parent = PARENT(i);
		}

		data[i] = key;
	}
}

template <typename T>
void DMaxHeap<T>::reserve(int newCapacity)
{
	if (newCapacity < SPARE_CAPACITY)
		newCapacity = SPARE_CAPACITY;

	if (newCapacity > theSize && newCapacity != theCapacity)
	{
		T *oldData = data;

		data = new T[newCapacity];
		for (int i = 0; i < theSize; ++i)
			data[i] = oldData[i];

		theCapacity = newCapacity;
		delete[] oldData;
	}
}

template<typename T>
void DMaxHeap<T>::max_heapify(int i)
{
	if (theSize > 0)
	{
		T tmp = data[i];
		int left = LEFT(i);

		while (left < theSize)
		{
			int maxChild = left;
			int child = left + 1;

			for(int k = 1; k < theBranches && child < theSize; ++k, ++child)
			{
				if (data[child] > data[maxChild])
					maxChild = child;
			}

			if (tmp < data[maxChild])
			{
				data[i] = data[maxChild];
				i = maxChild;
				left = LEFT(i);
			}
			else
				break;
		}

		data[i] = tmp;
	}
}

#endif // #ifndef _D_MAX_HEAP_H_
