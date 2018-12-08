#ifndef _YOUNG_MATRIX_ALGO_H_
#define _YOUNG_MATRIX_ALGO_H_

#include <stdexcept>

using namespace std;

template <typename T>
class YoungMatrix
{
public:
	YoungMatrix();
	explicit YoungMatrix(int w, int h, const T &infinity);
	YoungMatrix(const YoungMatrix &rhs);
	~YoungMatrix();
	const YoungMatrix& operator=(const YoungMatrix &rhs);

	const T& infinity() const { return theInfinity; }
	int width() const { return theWidth; }
	int height() const { return theHeight; }
	const T* operator[](int i) const;

	void clear();
	void set_infinity(const T &infinity) { theInfinity = infinity; }
	void set_size(int w, int h);
	T extract_min();
	void insert(const T &x);

private:
	int theWidth;
	int theHeight;
	T theInfinity;
	T *data;
};

template <typename T>
YoungMatrix<T>::YoungMatrix() : theWidth(0), theHeight(0), data(NULL)
{

}

template <typename T>
YoungMatrix<T>::YoungMatrix(int w, int h, const T &infinity) : theWidth(0), theHeight(0), theInfinity(infinity), data(NULL)
{
	if (w > 0 && h > 0)
	{
		data = new T[w*h];
		theWidth = w;
		theHeight = h;

		for (int i = 0; i < w*h; ++i)
			data[i] = theInfinity;
	}
}

template <typename T>
YoungMatrix<T>::YoungMatrix(const YoungMatrix<T> &rhs)
{
	operator=(rhs);
}

template <typename T>
YoungMatrix<T>::~YoungMatrix()
{
	if (data != NULL)
		delete[] data;
}

template <typename T>
const YoungMatrix<T>& YoungMatrix<T>::operator=(const YoungMatrix<T> &rhs)
{
	if (&rhs != this)
	{
		if (theWidth*theHeight != rhs.width()*rhs.height())
		{
			if (data != NULL) delete[] data;
			data = new T[rhs.width()*rhs.height()];
		}

		theWidth = rhs.width();
		theHeight = rhs.height();
		theInfinity = rhs.theInfinity;

		for (int i = 0; i < theWidth*theHeight; ++i)
			data[i] = rhs.data[i];
	}

	return *this;
}

template <typename T>
const T* YoungMatrix<T>::operator[](int i) const
{
	if (i >= 0 || i < theHeight)
		return data + i*theWidth;
	else
		throw runtime_error("invalid index error");
}

template <typename T>
void YoungMatrix<T>::clear()
{
	if (data != NULL)
	{
		delete[] data;
		data = NULL;
	}

	theWidth = 0;
	theHeight = 0;
}

template <typename T>
void YoungMatrix<T>::set_size(int w, int h)
{
	if (w > 0 && h > 0)
	{
		if (w != theWidth || h != theHeight)
		{
			if (data != NULL) delete[] data;
			data = new T[w*h];
			theWidth = w;
			theHeight = h;

			for (int i = 0; i < w*h; ++i)
				data[i] = theInfinity;
		}
	}
}

template <typename T>
T YoungMatrix<T>::extract_min()
{
	if (theWidth > 0 && theHeight > 0 && data != NULL && data[0] != theInfinity)
	{
		T min = data[0];
		int i = 0;	// row index
		int j = 0;	// column index
		int k = 0;	// index at data[]
		int smallest_offset;

		while (true)
		{
			if (i < theHeight-1)
			{
				smallest_offset = theWidth;	// defaultly move down
				if (j < theWidth-1 && data[k+1] < data[k+theWidth])		// move right
					smallest_offset = 1;
			}
			else if (j < theWidth-1)	// move right
				smallest_offset = 1;
			else
				break;

			if (data[k+smallest_offset] < theInfinity)
			{
				data[k] = data[k+smallest_offset];
				k += smallest_offset;
				if (smallest_offset == theWidth) i++;
				else j++;
			}
			else
				break;
		}

		data[k] = theInfinity;
		return min;
	}
	else
		throw runtime_error("empty matrix error");
}

template <typename T>
void YoungMatrix<T>::insert(const T &x)
{
	if (theWidth < 1 || theHeight < 1 || data == NULL)
		return;

	int k = theWidth*theHeight-1;	// index at data[]
	if (data[k] < theInfinity)
		return;

	int i = theHeight-1;	// row index
	int j = theWidth-1;		// column index
	int largest_offset;

	while (true)
	{
		if (i > 0)
		{
			largest_offset = -theWidth;
			if (j > 0 && data[k-theWidth] < data[k-1])
				largest_offset = -1;
		}
		else if (j > 0)
			largest_offset = -1;
		else
			break;

		if (x < data[k+largest_offset])
		{
			data[k] = data[k+largest_offset];
			k += largest_offset;
			if (largest_offset == -theWidth) i--;
			else j--;
		}
		else
			break;
	}

	data[k] = x;
}

#endif // #ifndef _YOUNG_MATRIX_ALGO_H_
