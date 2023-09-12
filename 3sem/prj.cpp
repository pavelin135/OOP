#include <iostream>
#include <list>

using namespace std;

template <class T>
void push(list<T>& ls, T elem)
{
	list<T> ptr = ls.begin();

	for (ptr; ptr != ls.end(); ptr++)
		if (*ptr > elem)
			break;
	ls.insert(ptr, elem);
}

template <class T>
T pop(list<T>& ls)
{
	T A = ls.end();
	ls.pop_back();
	return A;
}

int main()
{

}