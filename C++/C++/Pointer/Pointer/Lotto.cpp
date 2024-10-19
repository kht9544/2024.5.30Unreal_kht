#include <iostream>

using namespace std;

int lotto[45] = {};

void Swap(int& a, int& b);
void Shuffle(int arr[], int size, int count);
void SquentialSort(int arr[], int begin, int end);
void SelectSort(int arr[], int begin, int end);
void PrintArr(int arr[], int size);

void Swap(int& a, int& b)
{
	int temp = b;
	b = a;
	a = temp;

	cout << "Swap" << endl;
}

void Shuffle(int arr[], int size, int count)
{
	for (int i = 0; i < count; i++)
	{
		int a = rand() % 45;
		int b = rand() % 45;

		std::swap(arr[a], arr[b]);
	}
}

void SetLotto(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		arr[i] = i + 1;
	}

	Shuffle(arr, size, 10000);
	SelectSort(arr, 0, 7);
}

void PrintArr(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}


void SquentialSort(int arr[], int begin, int end)
{
	int size = end - begin;
	for (int i = 0; i < size - 1; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (arr[i] > arr[j])
				Swap(arr[i], arr[j]);
		}
	}
}

void SelectSort(int arr[], int begin, int end)
{
	int size = end - begin;
	for (int i = 0; i < size - 1; i++)
	{
		int best = i;
		for (int j = i + 1; j < size; j++)
		{
			if (arr[best] > arr[j])
			{
				best = j;
			}
		}

		if (best != i)
			Swap(arr[i], arr[best]);
	}
}

int main()
{
	srand(time(NULL));

	SetLotto(lotto, 45);

	PrintArr(lotto, 7);

	return 0;
}