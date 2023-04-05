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
		len = 0;
		p = new char[capacity];
		if (p == NULL)
		{
			capacity = 0;
			return;
		}

		for (len; ptr[len] != '\0'; len++);


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

	BaseString(int dim)
	{
		len = 0;
		capacity = dim;
		p = new char[capacity];
		if (p == NULL)
		{
			capacity = 0;
			return;
		}

	}

	~BaseString()
	{
		if (p != NULL)
		{
			delete[] p;
		}
		len = 0;
	}
	
	
	BaseString& operator=(BaseString& str)
	{
		char* ps = new char[str.capacity];
		if (ps == NULL)
		{
			return str;
		}

		for (int i = 0; i < len; i++)
		{
			ps[i] = str.p[i];
		}

		len = str.len;
		capacity = str.capacity;
		delete[] p;
		p = ps;

		return *this;
	}

	int LongestWordIndex()
	{
		int maxWord = 0;
		int index = 0;
		for (int i = 0; p[i] != '\0'; i++)
		{
			int k = i;
			for (k; !((p[k] == ' ') || (p[k] == '\0')); k++);

			int currentWord = k - i;

			if (currentWord > maxWord)
			{
				index = i;
				maxWord = currentWord;
				i = k - 1;
			}
		}
		return index;
	}
};



int main()
{
	BaseString a("asd"), b("aszx");
	a = b;
	
}