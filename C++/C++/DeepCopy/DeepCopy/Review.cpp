#include <iostream>

using namespace std;

// 클래스
// - 3속성
// -- 은닉성
// -- 상속성
// -- 다형성

// 은닉성 : 클래스에서 접근지정자(public, private, protected)
// - (private)멤버변수랑 (public)멤버함수...(메소드)
// 상속성 : is - a 관계가 성립 (Cat is a Animal)
// 다형성
// - 함수오버로딩(함수이름이 같고, 매개변수 형식이나 자료형이 다른 것을 정의),
// - 함수오버라이딩(부모의 함수를 자식에서 재정의)

// 가상함수
// - 가상함수를 선언/정의하면 vftable이 생기고 업캐스팅했을 때 실제 생성된 객체 자료형의 함수를 호출할 수 있다.

// 동적할당
// [Code]
// [Data]
// - 전역변수
// - 정적변수
// 생성주기 : 프로그램 실행 / 종료
// => 장점 : 어디서나 갖고와서 쓸 수 있다.
// => 단점 : 어디서나 갖고와서 쓸 수 있다./ 메모리 해제를 시킬 수 없다.
// 
// [Stack]
// - 스택프레임 : [반환주소값][지역변수][매개변수]
// 생성주기 : 함수가 호출되었을 때/ 함수가 종료되었을 때
// => 장점 : 비교적 전역보단 생성 주기를 제어할 수 있다.
// => 단점 : 여전히 내가 직접 생성주기를 제어할 수 없다.
// 
// [Heap]
// - 사용자 영역, 프로그래머 영역, 크기가 제일 큼
// 생성주기 : 사용자 마음대로
// => 장점 : 내 마음대로 할당하고 해제할 수 있다.
// => 단점 : 메모리 누수

int aInt = 0; // 전역변수

class Player
{
public:
	Player() : _id(1) {}

	virtual void PrintInfo()
	{
		cout << "Player 입니다." << endl;
	}

	int _id;
};

class Knight : public Player
{
public:
	Knight() : _hp(2) {}

	virtual void PrintInfo() override
	{
		cout << "Knight 입니다." << endl;
	}

	// 멤버변수
	int _hp;
};

int Temp(int hp) // hp : 매개변수, Parameter(Param) / Argument
{
	int mp = 0; // 지역변수

	return Temp(mp);
}

Knight* Alloc()
{
	Knight* k = new Knight();

	return k;
}

int main()
{
	// 동적할당
	// 지역변수
	// 업캐스팅
	Player* knight = new Knight();
	knight->PrintInfo();

	Temp(5);

	Knight* temp = Alloc();

	delete temp;

	return 0;
}