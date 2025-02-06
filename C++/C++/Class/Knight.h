#pragma once

#include "Creature.h"

class Knight : public Creature
{
public:
	Knight();
	Knight(int hp, int mp, int attack, int stamina);
	virtual ~Knight();

	virtual void Attack(Creature* p) override;

private:
	int _stamina;
};

