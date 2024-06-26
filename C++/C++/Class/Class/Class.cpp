#include <iostream>

using namespace std;

#include "Player.h"

// 클래스
// struct... 99프로 일치
// => 설계도
// ==> 건물을 지을 수 있다
// ==> 객체를 만들 수 있다.
// 클래스는 객체를 찍어내는 도구

// 객체지향 3속성
// 1. 은닉성
// 2. 다형성
// 3. 상속성(언리얼의 핵심 구조)

// 1. 은닉성
// struct와 class 차이는 기본접근지정자가 struct는 public, class는 private
// 접근지정자 public, protected, private

struct Temp
{
private:
	int hp;
};

class Car
{
public:
// 도대체 private 영역에 있는 멤버변수들은 초기화조차 못하는 건가?
// => 생성자
// => 생성할 때만 호출되는 함수
// => 생성자에서 멤버변수를 초기화한다.
	Car() // 기본생성자 : 암묵적으로 정의하지않아도 호출되는 생성자(다른 생성자가 하나라도 없을 경우)
	{
		cout << "기본 생성자 호출" << endl;
		_handle = 0;
		_wheels = 4;
		_doors = 4;
		_engine = 1;
	}

	Car(int doors)
	{
		cout << "타입 변환 생성자 호출" << endl; // 매개변수가 있는 생성자
		_doors = doors;
		_handle = 0;
		_wheels = 4;
		_engine = 1;
	}

	// 소멸자
	~Car()
	{
		cout << "소멸자 호출" << endl;
	}

public: // 외부에서 접근 가능
	int _handle;

private: // 내부에서만 접근 가능
	int _wheels;
	int _doors;

protected: // 내부, 자식에서만 접근 가능
	int _engine;
};

int main()
{
	Creature p = Creature(50, 10);
	p.TakeDamage(5);
	p.Print();

	return 0;
}