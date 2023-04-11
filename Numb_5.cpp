#include <iostream>
using namespace std;

//Task 5.1

//Task 5.2
// в конструкторе MultyArray дописать delete[] ps
class Exception : exception
{
protected:
	char* str;
public:
	Exception(const char* c)
	{
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


class MultiArray
{
protected:
	int dimStr;
	int dimCol;
	double** ptr;

public:
	MultiArray(int x, int y) //x - string, y - coloumn
	{
		ptr = new double* [x];
		if (ptr == NULL)
			return;

		for (int i = 0; i < x; i++)
		{
			double* ps = new double[y];
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

		ptr = new double* [dimStr];
		if (ptr == NULL)
		{
			dimStr = 0;
			dimCol = 0;
			return;
		}
		
		for (int i = 0; i < dimStr; i++)
		{
			double* ps = new double[dimCol];
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

class Matrix : public MultiArray
{
	void repl(double* arr, int dim)
	{
		double sw = arr[dim - 1];
		for (int i = dim - 1; i > 0; i--)
		{
			arr[i] = arr[i - 1];
		}
		arr[0] = sw;
	}
public:
	Matrix(int x, int y) : MultiArray(x, y)
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

	double getElement(int a, int b)
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
	
}
