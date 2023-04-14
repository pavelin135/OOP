#include <iostream>
#include <fstream>
#include <string>
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
		{
			str = NULL;
			return;
		}

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
		if (str != NULL)
			cout << "Exception: " << str;
	}
};

class WrongDimensionsException : public Exception
{
private:
	int str1, col1, // str1, col1 -- matrix 1
		str2, col2; // str2, col2 -- matrix 2
public:
	WrongDimensionsException(int a, int b, int c, int d) : Exception("matrix dimension aren't equal")
	{
		if (a < 1 || b < 1 || c < 1 || d < 1)
		{
			str1 = str2 = col1 = col2 = 0;
			return;
		}
		str1 = a; col1 = b;
		str2 = c; col2 = d;
	}

	virtual void print()
	{
		if (str != NULL)
			cout << "Exception: " << str << endl << "matrix dimension 1:\n" << str1 << " x " << col1 << endl
				<< "matrix dimension 2:\n" << str2 << " x " << col2 << endl;
	}
};

class IndexOutOfBounds : public Exception
{
	int x, y, // index
		z, w; // matrix dim
public:
	IndexOutOfBounds(int a, int b, int c, int d) : Exception("wrong index of matrix")
	{
		if (c < 1 || d < 1)
		{
			x = y = z = w = 0;
			return;
		}
		x = a; y = b;
		z = c; w = d;
	}
	void print()
	{
		if (str != NULL)
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
			dimStr = 0;
			dimCol = 0;
			ptr = NULL;
			return;
		}

		ptr = new T * [x];
		if (ptr == NULL)
		{
			dimStr = 0;
			dimCol = 0;
			return;
		}

		for (int i = 0; i < x; i++)
		{
			ptr[i] = new T[y];
			if (ptr[i] == NULL)
			{
				dimStr = i;
				dimCol = 0;
				return;
			}
		}
		dimStr = x;
		dimCol = y;
	}


	MultiArray(const MultiArray& a)
	{
		dimStr = a.dimStr;
		dimCol = a.dimCol;

		ptr = new T * [dimStr];
		if (ptr == NULL)
		{
			dimStr = 0;
			dimCol = 0;
			return;
		}

		for (int i = 0; i < dimStr; i++)
		{
			ptr[i] = new T[dimCol];
			if (ptr[i] == NULL)
			{
				dimStr = i;
				dimCol = 0;
				return;
			}
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

	void repl(T* arr, int dim)
	{
		if (dim <= 1 || arr == NULL)
			return;
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
		for (int i = 0; i < dimStr; i++)
		{
			for (int j = 0; j < dimCol; j++)
			{
				cin >> ptr[i][j];
			}
		}
	}

	Matrix(fstream& f) : MultiArray<T>(0, 0)
	{
		if (!f.is_open())
		{
			cout << "\nfile is not opened\n";
			return;
		}
		f >> *this;
	}

	Matrix replRight()
	{
		if (dimCol <= 1 || dimStr < 1)
			return *this;

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
		return a;
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
		return a;
	}

	const T& getElement(int a, int b)
	{
		if (a > dimStr || b > dimCol || a < 1 || b < 1)
		{
			throw IndexOutOfBounds(a, b, dimStr, dimCol);
		}

		return ptr[a - 1][b - 1];
	}

	friend fstream& operator<< <T> (fstream& f, const Matrix<T>& a);
	friend fstream& operator>> <T> (fstream& f, Matrix<T>& a);

};

template <class T>
fstream& operator<<(fstream& f, const Matrix<T>& a)
{
	if (!f.is_open())
	{
		cout << "\nfile is not opened\n";
		return f;
	}
	for (int i = 0; i < a.dimStr; i++)
	{
		for (int j = 0; j < a.dimCol; j++)
		{
			f << a.ptr[i][j] << ' ';
		}
		f << '\n';
	}
	f << '\n';
	return f;
}


template <class T>
fstream& operator>>(fstream& f, Matrix<T>& a)
{
	if (!f.is_open())
	{
		cout << "\nfile is not opened\n";
		return f;
	}
	int str = 0,
		col = 0;

	string s = "";
	string c = "";
	getline(f, c);

	for (str; c != ""; str++)
	{
		s += c + '\n';
		getline(f, c);
	}

	for (int i = 0; s[i] != '\n'; i++)
	{
		col += s[i] == ' ' ? 1 : 0;
	}


	if (str != a.dimStr || col != a.dimCol)
	{
		T** arr = new T * [str];
		if (arr == NULL)
			return f;

		for (int i = 0; i < str; i++)
		{
			arr[i] = new T[col];

			if (arr[i] == NULL)
			{
				for (int j = 0; j < i; j++)
					delete[] arr[j];
				delete[] arr;
				return f;
			}
		}


		int cnt = 0;
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < col; j++)
			{
				string numb = "";
				while (s[cnt] != ' ')
				{
					if (s[cnt] == '\0')
						return f;
					numb += s[cnt];
					cnt++;
				}
				cnt += s[cnt + 1] == '\n' ? 2 : 1;
				try
				{
					if (typeid(T) == typeid(int))
						arr[i][j] = stoi(numb);

					else if (typeid(T) == typeid(double))
						arr[i][j] = stod(numb);

					else if (typeid(T) == typeid(float))
						arr[i][j] = stof(numb);

				}
				catch (invalid_argument e)
				{
					cout << "\ninvalid argument\n";
					for (int i = 0; i < str; i++)
						delete[] arr[i];
					delete[] arr;
					return f;
				}
			}
		}


		for (int i = 0; i < a.dimStr; i++)
			delete[] a.ptr[i];
		delete[] a.ptr;

		

		a.ptr = arr;
		a.dimStr = str;
		a.dimCol = col;
	}
	else
	{
		int cnt = 0;
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < col; j++)
			{
				string numb = "";
				while (s[cnt] != ' ')
				{
					if (s[cnt] == '\0')
						return f;
					numb += s[cnt];
					cnt++;
				}
				cnt += s[cnt + 1] == '\n' ? 2 : 1;
				try
				{
					if (typeid(T) == typeid(int))
						a.ptr[i][j] = stoi(numb);

					else if (typeid(T) == typeid(double))
						a.ptr[i][j] = stod(numb);

					else if (typeid(T) == typeid(float))
						a.ptr[i][j] = stof(numb);

				}
				catch (invalid_argument e)
				{
					cout << "\ninvalid argument\n";
					return f;
				}
			}
		}
	}

	return f;
}



int main()
{
	fstream f("INPUT.txt");
	Matrix<int> A(f);
	try
	{
		cout << A.getElement(1, 3);
	}
	catch (Exception& e)
	{
		e.print();
	}
}