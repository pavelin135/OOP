#include <iostream>

template <class T>
class Queue
{
	Queue* FirstElem;
	Queue* LastElem;
	Queue* NextElem;

	T elem;

public:
	Queue(const T A)
	{
		FirstElem = LastElem = this;

		elem = A;
		NextElem = NULL;
		
	}

	void push(const T A)
	{
		Queue<T>* ptr = new Queue<T>(A);

		if (ptr == NULL)
			return;

		LastElem->NextElem = ptr;
		LastElem->NextElem->FirstElem = this;
		LastElem = LastElem->NextElem;
	}

	T pop()
	{
		T A = elem;

		if (NextElem == NULL)
			return A;

		elem = NextElem->elem;


		LastElem = NextElem->NextElem == NULL ? this : LastElem;

		Queue<T>* ptr = NextElem;

		NextElem = NextElem->NextElem;

		ptr->NextElem = NULL;

		delete ptr;

		return A;
	}

	void print() const
	{
		std::cout << elem << '\n';
		if (!NextElem)
			return;
		
		NextElem->print();
	}

	~Queue()
	{
		if (NextElem != NULL)
			delete NextElem;
	}

	template <class T>
	friend Queue<T>* filter(const Queue<T>& Q, T P);

	template <class T>
	friend Queue<T>* operator++ (const Queue<T>& Q);

	template <class T>
	friend T operator* (const Queue<T>& Q);

};

template <class T>
Queue<T>* filter(const Queue<T>& Q, T P)
{
	Queue<T>* new_Q = NULL;

	for (const Queue<T>* i = &Q; i->NextElem != NULL; i = i->NextElem)
	{
		if (P == i->elem)
		{
			if (!new_Q)
			{
				new_Q = new Queue<T>(P);

				if (new_Q == NULL)
					return NULL;

			}
			else
				new_Q->push(P);
		}
	}

	return new_Q;
}

template <class T>
Queue<T>* operator++ (const Queue<T>& Q)
{
	return Q.NextElem;
}

template <class T>
T operator* (const Queue<T>& Q)
{
	return Q.elem;
}


int main()
{
	Queue<int> M(5);

	M.push(7);
	M.push(1);
	M.pop();
	M.push(12);

	M.print();

	
}
