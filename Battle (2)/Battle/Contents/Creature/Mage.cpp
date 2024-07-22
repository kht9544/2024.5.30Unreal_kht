#include "pch.h"
#include "Mage.h"

Mage::Mage(string name, int hp, int atk, int maxmp)
	:Player(name, hp, atk), _maxmp(maxmp)
{
	_mp = _maxmp;
}

Mage::~Mage()
{
}

void Mage::Attack(Creature* other)
{
	this->Creature::PreAttack(other);
	if (_mp > 5)
	{
		_mp -= 5;
		other->TakeDamage(_atk);
	}
	else
	{
		cout << "마나부족" << '\n';
		_mp += 50;
	}

}

