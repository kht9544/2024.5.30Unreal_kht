#include <iostream>

// 디자인 패턴
// ... 프로그래밍 하면서 공통된 문제들을 해결하는 패턴을 정형화 해놓은 것

// 1. 싱글톤(Singleton)
// - 객체를 단 하나만.게임 로직을 담당하는 얘들, 시스템적인 면을 담당하는 
// - SoundManager : 
// ... 사운드가 출력되야할 때마다 동적할당?
// => SoundManager. 여기에 전사 10명의 목소리, 도적 10명의 목소리

// static 변수와 static 함수에 대해서 조사

// 메모리 영역
// - Code
// - Data
// => 전역변수(Global), 정적변수(static)
// => 프로그램이 시작할 때, 프로그램이 종료될 때
// - Stack
// => [반환주소값][지역변수][매개변수]
// => 함수 호출 시, 지역 시작 / 함수 종료 시, 지역 끝
// - Heap
// => 내가 원하는 데이터 크기만큼
// => 프로그래머가 원하는 대로

using namespace std;

class Marine
{
public:
	void Print()
	{
		cout << _hp << endl; 
		cout << atk << endl; // 멤버함수에서 정적멤버변수를 읽기 가능하다.
	}

	void Set(int hp, int atk)
	{
		_hp = hp;
		this->atk = atk; // 멤버함수에서 정적멤변수 쓰기가 가능하다.
	}

	// 정적멤버 함수
	// 멤버함수 호출 조건 : 객체가 무조건 있어야한다.
	// 정적멤버함수... 전역함수처럼 쓸 수 있다. => 객체가 없어도 된다.
	static void Print_S()
	{
		// cout << this->_hp << endl; // 정적멤버함수는 멤버변수에 접근할 수 없다. 
									  // 정적멤버함수는 this를 누군지 특정할 수 없다.
		cout << atk << endl; // 정적멤버함수는 정적멤버변수에 접근할 수 있다.
	}

	int _hp = 0;
	static int atk;
	int data[100];
};

int Marine::atk = 1;

Marine* marines[100];

int main()
{
	for (int i = 0; i < 100; i++)
	{
		marines[i] = new Marine();
	}

	Marine::atk++;

	marines[0]->Set(100, 50);
	Marine::Print_S();

	cout << marines[5]->atk << endl;

	return 0;
}