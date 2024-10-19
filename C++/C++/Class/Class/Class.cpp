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


struct Temp
{
private:
	int hp;
};

class Car
{
public:
	Car()
	{
		cout << "기본 생성자 호출" << endl;
		_handle = 0;
		_wheels = 4;
		_doors = 4;
		_engine = 1;
	}

	Car(int doors)
	{
		cout << "타입 변환 생성자 호출" << endl;
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

public: 
	int _handle;

private: 
	int _wheels;
	int _doors;

protected:
	int _engine;
};

int main()
{
	Creature p = Creature(50, 10);
	p.TakeDamage(5);
	p.Print();

	return 0;
}