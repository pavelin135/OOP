#include <iostream>
#include <fstream>
#include <string>
using namespace std;


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

	void repl(T* arr, int dim) const
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

	Matrix replRight() const
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
	if (f.eof())
	{
		return f;
	}

	/*
	*	INPUT Format:
	*	1 2 3 '\n'
	*	----- '\n'
	*	----- '\n'
	*	----- '\n'
	*	97 98 99 '\n'
	*	'\n'
	*	'\0'
	*/

	string s = "";

	int col = 0,
		str = 0;

	char c = f.get(),
		lc = '\0';

	bool first_space = 1;
	while (c != '\n')
	{
		switch (c)
		{
		case ' ':
		{
			if (lc == ' ' || first_space)
				return f;

			col++;
			s += c;
		}; break;
		case '-': s += c; break;
		case '.': s += c; break;
		case '0': s += c; break;
		case '1': s += c; break;
		case '2': s += c; break;
		case '3': s += c; break;
		case '4': s += c; break;
		case '5': s += c; break;
		case '6': s += c; break;
		case '7': s += c; break;
		case '8': s += c; break;
		case '9': s += c; break;
		default:
			return f;
			break;
		}
		first_space = 0;
		lc = c;
		c = f.get();
	}
	str++;

	if (lc != ' ')
		return f;
	
	if (col == 0)
		return f;

	c = f.get();

	for (str; c != '\n'; str++)
	{
		int ncol = 0;
		first_space = 1;
		while (c != '\n')
		{
			switch (c)
			{
			case ' ': 
			{
				if (lc == ' ' || first_space)
					return f;

				s += c;
				ncol++;
			}; break;
			case '-': s += c; break;
			case '.': s += c; break;
			case '0': s += c; break;
			case '1': s += c; break;
			case '2': s += c; break;
			case '3': s += c; break;
			case '4': s += c; break;
			case '5': s += c; break;
			case '6': s += c; break;
			case '7': s += c; break;
			case '8': s += c; break;
			case '9': s += c; break;
			default:
				return f;
				break;
			}
			first_space = 0;
			lc = c;
			c = f.get();
		}

		if (lc != ' ')
			return f;

		if (ncol != col)
			return f;

		c = f.get();
	}

	if (str != a.dimStr)
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
				{
					delete[] arr[j];
				}
				delete[] arr;
				return f;
			}
		}

		int k = 0;
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < col; j++)
			{
				string numb = "";
				for (k; s[k] != ' '; k++)
				{
					numb += s[k];
				}
				k++;

				try
				{
					if (typeid(T).name() == typeid(int).name())
					{
						arr[i][j] = stoi(numb);
					}
					else if (typeid(T).name() == typeid(double).name())
					{
						arr[i][j] = stod(numb);
					}
					else if (typeid(T).name() == typeid(float).name())
					{
						arr[i][j] = stof(numb);
					}
					else if (typeid(T).name() == typeid(long).name())
					{
						arr[i][j] = stol(numb);
					}
					else if (typeid(T).name() == typeid(long double).name())
					{
						arr[i][j] = stold(numb);
					}
					else if (typeid(T).name() == typeid(long long).name())
					{
						arr[i][j] = stoll(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long).name())
					{
						arr[i][j] = stoul(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long long).name())
					{
						arr[i][j] = stoull(numb);
					}
					else
					{
						for (int x = 0; x < str; x++)
							delete[] arr[x];
						delete[] arr;

						return f;
					}
				}
				catch (invalid_argument e)
				{
					cout << "\ninvalid argument\n";

					for (int x = 0; x < str; x++)
						delete[] arr[x];
					delete[] arr;

					return f;
				}
			}
		}

		if (a.ptr != NULL)
		{
			for (int i = 0; i < a.dimStr; i++)
			{
				if (a.ptr[i] != NULL)
					delete[] a.ptr[i];
			}
			delete[] a.ptr;
		}

		a.ptr = arr;
		a.dimCol = col;
		a.dimStr = str;
	}
	else if (col != a.dimCol)
	{
		for (int i = 0; i < str; i++)
		{
			if (a.ptr[i] != NULL)
				delete[] a.ptr[i];
		}
		a.dimCol = col;

		int k = 0;
		for (int i = 0; i < str; i++)
		{
			a.ptr[i] = new T[col];
			if (a.ptr[i] == NULL)
			{
				for (int n = 0; n < i; n++)
					delete[] a.ptr[n];
				delete[] a.ptr;
				a.dimStr = 0;
				a.dimCol = 0;
				return f;
			}

			for (int j = 0; j < col; j++)
			{
				string numb = "";
				for (k; s[k] != ' '; k++)
				{
					numb += s[k];
				}
				k++;

				try
				{
					if (typeid(T).name() == typeid(int).name())
					{
						a.ptr[i][j] = stoi(numb);
					}
					else if (typeid(T).name() == typeid(double).name())
					{
						a.ptr[i][j] = stod(numb);
					}
					else if (typeid(T).name() == typeid(float).name())
					{
						a.ptr[i][j] = stof(numb);
					}
					else if (typeid(T).name() == typeid(long).name())
					{
						a.ptr[i][j] = stol(numb);
					}
					else if (typeid(T).name() == typeid(long double).name())
					{
						a.ptr[i][j] = stold(numb);
					}
					else if (typeid(T).name() == typeid(long long).name())
					{
						a.ptr[i][j] = stoll(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long).name())
					{
						a.ptr[i][j] = stoul(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long long).name())
					{
						a.ptr[i][j] = stoull(numb);
					}
					else
					{
						for (int x = 0; x < i; x++)
							delete[] a.ptr[x];
						delete[] a.ptr;
						a.dimCol = 0;
						a.dimStr = 0;
						return f;
					}
				}
				catch (invalid_argument e)
				{
					cout << "\ninvalid argument\n";

					for (int x = 0; x < i; x++)
						delete[] a.ptr[x];
					delete[] a.ptr;
					a.dimCol = 0;
					a.dimStr = 0;
					return f;
				}
			}
		}
	}
	else
	{
		int k = 0;
		for (int i = 0; i < str; i++)
		{
			for (int j = 0; j < col; j++)
			{
				string numb = "";
				for (k; s[k] != ' '; k++)
				{	
					numb += s[k];
				}
				k++;

				try
				{
					if (typeid(T).name() == typeid(int).name())
					{
						a.ptr[i][j] = stoi(numb);
					}
					else if (typeid(T).name() == typeid(double).name())
					{
						a.ptr[i][j] = stod(numb);
					}
					else if (typeid(T).name() == typeid(float).name())
					{
						a.ptr[i][j] = stof(numb);
					}
					else if (typeid(T).name() == typeid(long).name())
					{
						a.ptr[i][j] = stol(numb);
					}
					else if (typeid(T).name() == typeid(long double).name())
					{
						a.ptr[i][j] = stold(numb);
					}
					else if (typeid(T).name() == typeid(long long).name())
					{
						a.ptr[i][j] = stoll(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long).name())
					{
						a.ptr[i][j] = stoul(numb);
					}
					else if (typeid(T).name() == typeid(unsigned long long).name())
					{
						a.ptr[i][j] = stoull(numb);
					}
					else
					{
						return f;
					}
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
	Matrix<int> A(2, 1);
	try
	{
		f >> A;
		cout << A.getElement(2, 1);
	}
	catch (Exception& e)
	{
		e.print();
	}
}