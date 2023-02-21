#include <iostream>
using namespace std;

class C
{
private:
	int matrix_el[4];

public:
	C() // конструктор, в котором вводятся элементы матрицы
	{
		cout << "enter 4 elements for matrix 2x2:\n";
		for (int i = 0; i < 4; i++)
		{
			cin >> matrix_el[i];
		}
	}

	int determinant() // считает определитель
	{
		return (matrix_el[0] * matrix_el[3] - matrix_el[1] * matrix_el[2]);
	}

	bool inverse_matrix() // проверяет, существует ли обратная матрица для данной
	{
		return determinant() == 0 ? false : true;
	}
	
	bool operator< (C A)
	{
		return determinant() < A.determinant() ? true : false;
	}

	friend bool operator< (int, C);
	friend bool operator< (C, int);
};

bool operator< (C A, int a)
{
	return A.determinant() < a ? true : false;
}

bool operator< (int a, C A)
{
	return a < A.determinant() ? true : false;
}

int main()
{
	C A, B;

	cout <<"determinant A: " << A.determinant() << endl
		 << "determinant B: " << B.determinant() << endl;

	bool f = A < B, k = B < A,
		r = 5 < A, d = -5 < B;

	
	cout << "Does determint A less than determinant B\? " << f << endl
		<< "Does determint B less than determinant A\? " << k << endl
		<< "Does 5 less than determinant A\? " << r << endl
		<< "Does -5 less than determinant B\? " << d << endl
		<< "Does inverse matrix exist for A\? " << A.inverse_matrix() << endl
		<< "Does inverse matrix exist for B\? " << B.inverse_matrix() << endl;

	return 0;
}