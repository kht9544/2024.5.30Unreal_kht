#include "pch.h"

void SetG_Arr(Goblin arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int randHp = rand() % 21 + 30;
		int randAtk = rand() % 4 + 2;
		arr[i].SetStat(randHp, 0, randAtk);
	}
}

bool GArr_Dead(Goblin arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		if (!arr[i].IsDead())
			return false;
	}
	return true;
}

int main()
{
	string name;
	cin >> name;

	Creature* knight = new Knight(500, 2, 15, 0);
	knight->SetName(name);

	knight->PrintCreature();

	delete knight;

	return 0;
}