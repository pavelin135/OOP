#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class LapTop
{
ptivate:
	string model;
	string processor;

	int RAM;
	int cost;
public:
	LapTop()
	{
		model = "model";
		processor = "proc";

		RAM = 0;
		cost = 0;
	}

	LapTop& operator= (const LapTop& A)
	{
		LapTop* ptr = &A;
		if (this == ptr)
			return *this
		model = A.model;
		processor = A.processor;

		RAM = A.RAM;
		cost = A.cost;

		return *this;
	}

	friend bool operator< (const LapTop& A, const LapTop& B);
	friend istream& operator>> (istream& f, LapTop& L);
	friend fstream& operator<< (fstream& f, const LapTop& L);
	friend fstream& operator>> (fstream& f, LapTop& L);
};

bool operator< (const LapTop& A, const LapTop& B)
{
	return (A.cost < B.cost ? 1 : 0);
}
istream& operator>> (istream& f, LapTop& L)
{
	cin >> L.model >> L.processor >> L.RAM >> L.cost;

	return f;
}

fstream& operator<< (fstream& f, const LapTop& L)
{
	if (!f.is_open())
		return f;

	f << L.model << endl << L.processor << endl << L.RAM << endl << L.cost << endl;
	return f;
}
fstream& operator>> (fstream& f, LapTop& L)
{
	if (!f.is_open())
		return f;

	char C;
	f >> L.model >> C >> L.processor >> C >> L.RAM >> C >> L.cost >> C;
	return f;
}

template <class T>
class BaseList
{
protected:
	T obj;
	
	BaseList* leftEl, * rightEl, * lastEl;
public:
	BaseList(const T& A)
	{
		obj = A;

		lastEl = this;
		leftEl = rightEl = NULL;
	}

	BaseList(const T& A, BaseList* leftEl, BaseList* rightEl, BaseList* lastEl)
	{
		obj = A;
		this->leftEl  = leftEl;
		this->rightEl = rightEl;
		this->lastEl  = lastEl;
	}

	~BaseList()
	{
		if (rightEl != NULL)
			delete rightEl;
	}



	void push(const T& A)
	{
		if (lastEl == NULL)
			return;

		BaseList* ptr = new BaseList(A, lastEl, NULL, NULL);
		if (ptr == NULL)
			return;
		lastEl = lastEl->lastEl = lastEl->rightEl = ptr->lastEl = ptr;
	}

	T pop()
	{
		if (lastEl == NULL)
			return obj;

		if (this != lastEl)
		{
			T N = lastEl->obj;
			BaseList* ptr = lastEl;
			lastEl->leftEl->rightEl = NULL;
			lastEl->leftEl->lastEl = lastEl->leftEl;
			lastEl = lastEl->leftEl;
			ptr->lastEl = ptr->leftEl = ptr->rightEl = NULL;
			delete ptr;
			return N;
		}
		else
		{
			lastEl = rightEl = leftEl = NULL;
			return obj;
		}
	}

	void insert(const T& A, int i)
	{
		if (i < 0) { return; }

		else if (i > 1)
		{
			if (rightEl == NULL)
				return;
			rightEl->insert(A, i - 1);
		}
		else if (i == 1)
		{
			BaseList* ptr = new BaseList(A, this, rightEl, lastEl);
			if (ptr == NULL)
				return;

			rightEl = ptr;
			ptr->rightEl->leftEl = ptr;
		}

		else if (i == 0)
		{
			if (rightEl != NULL)
			{
				BaseList* ptr = new BaseList(obj, this, rightEl, lastEl);
				if (ptr == NULL)
					return;

				obj = A;
				rightEl = ptr;
				ptr->rightEl->leftEl = ptr;
			}
			else
			{
				BaseList* ptr = new BaseList(obj, this, NULL, NULL);
				if (ptr == NULL)
					return;

				ptr->lastEl = ptr;
				lastEl = ptr;

				obj = A;
				rightEl = ptr;
			}
		}
	}

	bool remove(int i)
	{
		if (i < 0)
			return 0;

		else if (i > 0)
		{
			if (rightEl == NULL)
				return 0;
			if (rightEl->remove(i - 1))
			{
				if (leftEl == NULL)
					pop();
				return 1;
			}
		}

		else
		{
			if (rightEl == NULL)
			{
				if (leftEl == NULL)
					leftEl = rightEl = lastEl = NULL;
				else
					return 1;
			}

			else if (leftEl == NULL)
			{
				obj = rightEl->obj;
				BaseList* ptr = rightEl;
				
				if (rightEl->rightEl == NULL)
				{
					lastEl = this;
					rightEl = NULL;
				}

				else
				{
					lastEl = rightEl->lastEl;
					rightEl = rightEl->rightEl;

					ptr->rightEl->leftEl = this;

					ptr->lastEl = ptr->leftEl = ptr->rightEl = NULL;
				}
				delete ptr;
			}

			else
			{
				leftEl->rightEl = rightEl;
				rightEl->leftEl = leftEl;

				leftEl = rightEl = lastEl = NULL;
				
				delete this;
			}
			return 0;
		}
	}

	BaseList* find(const T& A) const
	{
		if (obj == A)
			return this;

		return (rightEl == NULL ? NULL : rightEl->find(A));
	}

	BaseList* find(const string& S) const
	{
		if (typeid(T) != typeid(LapTop))
			return NULL;

		LapTop N = obj;

		if (N.model == S)
			return this;

		return (rightEl == NULL ? NULL : rightEl->find(S));
	}

	BaseList* filter(bool f) const
	{
		if (typeid(T) != typeid(LapTop))
			return NULL;

		BaseList* ptr = new BaseList(obj);
		if (ptr == NULL)
			return NULL;

		for (BaseList* i = this->rightEl; i != NULL; i = i->rightEl)
		{
			ptr->push(obj);
			ptr->lastEl->obj = i->obj;
		}

		if (f)
		{
			for (BaseList* i = ptr; i != NULL; i = i->rightEl)
			{
				for (BaseList* j = i->rightEl; j != NULL; j = j->rightEl)
				{

					if (j->obj < i->obj)
					{
						LapTop t = j->obj;
						j->obj = i->obj;
						i->obj = t;
					}
				}
			}
		}
		else
		{
			for (BaseList* i = ptr; i != NULL; i = i->rightEl)
			{
				for (BaseList* j = i->rightEl; j != NULL; j = j->rightEl)
				{

					if (i->obj < j->obj)
					{
						LapTop t = j->obj;
						j->obj = i->obj;
						i->obj = t;
					}
				}
			}
		}
		

		return ptr;
	}

	void save(fstream& f)
	{
		if (!f.is_open())
			return;

		for (BaseList* i = this; i != NULL; i = i->rightEl)
			f << obj << endl;
	}

	void load(fstream& f)
	{
		if (!f.is_open())
			return;
		
		T L, N;
		f >> L;
		push(L);
		f >> N;
		while (L != '\n' && N != '\n')
		{
			L = N;
			f >> N;
			if (N != '\n')
				push(N);
		}
	}
};




int main()
{
	

	return 0;
}
