#include <iostream>

using namespace std;

// 포인터연산
// *(포인터변수) : 간접연산자
// &(변수) : 주소연산자

// 덧셈연산 : +1 하면... 자료형의 크기만큼 더해진다.

// 정적배열
// int arr[상수] = {초기화};

// 가장 중요한 특성1 : 메모리에 일렬로 나열이되어있다.
// 	int arr[5] = { 1,2,3,4,5 };

// 2 : 배열의 이름은 포인터처럼 동작한다.

// 임의접근하는데 상수의 시간이 걸린다.

// 연산자
// [변수] : 임의접근연산자... 변수번 째 인덱스(index)에 접근

// 탐색 : 인덱스 
// 순회 : for

void PrintArr(int* arr, int size)
{
	for (int i = 0; i < size; i++)
	{
		cout << arr[i] << endl;
	}
}

int main()
{
	//            0x10
	int arr[5] = { 3,2,1,4,5 };

	int* ptr = &arr[0]; // 0x10
	cout << *(ptr + 1) << endl; // 0x14
	cout << arr[1] << endl;

	cout << sizeof(arr) << endl;
	int size = sizeof(arr) / sizeof(int);
	cout << "Count : " << size << endl;

	PrintArr(arr, size);

	return 0;
}