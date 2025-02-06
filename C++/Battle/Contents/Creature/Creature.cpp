#include "pch.h"
#include "Creature.h"

Creature::Creature(string name, int hp, int atk)
: _name(name), _curHp(hp), _atk(atk), _maxHp(hp)
{
}

Creature::~Creature()
{
}

void Creature::Init()
{
	_curHp = _maxHp;
	isActive = true;
}

void Creature::PrintInfo()
{
	cout << "---------------" << endl;
	cout << "NAME : " << _name << endl;
	cout << "HP : " << _curHp << endl;
	cout << "ATK : " << _atk << endl;
	cout << "---------------" << endl;
}

void Creature::PreAttack(Creature* other)
{
	cout << _name << "Attack: " << other->_name << endl;
}

void Creature::TakeDamage(int amount, Creature* attacker)
{
	_curHp -= amount;

	if (attacker != nullptr && dynamic_cast<Monster*>(this) != nullptr)
	{
		Player* p = dynamic_cast<Player*>(attacker);
		if (p != nullptr)
		{
			p->GainExp(_maxHp);
			p->LevelUp();
		}
	}

	if (_curHp < 0)
		_curHp = 0;

	PrintInfo();
}

bool Creature::IsDead()
{
	if (_curHp <= 0)
	{
		isActive = false;
		return true;
	}

	return false;
}
