#ifndef _MAX_PRIORITY_QUEUE_H_
#define _MAX_PRIORITY_QUEUE_H_

#include <stdexcept>

using namespace std;

template <typename T>
class MaxPriorityQueue
{
public:
	explicit MaxPriorityQueue();
	MaxPriorityQueue(const MaxPriorityQueue &rhs);
	~MaxPriorityQueue();

	const MaxPriorityQueue& operator=(const MaxPriorityQueue &rhs);

	bool empty() const { return theSize == 0; }
	int size() const { return theSize; }
	int capacity() const { return theCapacity; }
	const T& operator[](int i) const;

	void clear();
	void insert(const T &x);
	const T extract_max();
	void increase_key(int i, const T &key);

private:
	static const int SPARE_CAPACITY = 4;
	T *data;
	int theCapacity;	// queue capacity
	int theSize;		// number of queue valid elements

	void reserve(int newCapacity);
	void max_heapify(int i);
	int PARENT(int i) const { return (i-1)>>1; }
	int LEFT(int i) const { return (i<<1) + 1; }
};

template <typename T>
MaxPriorityQueue<T>::MaxPriorityQueue() : theSize(0), theCapacity(SPARE_CAPACITY)
{
	data = new T[SPARE_CAPACITY];
}

template <typename T>
MaxPriorityQueue<T>::MaxPriorityQueue(const MaxPriorityQueue<T> &rhs) : data(NULL)
{
	operator=(rhs);
}

template <typename T>
MaxPriorityQueue<T>::~MaxPriorityQueue()
{
	if (data != NULL)
		delete[] data;
}

template <typename T>
const MaxPriorityQueue<T>& MaxPriorityQueue<T>::operator=(const MaxPriorityQueue<T> &rhs)
{
	if (this != &rhs)
	{
		if (data != NULL) delete[] data;
		theSize = rhs.size();
		theCapacity = rhs.capacity();

		data = new T[theCapacity];
		for (int i = 0; i < theSize; ++i)
			data[i] = rhs[i];
	}

	return *this;
}

template <typename T>
const T& MaxPriorityQueue<T>::operator[](int i) const
{
	if (i >= 0 && i < theSize)
		return data[i];
	else
		throw runtime_error("invalid index error");
}

template <typename T>
void MaxPriorityQueue<T>::clear()
{
	if (data != NULL)
	{
		delete[] data;
		data = NULL;
	}

	theSize = 0;
	theCapacity = SPARE_CAPACITY;
	data = new T[SPARE_CAPACITY];
}

template <typename T>
void MaxPriorityQueue<T>::insert(const T &x)
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
const T MaxPriorityQueue<T>::extract_max()
{
	if (theSize < 1)
		throw runtime_error("queue empty error");

	T max = data[0];
	data[0] = data[--theSize];
	max_heapify(0);

	return max;
}

template <typename T>
void MaxPriorityQueue<T>::increase_key(int i, const T &key)
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
void MaxPriorityQueue<T>::reserve(int newCapacity)
{
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
void MaxPriorityQueue<T>::max_heapify(int i)
{
	if (theSize > 0)
	{
		T tmp = data[i];
		int left = LEFT(i);

		while (left < theSize)
		{
			int right = left + 1;
			int maxChild = (right < theSize && data[left] < data[right]) ? right : left;

			if (tmp < data[maxChild])
			{
				data[i] = data[maxChild];
				i = maxChild;
				left = LEFT(i);
			}
			else
			{
				break;
			}
		}

		data[i] = tmp;
	}
}

#endif // #ifndef _MAX_PRIORITY_QUEUE_H_
