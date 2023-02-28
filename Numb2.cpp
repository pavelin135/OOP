#include <iostream>
using namespace std;

class MyArarayParent
{
protected:
	int capacity;
	int count;
	double* ptr;		
public:
	
	MyArrayParent(int Dimension)
	{
		ptr = new double[Dimension];
		capacity = Dimension;
		count = 0;
	}
	
	MyArrayParent(double* arr, int len)
	{
		ptr = new double[len];
		capacity = len;
		count = len;
		for (int i = 0; i < len; i++)
		{
			ptr[i] = arr[i];
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
	
	int Capacity(){return capacity;}
	int Size(){return count;}
	
	double GetComponent(int index)
	{
		if (index >= 0 && index < count)
		{
			return ptr[index];
		}
		return -1;
		//////
	}
	
	void SetComponent(int index, double value)
	{
		if (index >= 0 && index < count)
		{
			ptr[index] = value;
		}
		//////
	}
	
	void push(double value)
	{
		if (count < capacity)
		{
			ptr[count] = value;
			count++;
		}
		else
			return;
	}
	
	void RemoveLastValue()
	{
		if (count > 0)
		{
			count--;
		}
		else
			return;
	}
	
	double& operator[](int index)
	{
		return ptr[index];
	}
	
	MyArrayParent& operator=(const MyArrayParent& V)
	{
		//////
	}
	
	MyArrayParent(const MyArrayParent& V)
	{
		capacity = V.Capacity();
		count = V.Count();
		ptr = new double[capacity];
		for (int i = 0; i < count; i++)
		{
			ptr[i] = V[i];
		}
	}
};

int main(int argc, char** argv) {
	
	return 0;
}
