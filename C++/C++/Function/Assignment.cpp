#include <iostream>

using namespace std;

// 자료형
// 변수, 선언방법
// 연산자
// -- 비트플래그

// 메모리 4영역
// - 코드(Text)영역
// - Data 영역
//  => 전역변수, 정적변수
//  => 생성주기 : 생성(프로그램 시작) / 소멸(프로그램 종료)
// - Heap 영역
// - Stack 영역
//  => 지역변수, 매개변수, 반환주소값
//  => 생성주기 : 함수 호출 시에 할당되고, 함수 종료시에 해제된다.
//  => 단점 : 다른 지역에서는 쓰지못한다 , 지역 끝나면 해당 변수는 유효하지 않다.

int aInt = 0;
short aShort = 1;

float aFloat = 4.0f;

char aChar = 1;

int HelloWorld(int arg/*매개변수*/)
{
	int hello = 5;
	aChar = 2;

	return 0;
}

int main()
{ // 지역
	int bInt = 2;
	float bFloat = 1.1f;

	{
		int cInt = 2;
		bInt = 3;
	}

	return 0;
} // 지역 끝