#include <iostream>

class BaseString
{
protected:
	char* p;
	int len;
	int capacity;
public:
	BaseString(const char* ptr)
	{
		capacity = 256;
		p = new char[capacity];
		if (p == NULL)
		{
			capacity = 0;
			return;
		}

		for (int i = 0; ptr[i] != '\0'; i++) len++;
		len++;


		if (len > capacity)
		{
			capacity = 0;
			len = 0;
			return;
		}

		for (int i = 0; i < len; i++)
		{
			p[i] = ptr[i];
		}
	}

	BaseString(int capas)
	{
		capacity = capas;
		p = new char[capacity];
		if (p == NULL)
		{
			capacity = 0;
			return;
		}

		len = 0;
	}

	~BaseString()
	{
		if (p != NULL)
		{
			delete[] p;
		}
		len = 0;
	}

	

	BaseString operator= (const BaseString& str)
	{
		char* ps = p;
		int ncapacity = capacity;
		int nlen = len;

		capacity = str.capacity;
		len = str.len;

		delete[] p;
		p = new char[capacity];
		if (p == NULL)
		{
			p = ps;
			capacity = ncapacity;
			len = nlen;
			return str;
		}
		
		for (int i = 0; i < len; i++)
		{
			p[i] = str.p[i];
		}

		return *this;
	}

	int LongestWordIndex()
	{
		int maxWord = 0;
		int index = 0;
		for (int i = 0; i != '\0'; i++)
		{
			int s = 0;
			int k = 0;
			for(k; p[i] != (' ' || '\0'); k++)
			{
				s++;
			}

			if (s > maxWord)
			{
				maxWord = s;
				index = i;
				i += k;
			}
		}
		return index;
	}
};


int main()
{
	
	char c[5] = "a cd";
	BaseString a(c);
	std::cout << a.LongestWordIndex();
}