#include <iostream>
using namespace std;

class A1
{
public:
	A1(int n)
	{
		a1 = n;
	}

	virtual void print()
	{
		cout << "class A1\n";
	}

	virtual void show()
	{
		cout << "a1\n";
	}
protected:
	int a1;
};

class B1 : virtual public A1
{
public:
	B1(int n, int nA1) : A1(nA1)
	{
		b1 = n;
	}

	virtual void print()
	{
		cout << "class B1\n";
	}

	virtual void show()
	{
		cout << "a1, b1\n";
	}
protected:
	int b1;
};

class B2 : virtual public A1
{
public:
	B2(int n, int nA1) : A1(nA1)
	{
		b2 = n;
	}

	virtual void print()
	{
		cout << "class B2\n";
	}

	virtual void show()
	{
		cout << "a1, b2\n";
	}
protected:
	int b2;
};

class C1 : public B1, public B2
{
public:
	C1(int n, int nB1, int nB2, int nA1) : A1(nA1), B1(nB1, nA1), B2(nB2, nA1)
	{
		c1 = n;
	}
	virtual void print()
	{
		cout << "class C1\n";
	}

	virtual void show()
	{
		cout << "c1, b1, b2\n";
	}
protected:
	int c1;
};

class C2 : public B1, public B2
{
public:
	C2(int n, int nB1, int nB2, int nA1) : A1(nA1), B1(nB1, nA1), B2(nB2, nA1)
	{
		c2 = n;
	}
	virtual void print()
	{
		cout << "class C2\n";
	}

	virtual void show()
	{
		cout << "c2, b1, b2\n";
	}
protected:
	int c2;
};

int main()
{
	C1 var(1, 2, 3, 4);
	A1* pv = &var;
	pv->print();
	pv->show();
	return 0;
}