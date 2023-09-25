#include <iostream>

template <class T>
class Node
{
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;

	T elem;
public:
	Node<T>(const T& A)
	{
		parent = left = right = NULL;

		elem = A;
	}

	void setElem(const T& A) { elem = A; }

	const T& getElem() { return elem; }

	void setLeft(Node* P) { left = P; }

	void setRight(Node* P) { right = P; }

	void setParent(Node* P) { parent = P; }

	Node* getLeft() { return left; }
	Node* getRight() { return right; }
	Node* getParent() { return parent; }
};

template <class T>
class Tree
{
	Node<T>* root;

	void Add_R(Node<T>* P, Node<T>* Current)
	{

		if (P->getElem() < Current->getElem())
		{
			if (!Current->getLeft())
			{
				Current->setLeft(P);
				P->setParent(Current);
			}
			else
				Add_R(P, Current->getLeft());

			return;
		}
		else
		{
			if (!Current->getRight())
			{
				Current->setRight(P);
				P->setParent(Current);
			}
			else
				Add_R(P, Current->getRight());

			return;
		}

	}

public:
	Tree<T>() { root = NULL; }

	void Add_R(Node<T>* P)
	{
		if (!P)
			return;

		if (!root)
		{
			root = P;
			return;
		}

		Add_R(P, root);
	}
};

int main()
{
	Tree<int> M;

	Node<int>* ptr1 = new Node<int>(3);
	Node<int>* ptr2 = new Node<int>(4);
	Node<int>* ptr3 = new Node<int>(5);

	M.Add_R(ptr1);
	M.Add_R(ptr2);
	M.Add_R(ptr3);
}