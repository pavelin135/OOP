#include <iostream>
#include <vector>
#include <string>
#include <queue>

using namespace std;

//////////////////////////////////////
//									//
//				N 3.1				//
//									//	
//////////////////////////////////////


class Laptop
{
	string CPU;
	unsigned int memory_size;
public:
	Laptop()
	{
		CPU = "";
		memory_size = 0;
	}

	Laptop(const string& S, unsigned int a)
	{
		CPU = S;
		memory_size = a;
	}

	void setCPU(const string& S) { CPU = S; }
	void setMemorySize(unsigned int a) { memory_size = a; }

	string getCPU()	const { return CPU; }
	unsigned int getMemorySize() const { return memory_size; }

	bool operator<(const Laptop& B) const
	{
		return this->getMemorySize() < B.getMemorySize();
	}
};

ostream& operator<<(ostream& f, const Laptop& A)
{
	f << A.getMemorySize();

	return f;
}


struct cmp_Laptop
{
	bool operator() (const Laptop& A, const Laptop& B)
	{
		return A < B;
	}
};


template <class T, class S>
void print_queue(priority_queue<T, vector<T>, S>& q)
{
	while (!q.empty())
	{
		cout << q.top() << endl;
		q.pop();
	}
}


//////////////////////////////////////
//									//
//				N 3.2				//
//									//
//////////////////////////////////////

template <class T>
class Heap
{
	T* arr;

	int len;  //current length
	int size; //amount of pits

	void LiftRight(int i)
	{
		if (!len || !size || !arr || i < 0 || i >= len || len == size)
			return;

		for (int c = len - 1; c >= i; c--)
		{
			arr[c + 1] = arr[c];
		}
	}

	void LiftLeft(int i)
	{
		if (!len || !size || !arr || i < 0 || i >= len || len == size)
			return;

		for (; i < len - 1; i++)
		{
			arr[i] = arr[i + 1];
		}
	}

public:
	Heap()
	{
		arr = NULL;
		len = 0;
		size = 0;
	}

	Heap(int s)
	{
		if (s < 1)
			return;

		size = s;

		arr = new T[size];

		if (!arr)
			return;

		len = 0;
	}

	~Heap()
	{
		if (arr != NULL)
			delete[] arr;
	}

	void add_elem(const T& e)
	{
		if (len == size)
			return;

		int i = 0;
		for (; i < len && e < arr[i]; i++);

		LiftRight(i);

		len++;

		arr[i] = e;
	}

	void del_elem(int i)
	{
		if (i < 0 || i >= len)
			return;
		else if (len == 1)
		{
			arr[i] = T();
		}
		else
		{
			LiftLeft(i);
		}

		len--;
	}

	T get_elem(int i) const
	{
		return i < 0 || i >= len ? T() : arr[i];
	}

	T get_left_child(int i) const
	{
		int I = 2 * i + 1;

		return I < 0 || I >= len ? T() : arr[I];
	}

	T get_right_child(int i) const
	{
		int I = 2 * i + 2;

		return I < 0 || I >= len ? T() : arr[I];
	}

	void print_heap() const
	{
		for (int i = 0; i < len; i++)
			cout << arr[i] << endl;
	}
};

  
int main()
{
	//N 3.1
	priority_queue<Laptop, vector<Laptop>, cmp_Laptop> q;

	Laptop L1("A", 8), L2("B", 16), L3("C", 4);

	q.push(L1); q.push(L2); q.push(L3);

	print_queue(q);
	
	cout << endl;

	//N 3.2

	Heap<Laptop> H(100);

	H.add_elem(L1);
	H.add_elem(L2);
	H.add_elem(L3);

	H.print_heap();
	
	cout << endl << H.get_right_child(0);
}
