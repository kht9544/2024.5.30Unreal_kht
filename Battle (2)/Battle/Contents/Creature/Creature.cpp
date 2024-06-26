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
	cout << "---- 정보 ----" << endl;
	cout << "이름 : " << _name << endl;
	cout << "HP : " << _curHp << endl;
	cout << "ATK : " << _atk << endl;
	cout << "---------------" << endl;
}

void Creature::PreAttack(Creature* other)
{
	cout << _name << "이 " << other->_name << "에게 공격을 시도합니다." << endl;
}

void Creature::TakeDamage(int amount, Creature* attacker)
{
	_curHp -= amount;

	if (attacker != nullptr && dynamic_cast<Monster*>(this) != nullptr)
	{
		// 내가 고블린이고, attacker가 유효하다.

		// attacker가 Player였을 때
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
