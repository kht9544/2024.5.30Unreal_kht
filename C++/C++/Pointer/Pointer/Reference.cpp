#include <iostream>

using namespace std;


struct Player
{
	int hp;
	int mp;
};

void PrintPlayer(const Player& player)
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
#pragma region ����
	int aInt = 1;

	int& aRef = aInt;
	int* aPtr = &aInt;

	*aPtr = 10;

	aRef = 11;
#pragma endregion

	Player p;
	p.hp = 0;
	p.mp = 0;

	SetPlayer(p, 100, 100);
	PrintPlayer(p);

	return 0;
}