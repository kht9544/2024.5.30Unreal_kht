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

// 순차정렬
// [5][2][1][3][4]

// i = 0
// [5] [2] [1][3][4]
// [2] [5] [1][3][4] => Swap

// [2][5] [1] [3][4]
// [1][5][2][3][4] => Swap

// [1][5][2][3][4]
// [1][5][2][3][4]

// [1] [5] [2] [3][4]
// [1][2][5][3][4] => Swap

// [1][2] [5] [3] [4]
// [1][2] [3] [5] [4] => Swap

// [1][2][3][4][5] => Swap

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

// 선택정렬
// [5][2][1][3][4] best
// i = 0 best = 0      값(인덱스)
// [5][2][1][3][4] best 5(0) j = 0
// [5][2][1][3][4] best 2(1) j = 1
// [5][2][1][3][4] best 1(2) j = 2
// [5][2][1][3][4] best 1(2) j = 3
// [5][2][1][3][4] best 1(2) j = 4
// Swap => [1][2][5][3][4]

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