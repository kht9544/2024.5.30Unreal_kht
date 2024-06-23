#include <iostream>

using namespace std; // standard library

// 그러면 우리가 저장은 0,1은 알겠다.
// bit : 0,1
// byte : 8bit

// 근데 내가 어떤 걸 저장할 수 있을까?
// 자료형(DataType)
// 변수 (바구니)
// 변수 선언방법
// (자료형) (변수이름) = 초기화

// 정수형
// short 2바이트, 2^16 (-2^15 ~ 2^15 -1) => (-32768 ~ 32767)
// int  4바이트, 2^32 (-2^31 ~ 2^31-1) => (-21억 ~ 21억)
// long long(int64) 8바이트, 2^64 (-2^63 ~ 2^63-1)

// 음의 정수 만드는 방법(2의 보수법)
// 1. 비트를 모두 뒤바꾼다.
// 2. +1 을 한다.

// 정수의 오버플로우

// 실수형
// float 4바이트
// double 8바이트
// 부동소수점
// float -> 32비트
// (부호 1) + (지수 8) + (유효숫자 23)

// 논리형
// bool 1바이트
// true 1 / false 0
// 0을 저장하면 false, 그 외에 모든 것이 다 true

// 문자형
// char : 1바이트
// 256가지의 알파벳, 문자를 표현할 수 있다. => 아스키코드
// 유니코드 (wchar)
// - UTF-8  : 알파벳, 숫자(1바이트) / 한글, 중국어(3바이트)
// - UTF-16 : 알파벳, 숫자, 한글, 중각어(2바이트) / 고대문자(4바이트)

// Escape Sequence
// \n : 줄바꿈
// \t : Tab
// \" : " 표시
// \0 : NULL 표시

// 부호부가 없는 자료형
unsigned short u_aShort = 1; // 0 ~ 2^16 -1
unsigned int u_aInt = 5; // 0 ~ 2^32 -1

// 사용자 정의 자료형
struct Pos
{
	int x;
	int y;
};

int main() // 메인 함수
{
	// 정수형
	short aShort = -32768 - 1; // 정수형 오버플로우가 일어난다.
	int aInt = 1;
	__int64 aInt64 = 241313;

	// 실수형
	float aFloat = 1.25f;
	double aDouble = 1.222;

	// 논리형
	bool aBool = -1;

	// 문자형
	char aChar = 97;
	
	// 사용자 정의 자료형
	Pos aPos;
	aPos.x = 1;
	aPos.y = 2;

	Pos bPos;
	bPos.x = 3;
	bPos.y = 3;

	// 출력부
	cout << "Pos자료형의 크기" << sizeof(aPos) << endl;

	int sum = aInt + 5;

	return 0;
}