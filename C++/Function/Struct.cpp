#include <iostream>

using namespace std;


struct Player
{
	int hp;
	int mp;

};

void PrintPlayer(Player player) 
{

}

void PrintPlayer(const Player* const player) 
{
	cout << "Hp : " << player->hp << endl;
	cout << "Mp : " << player->mp << endl;
}

void SetPlayer(Player* const player, int hp, int mp)
{
	(*player).hp = hp;
	player->mp = mp;
}

int main()
{
	Player p;
	p.hp = 0;
	p.mp = 0;

	SetPlayer(&p, 100, 100);
	PrintPlayer(p);

	return 0;
}