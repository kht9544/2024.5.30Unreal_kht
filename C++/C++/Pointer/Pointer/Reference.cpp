#include <iostream>

using namespace std;

// Reference 참조
// 선언 방법 : (자료형)& (변수 이름) = (반드시 초기화)

// 어셈블리어 상 하는 기능은 완전히 동일

// 참조 : C++ 기준 별명(반드시 누군가 필요함)을 지어주는 변수

// Ptr을 쓰는 이유
// 1. nullptr을 나타낼 수 있다... => ptr에는 NULL값을 저장할 수 있다.

// Ref를 쓰는 이유
// 1. 편하다. (연산자를 굳이 쓸 필요가 없다.) => 값전달과 사용하는 방식이 동일
// 2. NULL 표시를 할 수 없다.
// 3. ptr이 위험하다.

struct Player
{
	int hp;
	int mp;
};

// 매개변수로 참조를 넘긴다... Call by Reference
// 읽기전용 : const 참조
void PrintPlayer(const Player& player) // 포인터와 넘겨주는 바이트가 같다
{
	cout << player.hp << endl;
	cout << player.mp << endl;
}

void SetPlayer(Player& player, int hp, int mp)
{
	player.hp = hp;
	player.mp = mp;
}

int main()
{
#pragma region 참조
	int aInt = 1;

	// 참조
	int& aRef = aInt; // aInt의 별명은 aRef
	// 포인터
	int* aPtr = &aInt;

	*aPtr = 10;
	//cout << aInt << endl;

	aRef = 11;
	//cout << aInt << endl;
#pragma endregion

	Player p;
	p.hp = 0;
	p.mp = 0;

	SetPlayer(p, 100, 100);
	PrintPlayer(p);

	return 0;
}