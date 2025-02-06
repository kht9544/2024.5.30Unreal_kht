#include "pch.h"
#include "Creature.h"

Creature::Creature()
: _name("")
{
	_hp = 0;
	_mp = 0;
	_attack = 0;

}

Creature::Creature(int hp, int mp, int attack)
: _name("")
{
	_hp = hp;
	_mp = mp;
	_attack = attack;
}

Creature::~Creature()
{
	cout << "Creature 소멸" << endl;
}

void Creature::PrintCreature()
{
	cout << "Name : " << _name << endl;
	cout << "HP : " << _hp << endl;
	cout << "MP : " << _mp << endl;
	cout << "ATTACK : " << _attack << endl;
}

void Creature::TakeDamage(int amount)
{
	_hp -= amount;

	if (_hp <= 0)
		_hp = 0;
}

void Creature::SetStat(int hp, int mp, int attack)
{
	_hp = hp;
	_mp = mp;
	_attack = attack;
}

void Creature::SetName(const string& name)
{
	_name = name;
}
