#include <iostream>
using namespace std;

//Task 5.1

//Task 5.2

class Exception : exception
{
protected:
	char* str;
public:
	Exception(const char* c)
	{
		if (c == NULL)
			return;
			
		int len = 0;

		for (len; c[len] != '\0'; len++);
		len++;

		str = new char[len];
		if (str == NULL)
			return;

		for (int i = 0; i < len; i++)
			str[i] = c[i];
	}
	~Exception()
	{
		if (str != NULL)
			delete[] str;
	}

	virtual void print()
	{
		cout << "Exception: " << str;
	}
};

class WrongDimensionsException : public Exception
{
private:
	int str1, col1,
		str2, col2;
public:
	WrongDimensionsException(int a, int b, int c, int d) : Exception("matrix dimension aren't equal")
	{
		if (a < 1 || b < 1 || c < 1 || d < 1)
		{
			return;
		}
		str1 = a; col1 = b;
		str2 = c; col2 = d;
	}

	void print()
	{
		cout << "Exception: " << str << endl << "matrix dimension 1:\n" << str1 << " x " << col1 << endl
			<< "matrix dimension 2:\n" << str2 << " x " << col2 << endl;
	}
};

class IndexOutOfBounds : public Exception
{
	int x, y, z, w;
public:
	IndexOutOfBounds(int a, int b, int c, int d) : Exception("wrong index of matrix")
	{
		if (a < 1 || b < 1 || c < 1 || d < 1)
		{
			return;
		}
		x = a; y = b;
		z = c; w = d;
	}
	void print()
	{
		cout << "Exception: " << str << endl
			<< "your index: " << x << "\t" << y << endl
			<< "matrix dimension: " << z << '\t' << w << endl;
	}
};

template <class T>
class MultiArray
{
protected:
	int dimStr;
	int dimCol;
	T** ptr;

public:
	MultiArray(int x, int y) //x - string, y - coloumn
	{
		if (x < 1 || y < 1)
		{
			return;
		}
		ptr = new T* [x];
		if (ptr == NULL)
			return;

		for (int i = 0; i < x; i++)
		{
			T* ps = new T[y];
			if (ps == NULL)
				return;
			ptr[i] = ps;
		}
		dimStr = x;
		dimCol = y;
	}


	MultiArray(const MultiArray& a)
	{
		dimStr = a.dimStr;
		dimCol = a.dimCol;

		ptr = new T* [dimStr];
		if (ptr == NULL)
		{
			dimStr = 0;
			dimCol = 0;
			return;
		}

		for (int i = 0; i < dimStr; i++)
		{
			T* ps = new T[dimCol];
			if (ps == NULL)
				return;
			ptr[i] = ps;
		}

		for (int i = 0; i < dimStr; i++)
		{
			for (int j = 0; j < dimCol; j++)
			{
				ptr[i][j] = a.ptr[i][j];
			}
		}
	}

	~MultiArray()
	{
		for (int i = 0; i < dimStr; i++)
		{
			if (ptr[i] != NULL)
				delete[] ptr[i];
		}
		if (ptr != NULL)
			delete[] ptr;
	}
};

template <class T>
class Matrix : public MultiArray<T>
{
	using MultiArray<T>::dimStr;
	using MultiArray<T>::dimCol;
	using MultiArray<T>::ptr;

	void repl(double* arr, int dim)
	{
		T sw = arr[dim - 1];
		for (int i = dim - 1; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[0] = sw;
	}
public:
	Matrix(int x, int y) : MultiArray<T>(x, y)
	{
		for (int i = 0; i < x; i++)
		{
			for (int j = 0; j < y; j++)
			{
				cin >> ptr[i][j];
			}
		}
	}

	Matrix replRight()
	{
		Matrix a(*this);

		for (int st = 0; st < a.dimStr; st++)
		{
			int steps = a.dimCol;
			for (int i = 0; i < steps; i++)
			{
				if (a.ptr[st][i % a.dimCol] < 0)
				{
					repl(a.ptr[st], a.dimCol);
					steps++;
					i++;
				}
			}
		}
		return Matrix(a);
	}

	Matrix operator+(const Matrix& b)
	{
		if (dimStr != b.dimStr || dimCol != b.dimCol)
		{
			throw WrongDimensionsException(dimStr, dimCol, b.dimStr, b.dimCol);
		}
		Matrix a(*this);

		for (int i = 0; i < dimStr; i++)
		{
			for (int j = 0; j < dimCol; j++)
			{
				a.ptr[i][j] += b.ptr[i][j];
			}
		}
		return Matrix(a);
	}

	T& getElement(int a, int b)
	{
		if (a > dimStr || b > dimCol)
		{
			throw IndexOutOfBounds(a, b, dimStr, dimCol);
		}

		return ptr[a - 1][b - 1];
	}
};



int main()
{
	Matrix<double> A(1, 2), B(1,1);
	try
	{
		A + B;
	}
	catch (Exception& e)
	{
		e.print();
	}

}
