#pragma once

#include "Creature.h"

class Knight : public Creature
{
public:
	Knight();
	Knight(int hp, int mp, int attack, int stamina);
	virtual ~Knight();

	// 함수 오버라이딩 : 부모의 함수를 재정의
	virtual void Attack(Creature* p) override;

private:
	int _stamina;
};

