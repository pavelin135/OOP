#include <iostream>
#include <stdexcept>
using namespace std;

class MyArrayParent
{
protected:
	int capacity;
	int count;
	double* ptr;
	bool Check_ptr(double* a)
		return a == NULL
public:

	MyArrayParent(int Dimension)
	{
		ptr = new double[Dimension];
		if (Check_ptr(ptr))
			return;
		capacity = Dimension;
		count = 0;
	}

	MyArrayParent(double* arr, int len)
	{
		ptr = new double[len];
		if (Check_ptr(ptr))
			return;
		capacity = len;
		count = len;
		for (int i = 0; i < len; i++)
		{
			ptr[i] = arr[i];
		}
	}

	MyArrayParent(const MyArrayParent& V)
	{
		capacity = V.capacity;
		count = V.count;
		ptr = new double[capacity];
		if (Check_ptr(ptr))
			return;
		for (int i = 0; i < count; i++)
		{
			ptr[i] = V.ptr[i];
		}
	}

	~MyArrayParent()
	{
		if (ptr != NULL)
		{
			delete[] ptr;
			ptr = NULL;
		}
	}

	int Capacity() { return capacity; }
	int Size() { return count; }

	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
		{
			return ptr[index];
		}
		else
		{
			throw std::invalid_argument("received wrong index");
		}
		return -1;
	}

	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
		{
			ptr[index] = value;
		}
		else
		{
			throw std::invalid_argument("received wrong index");

		}
		
	}

	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
			
		}
		return;
	}

	void RemoveLastValue()
	{
		count -= count > 0 ;
		return;
	}

	int IndexOf(double a)
	{
		for (int i = 0; i < count; i++)
		{
			if (ptr[i] == a)
				return i;
		}
		return -1;
	}

	double& operator[](int index)
	{
		return ptr[index];
	}

	MyArrayParent& operator=(const MyArrayParent& V)
	{
		capacity = V.capacity;
		count = V.count;
		delete[] ptr;
		ptr = new double[capacity];
		for (int i = 0; i < count; i++)
		{
			ptr[i] = V.ptr[i];
		}
		return *this;
	}

};


class MyArrayChild : public MyArrayParent
{
public:
	MyArrayChild(int Dimension) : MyArrayParent(Dimension)			{ cout << "\nMyArrayChild constructor"; }
	
	MyArrayChild(double* arr, int len) : MyArrayParent(arr, len)	{ cout << "\nMyArrayChild constructor"; }
	
	MyArrayChild(const MyArrayParent& V) : MyArrayParent(V)			{ cout << "\nMyArrayChild constructor"; }

	~MyArrayChild()	{ cout << "\nMyArrayChild destructor\n"; }

	void RemoveAt(int index)
	{
		int cnt = Size();
		if (index >= 0 && index < cnt)
		{
			for (int i = index; i < cnt - 1; i++)
			{
				SetComponent(i, GetComponent(i + 1));
			}
			RemoveLastValue();
		}
		else
		{
			return;
		}
	}

	void InserAt(double value, int index)
	{
		int cnt = Size();
		if (index >= 0 && index < cnt && Capacity() > cnt)
		{
			for (int i = cnt; i > index; i--)
			{
				SetComponent(i, GetComponent(i - 1));
			}
			SetComponent(index, value);
		}
		else
			return;
	}

	MyArrayChild Sort()
	{
		MyArrayChild C(*this);

		int cnt = C.Size(),
			j = 0;

		bool chek_first_minus = 1;

		for (int i = 0; i < cnt; i++)
		{
			if (C.GetComponent(i) < 0)
			{
				if (chek_first_minus)
				{
					j = i;
					chek_first_minus = 0;
					continue;
				}

				int k = i - 1;
				j++;
				while (k > j)
				{
					double t = C.GetComponent(k);
					C.SetComponent(k, C.GetComponent(j));
					C.SetComponent(j, t);
					k--;
					j++;
				}
				j = i;
			}
		}
		return C;
	}
};


class MySortedArray : public MyArrayChild
{
public:
	MySortedArray(int Dimension) : MyArrayChild(Dimension) { cout << "\nMySortedArray constructor"; }

	MySortedArray(double* arr, int len) : MyArrayChild(arr, len) { cout << "\nMySortedArray constructor"; }

	MySortedArray(const MyArrayParent& V) : MyArrayChild(V) { cout << "\nMySortedArray constructor"; }

	~MySortedArray() { cout << "\nMySortedArray destructor\n"; }

	MyArrayChild Sort()
	{
		cout << "\nit already sorted\n";
		return *this;
	}
};


int main(int argc, char** argv)
{
	
	return 0;
}
