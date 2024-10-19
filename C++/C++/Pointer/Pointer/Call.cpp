#include <iostream>

using namespace std;

struct Player
{
	int hp;
	int mp;
};

void PrintPlayer_Value(Player p)
{
	cout << p.hp << endl;
	cout << p.mp << endl;
}

void SetPlayer_Value(Player p, int hp, int mp)
{
	p.hp = hp;
	p.mp = mp;
}

void PrintPlayer_Ref(const Player& p) 
{
	cout << p.hp << endl;
	cout << p.mp << endl;
}

void SetPlayer_Ref(Player& p, int hp, int mp)
{
	p.hp = hp;
	p.mp = mp;
}

void PrintPlayer_Ptr(const Player* const p)
{
	cout << p->hp << endl;
	cout << p->mp << endl;
}

void SetPlayer_Ptr(Player* const p, int hp, int mp)
{
	p->hp = hp;
	p->mp = mp;
}

void PrintPlayer(Player*& p)
{
	cout << p->hp << endl;
	cout << p->mp << endl;
}

void PrintPlayer(Player** p)
{
	Player* player = *p;
	cout << player->hp << endl;
	cout << player->mp << endl;
}

int main()
{
	Player p;
	p.hp = 0;
	p.mp = 0;

	SetPlayer_Ptr(&p, 50, 50);
	PrintPlayer_Ptr(&p);

	return 0;
}