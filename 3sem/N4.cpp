#include <iostream>

using namespace std;

class Treap;

class TreapNode
{
	int key;
	int prior;

	TreapNode* parent;
	TreapNode* leftChild;
	TreapNode* rightChild;

public:
	TreapNode(int k = 0, int p = 0)
	{
		key = k;
		prior = p;

		parent = leftChild = rightChild = NULL;
	}

	TreapNode* findHigherPrior()
	{
		return !parent ? this : parent->findHigherPrior();
	}

	friend class Treap;
	friend class iter;
};

class Treap
{
	TreapNode* root;

public:
	Treap(TreapNode* P = NULL)
	{
		root = P;
	}

	void merge(Treap& R)
	{
		if (!root || !R.root)
			return;
		else if (root->prior >= R.root->prior)
		{
			if (!root->rightChild)
			{
				root->rightChild = R.root;
				R.root->parent = root;

				return;
			}

			Treap(root->rightChild).merge(R);
		}
		else
		{
			Treap B(R.root->leftChild);

			R.root->leftChild = root;
			R.root->parent = root->parent;
			root->parent = R.root;

			if (R.root->parent != NULL)
				R.root->parent->rightChild = R.root;

			if (!B.root)
				return;

			Treap(R.root->leftChild).merge(B);
		}
	}

	Treap* split(int x)
	{
		static TreapNode* sw = NULL;

		if (root->key <= x)
		{
			if (!root->rightChild)
			{
				Treap A(root->findHigherPrior());
				
				Treap arr[2];

				arr[0] = A;

				if (sw != NULL)
				{
					Treap B(sw->findHigherPrior());
					
					arr[1] = B;

					return arr;
				}

				arr[1] = Treap(NULL);

				return arr;
			}
			else if (root->rightChild->key > x)
			{
				TreapNode* p = root->rightChild;
				root->rightChild->parent = NULL;
				root->rightChild = NULL;

				Treap SW(sw);
				Treap P(p);
				P.merge(SW);

				sw = root;

				P.split(x);
			}
			else
				return Treap(root->rightChild).split(x);
		}
		else
		{
			if (!root->leftChild)
			{
				Treap A(root->findHigherPrior());

				Treap arr[2];

				arr[0] = A;

				if (sw != NULL)
				{
					Treap B(sw->findHigherPrior());

					arr[1] = B;

					return arr;
				}

				arr[1] = Treap(NULL);

				return arr;
			}
			else if (root->leftChild->key < x)
			{
				TreapNode* p = root->leftChild;
				root->leftChild->parent = NULL;
				root->leftChild = NULL;

				Treap SW(sw);
				Treap P(p);
				P.merge(SW);

				sw = root;

				P.split(x);
			}
			else
				return Treap(root->leftChild).split(x);
		}
	}

	TreapNode* min() const
	{
		return !root->leftChild ? root : Treap(root->leftChild).min();
	}

	TreapNode* max() const
	{
		return !root->rightChild ? root : Treap(root->rightChild).max();
	}

	int size() const
	{
		int count = 0;
		Treap R(root);

		Treap::iter it;

		TreapNode* maxR = R.max();
		for (it = R.min(); it != maxR; ++it, count++);

		return ++count;
	}

	class iter
	{
		TreapNode* ptr;
	public:
		iter()
		{
			ptr = NULL;
		}

		iter operator=(TreapNode* p)
		{
			if (!p)
				return iter();

			ptr = p;
			
			return *this;
		}

		bool operator!=(const TreapNode* p) const
		{
			return ptr != p;
		}

		TreapNode* operator*() const
		{
			return ptr;
		}

		iter operator++()
		{
			if (!ptr->rightChild)
			{
				if (!ptr->parent)
					return *this;

				else if (ptr->parent->key >= ptr->key)
					ptr = ptr->parent;

				else
				{
					if (ptr == Treap(ptr->findHigherPrior()).max())
						return *this;

					while (ptr->key > ptr->parent->key)
						ptr = ptr->parent;

					ptr = ptr->parent;
				}
			}
			else
				ptr = Treap(ptr->rightChild).min();

			return *this;
		}
	};
};

int main()
{
	TreapNode A(2, 5), B(4, 3), C(5,6);
	Treap SA(&A), SB(&B), SC(&C);
	SA.merge(SB);
	SA.merge(SC);

	cout << SC.size();

	
	
}