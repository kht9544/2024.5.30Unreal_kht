#include <iostream>

using namespace std;

struct Player
{
	int hp;
	int mp;
};

void PrintPlayer(const Player* const player)
{
	cout << player->hp << endl;
	cout << player->mp << endl;
}

void SetPlayer(Player player) {}
 

void SetPlayer(Player* const player, int hp, int mp)
{
	player->hp = hp;
	player->mp = mp;
}

int main()
{
	Player p;
	p.hp = 0;
	p.mp = 0;

	Player* p_ptr = &p; 

	SetPlayer(&p, 50, 50);
	PrintPlayer(&p);

	return 0;
}