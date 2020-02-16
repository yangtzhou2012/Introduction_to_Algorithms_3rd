#ifndef _STRASSEN_SQUARE_MATRIX_MULTIPLY_H_
#define _STRASSEN_SQUARE_MATRIX_MULTIPLY_H_

template <typename T>
static void NaiveMatrixMultiply(T **a, int ay, int ax,
								T **b, int by, int bx,
								int m, int p, int n,
								T **c, int cy, int cx)
{
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			T sum = 0;
			for (int k = 0; k < p; ++k)
				sum += a[ay+i][ax+k] * b[by+k][bx+j];

			c[cy+i][cx+j] = sum;
		}
	}
}

template <typename T>
static void MatrixAdd(T **a, int ay, int ax,
					  T **b, int by, int bx,
					  int m, int n,
					  T **c, int cy, int cx)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			c[cy+i][cx+j] = a[ay+i][ax+j] + b[by+i][bx+j];
}

template <typename T>
static void MatrixSub(T **a, int ay, int ax,
					  T **b, int by, int bx,
					  int m, int n,
					  T **c, int cy, int cx)
{
	for (int i = 0; i < m; ++i)
		for (int j = 0; j < n; ++j)
			c[cy+i][cx+j] = a[ay+i][ax+j] - b[by+i][bx+j];
}

template <typename T>
static void StrassenSquareMatrixMultiply(T **a, int ay, int ax,
										 T **b, int by, int bx,
										 int n, T **c, int cy, int cx)
{
	if (n == 1)
	{
		c[cy][cx] = a[ay][ax] * b[by][bx];
	}
	else if ((n&1) == 1)
	{
		int m = n - 1;
		int aym = ay + m;
		int axm = ax + m;
		int bym = by + m;
		int bxm = bx + m;
		int cym = cy + m;
		int cxm = cx + m;

		T *tempMem = new T[m*m];
		T **temp = new T*[m];

		temp[0] = tempMem;
		for (int i = 1; i < m; ++i)
			temp[i] = temp[i-1] + m;

		StrassenSquareMatrixMultiply(a, ay, ax, b, by, bx, m, c, cy, cx);
		NaiveMatrixMultiply(a, ay, axm, b, bym, bx, m, 1, m, temp, 0, 0);
		MatrixAdd(c, cy, cx, temp, 0, 0, m, m, c, cy, cx);

		NaiveMatrixMultiply(a, ay, ax, b, by, bxm, m, m, 1, c, cy, cxm);
		NaiveMatrixMultiply(a, ay, axm, b, bym, bxm, m, 1, 1, temp, 0, 0);
		MatrixAdd(c, cy, cxm, temp, 0, 0, m, 1, c, cy, cxm);

		NaiveMatrixMultiply(a, aym, ax, b, by, bx, 1, m, m, c, cym, cx);
		NaiveMatrixMultiply(a, aym, axm, b, bym, bx, 1, 1, m, temp, 0, 0);
		MatrixAdd(c, cym, cx, temp, 0, 0, 1, m, c, cym, cx);

		NaiveMatrixMultiply(a, aym, ax, b, by, bxm, 1, m, 1, c, cym, cxm);
		c[cym][cxm] += (a[aym][axm] * b[bym][bxm]);

		delete[] tempMem;
		delete[] temp;
	}
	else
	{
		int m = (n>>1);
		int aym = ay + m;
		int axm = ax + m;
		int bym = by + m;
		int bxm = bx + m;
		int cym = cy + m;
		int cxm = cx + m;

		T *tempMem = new T[m*m*17];
		T ***temp = new T**[17];

		for (int i = 0; i < 17; ++i)
		{
			temp[i] = new T*[m];
			temp[i][0] = tempMem + m*m*i;
			for (int j = 1; j < m; ++j)
				temp[i][j] = temp[i][j-1] + m;
		}

		MatrixSub(b, by,  bxm, b, bym, bxm, m, m, temp[0], 0, 0);
		MatrixAdd(a, ay,  ax,  a, ay,  axm, m, m, temp[1], 0, 0);
		MatrixAdd(a, aym, ax,  a, aym, axm, m, m, temp[2], 0, 0);
		MatrixSub(b, bym, bx,  b, by,  bx,  m, m, temp[3], 0, 0);
		MatrixAdd(a, ay,  ax,  a, aym, axm, m, m, temp[4], 0, 0);
		MatrixAdd(b, by,  bx,  b, bym, bxm, m, m, temp[5], 0, 0);
		MatrixSub(a, ay,  axm, a, aym, axm, m, m, temp[6], 0, 0);
		MatrixAdd(b, bym, bx,  b, bym, bxm, m, m, temp[7], 0, 0);
		MatrixSub(a, ay,  ax,  a, aym, ax,  m, m, temp[8], 0, 0);
		MatrixAdd(b, by,  bx,  b, by,  bxm, m, m, temp[9], 0, 0);

		StrassenSquareMatrixMultiply(a, ay, ax, temp[0], 0, 0, m, temp[10], 0, 0);
		StrassenSquareMatrixMultiply(temp[1], 0, 0, b, bym, bxm, m, temp[11], 0, 0);
		StrassenSquareMatrixMultiply(temp[2], 0, 0, b, by, bx, m, temp[12], 0, 0);
		StrassenSquareMatrixMultiply(a, aym, axm, temp[3], 0, 0, m, temp[13], 0, 0);
		StrassenSquareMatrixMultiply(temp[4], 0, 0, temp[5], 0, 0, m, temp[14], 0, 0);
		StrassenSquareMatrixMultiply(temp[6], 0, 0, temp[7], 0, 0, m, temp[15], 0, 0);
		StrassenSquareMatrixMultiply(temp[8], 0, 0, temp[9], 0, 0, m, temp[16], 0, 0);

		MatrixAdd(temp[14], 0, 0, temp[13], 0, 0, m, m, c, cy, cx);
		MatrixSub(c, cy, cx, temp[11], 0, 0, m, m, c, cy, cx);
		MatrixAdd(c, cy, cx, temp[15], 0, 0, m, m, c, cy, cx);

		MatrixAdd(temp[10], 0, 0, temp[11], 0, 0, m, m, c, cy, cxm);

		MatrixAdd(temp[12], 0, 0, temp[13], 0, 0, m, m, c, cym, cx);

		MatrixAdd(temp[14], 0, 0, temp[10], 0, 0, m, m, c, cym, cxm);
		MatrixSub(c, cym, cxm, temp[12], 0, 0, m, m, c, cym, cxm);
		MatrixSub(c, cym, cxm, temp[16], 0, 0, m, m, c, cym, cxm);

		for (int i = 0; i < 17; ++i)
			delete[] temp[i];

		delete[] temp;
		delete[] tempMem;
	}
}

template <typename T>
bool StrassenSquareMatrixMultiply(T *a, T *b, int n, T *c)
{
	if (a == NULL || b == NULL || n < 1 || c == NULL)
		return false;

	T **ap = new T*[n];
	T **bp = new T*[n];
	T **cp = new T*[n];

	ap[0] = a;
	bp[0] = b;
	cp[0] = c;

	for (int i = 1; i < n; ++i)
	{
		ap[i] = ap[i-1] + n;
		bp[i] = bp[i-1] + n;
		cp[i] = cp[i-1] + n;
	}

	StrassenSquareMatrixMultiply(ap, 0, 0, bp, 0, 0, n, cp, 0, 0);

	delete[] ap;
	delete[] bp;
	delete[] cp;

	return true;
}


#endif // #ifndef _STRASSEN_SQUARE_MATRIX_MULTIPLY_H_
