#include <iostream>

using namespace std;

// 포인터 ... Pointer
// 가르키는 얘
// 주소를 담고있는 변수
// (자료형)* (포인터변수이름) = (초기화);
// (자료형) : 포탈을 타고 들어갔을 때 해당 자료형이 있을 것이다 라는 힌트

// 크기 : 32비트 운영체제 프로그램에서 4바이트, 64비트 운영체제 프로그램에서는 8바이트

// 연산자
// &(변수이름) : 주소연산자
// *(포인터변수) : 간접연산자... 포탈연산자

// void* : 타고들어가면 무슨 자료형이 있던 상관없다.

// 매개변수로 온 값
// Call by Value
void AddOne(int num)
{
	num++;
}

// 매개변수로 온 '주소'값
// Call by Address
void AddOne(int* ptr)
{
	(*ptr)++; // aInt ... + 1
}


int main()
{
	int aInt = 5;	   // 0x0102FF      5

	int* aPtr = &aInt; // 0x0213FF    0x0102FF 

	cout << "aInt의 주소" << &aInt << endl;
	cout << "aInt 변수가 들고 있는 값" << aInt << endl;
	cout << "aPtr의 주소" << &aPtr << endl;
	cout << "aPtr 변수가 들고 있는 값" << aPtr << endl;

	cout << *aPtr << endl; // 간접연산자... 포탈연산자
	*aPtr = 6;

	cout << aInt << endl;

	// void*
	void* vPtr = &aInt;
	
	aInt = 0;
	AddOne(&aInt);

	cout << aInt << endl;

	return 0;
}