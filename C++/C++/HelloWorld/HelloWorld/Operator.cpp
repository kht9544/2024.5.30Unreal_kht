#include <iostream>

using namespace std;

// 연산자
// 사칙연산
// + - * / % => 자료형마다 다를 수 있다.

// 정수형
// + - *...
// / ... 몫을 반환
// 10 / 3 => 3

// % ... 나머지를 반환 => 순환 구조, 랜덤한 수를 만들 때
// 10 % 3 => 1

// 실수형
// + - *
// / ... 부동소수점의 오차를 주의

// = 대입연산자
// a = b : a에다가 b를 대입하고 a의 원본을 반환한다.
// += , -=, *=, /=

// 증감연산자
// ++, --
// aInt++ / aInt-- ... 후위연산자
// aInt = bInt++;
// => aInt에다 bInt를 먼저 대입하고 bInt를 1올린다.
// 
// ++aInt / --aInt ... 전위연산자
// aInt = ++bInt;
// => aInt에다 우선 bInt를 1올리고 그것을 대입한다.

// 비교연산자
// 반환자료형이 bool
// ==, !=, <, >, <=, >=
// == : 같으면 true 다르면 false
// != : 다르면 true 같으면 false !(==)
// a > b...

// 논리연산자
// 반환자료형이 bool
// !, &&, ||
// ! : not
// a && b : a가 true이고 b가 true면 true를 반환 그게아니면 false
// a || b : a,b 둘 중에 하나라도 true면 true 그게 아니면 false

// 비트연산자 : 부호없는 정수형과 쓰인다.
// &, |, ^, >>, <<
// a & b : 비트의 한자리수 씩 and
// ex) 1 & 3 : 1
// a | b : 비트의 한자리수 씩 or
// a ^ b : xor 연산... 비트가 서로 같지 않을 때 1, 같으면 0

// << : 왼쪽 Shift연산
// - *2가 된다.
// - 오른쪽비트는 항상 0으로 채워진다.

// >> : 오른쪽 Shift연산
// - 맨 오른쪽 비트는 버려지게 된다.
// - 부호가 있는 정수형이라면 왼쪽 부호비트는 유지된다.

// 비트플래그
// [기절][수면][에어본][무적]
unsigned char state = 0;
unsigned char sturn = 0b1000; // 1 << 3
unsigned char sleep = (1 << 2);
unsigned char airbone = 2;
unsigned char invinsible = 1;

// 비트마스크
// & (보고싶은 비트)

int main()
{
#pragma region 연산자
	int aInt = 10;
	int bInt = 3;
	int cInt = 0;

	cInt = (aInt + bInt) % bInt;
	cout << cInt << endl;

	float aFloat = 0.0f;
	float cFloat = 10.0f / aFloat;
	cout << cFloat << endl;

	aInt += 1; // aInt = aInt + 1

	cout << ++aInt << endl; // 12
	cout << aInt++ << endl; // 12
	cout << aInt << endl; // 13

	aInt = ++bInt;
	aInt = bInt++;
	cout << aInt << endl; // aInt:4 , bInt 5
	cout << (aInt > bInt) << endl; // false 0
	cout << ((aInt < bInt) > (aInt == bInt)) << endl; // true

	aInt = 2;
	bInt = 3;
	cInt = ++bInt;

	bool check1 = (aInt > bInt);
	bool check2 = (cInt != aInt);
	bool check3 = !check1;

	bool check4 = check3 || check2;
	bool check5 = check2 && (check3 || check4);

	cout << (1 & 2) << endl;
	cout << (1 | 3) << endl;
	// xor...
	// a ^ b ^ b = a... 암호학
	aInt = 1;
	bInt = 3;
	cInt = (aInt ^ bInt);
	cout << (cInt ^ bInt) << endl;

	unsigned char u_aChar = 3;
	unsigned char u_bChar = (1 << 4);
	unsigned char u_cChar = (u_aChar | u_bChar);
	unsigned char u_dChar = (1 << 3) | (1 << 2);
	unsigned char u_fChar = (u_cChar & u_dChar);
#pragma endregion

#pragma region 비트플래그
	state |= (sturn | sleep);
	if (state & sturn)
	{
		cout << "스턴상태입니다." << endl;
	}

	if (state & sleep)
	{
		cout << "수면 " << endl;
	}

	if (state & (sleep | sturn))
	{
		cout << "스턴 수면" << endl;
	}

#pragma endregion

	return 0;
}