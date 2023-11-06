#include <iostream>
#include <string>
#include <list>
#include <cmath>

template <class T>
class Node
{
	Node<T>* parent;
	Node<T>* left;
	Node<T>* right;

	T elem;

	int height;


	
	bool checkH()
	{
		if ((left == NULL ? 0 : left->height) - (right == NULL ? 0 : right->height) > 1)
		{
			if ((left->right == NULL ? 0 : left->right->height) > (right == NULL ? 0 : right->height))
				left->right->rotate();

			left->rotate();
			return 1;
		}
		else if ((right == NULL ? 0 : right->height) - (left == NULL ? 0 : left->height) > 1)
		{
			if ((right->left == NULL ? 0 : right->left->height) > (left == NULL ? 0 : left->height))
				right->left->rotate();

			right->rotate();
			return 1;
		}
		else
			return 0;
	}



public:
	Node<T>(const T& A)
	{
		parent = left = right = NULL;

		elem = A;

		height = 1;
	}

	void upHeight()
	{
		Node<T>* ptr = this;
		for (ptr; ptr->parent != NULL; ptr = ptr->parent)
		{
			if (ptr->parent->checkH())
				break;

			else if (!ptr->parent->left || !ptr->parent->right)
			{
				ptr->parent->height++;
			}

			else if (ptr->parent->right == ptr)
			{
				if (ptr->parent->left->height >= ptr->height)
					break;

				ptr->parent->height++;
			}

			else
			{
				if (ptr->parent->right->height >= ptr->height)
					break;

				ptr->parent->height++;

			}
		}
	}


	void setElem(const T& A) { elem = A; }

	const T& getElem() const { return elem; }

	int getH() const { return height; }

	void setLeft(Node* P) { left = P; }

	void setRight(Node* P) { right = P; }

	void setParent(Node* P)
	{
		parent = P;
	}

	void rotate()
	{
		if (!parent)
			return;

		if (elem < parent->elem)
		{
			parent->left = right;

			right = parent;

			parent = parent->parent;

			if (parent != NULL)
			{
				if (parent->elem <= elem)
					parent->right = this;
				else
					parent->left = this;
			}

			right->parent = this;

			right->height = std::max(
				right->right == NULL ? 1 : right->right->height + 1,
				right->left == NULL ? 1 : right->left->height + 1
			);

			height = std::max(left == NULL ? 1 : left->height + 1, right->height + 1);
		}
		else
		{
			parent->right = left;

			left = parent;

			parent = parent->parent;

			if (parent != NULL)
			{
				if (parent->elem <= elem)
					parent->right = this;
				else
					parent->left = this;
			}

			left->parent = this;

			left->height = std::max(
				left->left == NULL ? 1 : left->left->height + 1,
				left->right == NULL ? 1 : left->right->height + 1
			);

			height = std::max(right == NULL ? 1 : right->height + 1, left->height + 1);
		}
	}

	Node* getLeft() const { return left; }
	Node* getRight() const { return right; }
	Node* getParent() const { return parent; }
};

template <class T>
class Tree
{
protected:

	void Add_R(Node<T>* P, Node<T>* Current)
	{

		if (P->getElem() < Current->getElem())
		{
			if (!Current->getLeft())
			{
				Current->setLeft(P);
				P->setParent(Current);
				P->upHeight();
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
				P->upHeight();
			}
			else
				Add_R(P, Current->getRight());


			return;
		}

	}

	void print(const Node<T>* Current) const
	{
		if (!Current)
			return;

		std::cout << '(' << Current->getElem() << " : " << Current->getH() << ')' << ' ';

		if (Current->getLeft() != NULL)
			print(Current->getLeft());

		std::cout << '\n';

		if (Current->getRight() != NULL)
			print(Current->getRight());
	}

	void Search(std::list<T>* LS, const T& A, Node<T>* ptr)
	{
		if (!ptr && !LS) return;

		if (!(ptr->getLeft() || ptr->getRight())) return;

		else if (A == ptr->getElem())
			LS->push_back(ptr->getElem());

		if (ptr->getElem() < A && ptr->getRight != NULL)
			Search(LS, A, ptr->getRight());

		else if (!(ptr->getElem() < A) && ptr->getLeft() != NULL)
			Search(LS, A, ptr->getLeft());

		return;
	}
public:

	Node<T>* root;

	Tree<T>() { root = NULL; }

	virtual void Add_R(Node<T>* P)
	{
		if (!P)
			return;

		if (!root)
		{
			root = P;
			return;
		}

		Add_R(P, root);
		findRoot();
	}

	void print() const
	{
		print(root);
	}

	Node<T>* findRoot()
	{
		Node<T>* ptr = root;
		for (ptr; ptr->getParent() != NULL; ptr = ptr->getParent());

		root = ptr;

		return root;
	}

	std::list<T>& operator[] (const T& A)
	{
		std::list<T> LS;
		Search(&LS, A, root);

		return LS;
	}
};


//------------------------//
//-------N 2.5------------//
//------------------------//


template <class T>
class SplayTree : public Tree<T>
{
public:

	SplayTree() : Tree<T>(this)
	{

	}

	void Add_R(Node<T>* P, Node<T>* Current)
	{
		std::cout << "mgm\n";

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


	Node<T>* Search(const T& A, const Node<T>* ptr) const
	{
		if (!ptr)
			return NULL;

		else if (ptr->getElem() == A)
			return ptr;

		if (ptr->getLeft() != NULL)
		{
			if (Search(A, ptr->getLeft())->getElem == A)
				return ptr;
		}

		if (ptr->getRight() != NULL)
		{
			if (Search(A, ptr->getRight())->getElem == A)
				return ptr;
		}

		return NULL;
	}

	Node<T>* operator[] (const T& val)
	{
		if (!root)
			return NULL;

		Node<T>* ptr = Search(val, root);

		if (!ptr)
			return;

		while (ptr->getParent() != NULL)
			ptr->rotate();
	}

};




int main()
{

}