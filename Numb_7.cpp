#include <iostream>
#include <fstream>
using namespace std;

template <class T>
void sortBubble(T arr[], int dim)
{
	for (int i = 0; i < dim - 1; i++)
	{
		for (int k = 0; k < dim - i - 1; k++)
		{
			if (arr[k + 1] > arr[k])
			{
				T t = arr[k];
				arr[k] = arr[k + 1];
				arr[k + 1] = t;
			}
		}
	}
}

template <class T> void Mix(T arr[], int left, int mid, int right);

template <class T> void sortMix(T arr[], int left, int right);

template <class T>
void sortMerg(T arr[], int left, int right)
{
	sortMix(arr, left, right);

	Mix(arr, left, right, right + 1);
}

template <class T>
void sortMix(T arr[], int left, int right)
{
	if (left + 1 >= right)
		return;

	int mid = (left + right) / 2;

	sortMix(arr, left, mid);
	sortMix(arr, mid, right);
	Mix(arr, left, mid, right);
}

template <class T> void Mix(T arr[], int left, int mid, int right)
{
	int x1 = 0,
		x2 = 0;
	T* a = new T[right - left];
	if (a == NULL)
		return;


	while (left + x1 < mid && mid + x2 < right)
	{
		if (arr[left + x1] < arr[mid + x2])
		{
			a[x1 + x2] = arr[left + x1];
			x1++;
		}
		else
		{
			a[x1 + x2] = arr[mid + x2];
			x2++;
		}
	}

	for (x1; left + x1 < mid; x1++)
		a[x1 + x2] = arr[left + x1];

	for (x2; mid + x2 < right; x2++)
		a[x1 + x2] = arr[mid + x2];

	for (int i = 0; i < x1 + x2; i++)
		arr[left + i] = a[i];

	delete[] a;
}



int main()
{
	fstream fo("INPUT.txt"),
		fi("OUTPUT.txt");
	if (!fo.is_open() || !fi.is_open())
		return -1;
	const int S = 5;

	int arr[S];

	for (int i = 0; i < S; i++)
		fo >> arr[i];

	sortMerg(arr, 0, S - 1);

	for (int i = 0; i < S; i++)
		fi << arr[i] << ' ';

}