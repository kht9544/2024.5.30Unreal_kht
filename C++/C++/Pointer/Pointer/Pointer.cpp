#include <iostream>

using namespace std;

// 함수
// 함수 선언 방법
// (반환자료형) (함수 이름) ((매개변수...)) 인자 , parameter, argument
// 스택프레임 main([반환주소값][지역변수][매개변수]) HelloWorld([][][]) ... stack형식으로 쌓인다

// 포인터
// 주소를 담는 변수
// (자료형) * (포인터 이름) = (초기화) ... 나중에 초기화해도 된다.
// 연산자
// *(포인터변수) : 간접연산자, 포탈연산자 => 주소로 타고 들어간다.
// &(변수) : 주소연산자
// (변수). : 멤버연산자
// (변수)-> : 간접멤버연산자

// 구조체
// Player 
// hp, mp => int
// 읽기전용으로 Print
// 인자로 hp, mp 받아서 Setting 함수

struct Player
{
	int hp;
	int mp;
};

// 읽기전용
void PrintPlayer(const Player* const player)
{
	cout << player->hp << endl;
	cout << player->mp << endl;
}

// 값 전달... Call by Value
void SetPlayer(Player player) {}
 
// 주소 전달... Call by Address
// 원본을 매개변수로 넘긴다,,, 원본 전달
void SetPlayer(Player* const player /* 0x16 */, int hp, int mp)
{
	// main[][][player(0x16) : hp,mp] SetPlayer[player : 0x16][][]
	player->hp = hp;
	player->mp = mp;
}

int main()
{
	Player p;
	p.hp = 0;
	p.mp = 0;

	Player* p_ptr = &p; // p_ptr ... p의 주소값
	// p : 0x16

	SetPlayer(&p, 50, 50);
	PrintPlayer(&p);

	return 0;
}