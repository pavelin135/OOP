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
		if (ptr == NULL)
		{
			capacity = 0;
			len = 0;
			return;
		}
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
		if (dim < 0)
		{
			capacity = 0;
			len = 0;
			return;
		}
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
		capacity = 0;
	}
	
	
	BaseString& operator=(const BaseString& str)
	{
		if(this!=&str)
		{
		char* ps = new char[str.capacity];
		if (ps == NULL)
			return str;

		for (int i = 0; i < str.len; i++)
			ps[i] = str.p[i];

		len = str.len;
		capacity = str.capacity;

		delete[] p;
		p = ps;
		}
		return *this;
	}

	BaseString& operator=(const char* ptr)
	{
		if (ptr == NULL)
		{
			return *this;
		}
		
		int newlen = 0;
		
		for (newlen; ptr[newlen] != '\0'; newlen++);
		
		int newcapacity = newlen > capacity ? newlen : capacity;
		
		char* ps = new char[newcapacity];
		
		if (ps == NULL)
			return *this;
		
		for (int i = 0; i < newlen; i++)
			ps[i] = ptr[i];
		
		capacity = newcapacity;
		
		delete[] p;
		p = ps;

		return *this;
	}
};

class String : public BaseString
{
public:
	String(const char* ptr) : BaseString(ptr){}
	String(int dim) : BaseString(dim){}

	int LongestWordIndex()
	{
		int maxWord = 0;
		int index = 0;
		for (int i = 0; i < len; i++)
		{
			int k = i;
			for (k; !((p[k] == ' ') || (k == len)); k++);

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
	String a("asd asdasd asd");
	std::cout << a.LongestWordIndex();
}
