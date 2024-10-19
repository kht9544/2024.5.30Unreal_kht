#include <iostream>

using namespace std;


// 동적할당
// 메모리 4영역
// Code
// Data (전역변수, 정적변수)
// 생성주기 : 프로그램이 시작할 때 생성 / 프로그램이 종료될 때 해제된다.
// 단점 : 코드가 난잡해질 수 있다./ 메모리가 계속 할당되어 있다.
// Stack (지역변수, 매개변수, 반환주소값)
// 생성주기 : 함수가 호출되서 시작할 때 생성/ 함수가 끝났을 때 해제
// 단점 : 메모리를 제어할 수 없다.
// Heap : 사용자 영역
// 생성주기 : 내 마음대로 제어할 수 있다.
// 단점 : 내 마음대로 제어할 수 있다. => 내가 실수하면 메모리 누수

class Player
{
public:
	Player()
	: _hp(0)
	{
	}
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

	virtual void PrintInfo() override { cout << "Knight입니다." << endl; }

	int _stamina;
};

int main()
{
#pragma region 동적할당
	void* ptr = malloc(1000);

	int* ptr_Int = (int*)ptr;
	*ptr_Int = 5;

	free(ptr);

	int* aInt = new int();

	delete aInt;
#pragma endregion

	Player* arr[10];

	Player* player = new Player();
	Player* knight = new Knight();

	player->PrintInfo();
	knight->PrintInfo();

	delete knight;
	delete player; 

	return 0;
}