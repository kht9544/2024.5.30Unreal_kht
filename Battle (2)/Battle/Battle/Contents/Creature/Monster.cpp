#include "pch.h"
#include "Monster.h"

Monster::Monster(string name, int hp, int atk)
: Creature(name, hp, atk)
{
}

Monster::~Monster()
{
}

void Monster::Attack(Creature* other)
{
	this->Creature::PreAttack(other);

	other->TakeDamage(_atk);
}
