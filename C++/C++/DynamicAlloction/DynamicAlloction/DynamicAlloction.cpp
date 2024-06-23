#include <iostream>

using namespace std;

#pragma region 복습
// - Class
// 1. 객체지향의 3속성
// -- 은닉성 (접근지정자)
// -- 상속성 (is - a관계 성립) ... Cat is A Animal(O)
// -- 다형성 (함수오버로딩, 함수오버라이딩...(가상함수))

// - 빠른 초기화... 느린 초기화 영역
// - 연산자 오버로딩
// - 멤버 함수 연습용 실습
// -- 멤버함수는 따로 독립적으로 호출X => 객체가 호출해줘야함... 멤버함수 호출은 무조건 객체가 필요하다

// 함수
// - 전역함수
// - 멤버함수
#pragma endregion

// 동적할당
// 메모리 4영역
// Code
// Data (전역변수, 정적변수)
// 생성주기 : 프로그램이 시작할 때 생성 / 프로그램이 종료될 때 해제된다.
// 단점 : 코드가 난잡해질 수 있다./ 메모리가 계속 할당되어 있다.
// Stack (지역변수, 매개변수, 반환주소값)
// 생성주기 : 함수가 호출되서 시작할 때 생성/ 함수가 끝났을 때 해제
// 단점 : 메모리를 제어할 수 없다.
// 
// Heap : 사용자 영역
// 생성주기 : 내 마음대로 제어할 수 있다.
// 단점 : 내 마음대로 제어할 수 있다. => 내가 실수하면 메모리 누수

// 동적할당하는 순서
// => 운영체제 커널영역 -> 힙에다가 1000바이트 할당하고 싶다. -> 운영체제에서 할당해주고 그 첫번 째 주소를 반환해준다.
// C 스타일
// malloc / free

// C++ 스타일
// new / delete
// new[] / delete []

class Player
{
public:
	Player()
	: _hp(0)
	{
	}

	// 가상함수
	// 가상함수테이블(vftable)을 이용하여 C++이 타입을 실행시간에 추론해준다.
	// => 할당되어있는 자료형에 맞는 함수를 호출해준다.
	// => 이 때 가상함수테이블은 가상함수가 하나 이상 존재하여야 생긴다.
	virtual void PrintInfo() { cout << "Player입니다." << endl; }

	int _hp;
};

class Knight : public Player
{
public:
	Knight()
	: Player()
	, _stamina(1)
	{

	}

	// 가상함수 오버라이딩
	virtual void PrintInfo() override { cout << "Knight입니다." << endl; }

	int _stamina;
};

int main()
{
#pragma region 동적할당
	void* ptr = malloc(1000);

	// cast
	int* ptr_Int = (int*)ptr;
	*ptr_Int = 5;

	free(ptr);

	int* aInt = new int();

	delete aInt;
#pragma endregion

	Player* arr[10];

	// 10명의 Knight Player*
	// 10명의 Mage   Player*
	// 10명의 Archer Player*

	Player* player = new Player();
	Player* knight = new Knight();

	// 가상함수테이블(vftable)을 이용하여 C++이 타입을 실행시간에 추론해준다.
	// => 할당되어있는 자료형에 맞는 함수를 호출해준다.
	player->PrintInfo();
	knight->PrintInfo();

	delete knight;
	delete player; // 삭제는 생성의 역순

	return 0;
}