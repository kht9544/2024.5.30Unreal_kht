#include <iostream>

using namespace std;

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