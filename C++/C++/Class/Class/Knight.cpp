#include "pch.h"
#include "Creature.h"
#include "Knight.h"

Knight::Knight()
: Creature()
{
	_stamina = 0;
}

Knight::Knight(int hp, int mp, int attack, int stamina)
: Creature(hp, mp, attack)
{
	_stamina = stamina;
}

Knight::~Knight()
{
}

void Knight::Attack(Creature* p)
{
	if (IsDead() || p->IsDead()) return;

	cout << "Knight Attack!!!" << endl;
	p->TakeDamage(_attack);
}
