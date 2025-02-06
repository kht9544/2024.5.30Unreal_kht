#include <iostream>

using namespace std;


void PrintArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	int arr[5] = { 3,2,1,4,5 };

	int* ptr = &arr[0]; 
	cout << *(ptr + 1) << endl; 
	cout << arr[1] << endl;

	cout << sizeof(arr) << endl;
	int size = sizeof(arr) / sizeof(int);
	cout << "Count : " << size << endl;

	PrintArr(arr, size);

	return 0;
}