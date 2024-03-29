﻿#include <iostream>
#include <string>
#include <list>

using namespace std;

class SuperHero
{
	string Nick;
	string Name;
	int Birth;
	bool sex;
	string Ability;
	string Sickness;
	int amount_victories;
	int rate;
public:
	SuperHero()
	{
		Nick = Name = Ability = Sickness = "None";
		sex = 0;
		Birth = amount_victories = rate = 0;
	}

	void setRate(int n)
		rate = n;

	void setName(const string& S)
		Name = S;

	void setAbility(const string& S)
		Ability = S;


	int getRate()
		return rate;
	
	string getName()
		return Name;

	string getAbility()
		return Ability;
	

};

class Fraction
{
	int A;
	int B;
public:
	Fraction()
	{
		A = 0;
		B = 1;
	}

	void setFraction(int a, int b)
	{
		if (b == 0)
			return;

		A = a;
		B = b;
	}

	int* getFraction() const
	{
		int* ARR = new int[2];

		*ARR = A;
		*(ARR + 1) = B;

		return ARR;
	}

	bool operator== (int N)
	{
		return A == N ? true : false;
	}
};

template <class T>
list<T>* filter(const list<T>& ls, int P)
{
	list<T>* L = new list<T>;

	if (!L)
		return NULL;
		
	list<Fraction>::iterator ptr = ls.begin();

	for (ptr; ptr != ls.end(); ptr++)
	{
		Fraction F = *ptr;
		if (F == P)
			L->push_back(F);
	}

	return L.begin() == L.end() ? NULL : L;
}


template <class T>
void push(list<T>& ls, const T& elem)
{
	list<Fraction>::iterator ptr = ls.begin();

	for (ptr; ptr != ls.end(); ptr++)
		if (*ptr > elem)
			break;
	ls.insert(ptr, elem);
}

template <class T>
SuperHero pop(list<T>& ls)
{
	list<Fraction>::iterator ptr = ls.end();

	SuperHero H = *ptr;

	ls.pop_back();

	return H;
}

int main()
{
	list<Fraction> LS;
	Fraction  a, b, c;

	a.setFraction(1, 2);
	b.setFraction(2, 3);
	c.setFraction(1, 3);

	LS.push_back(a);
	LS.push_back(b);
	LS.push_back(c);

	list<Fraction> LS_new = *filter(LS, 1);

	list<Fraction>::iterator ptr = LS_new.begin();

	for (ptr; ptr != LS_new.end(); ptr++)
	{
		Fraction F = *ptr;

		cout << *F.getFraction() << '/' << *(F.getFraction() + 1) << endl;
	}


}
