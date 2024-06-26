#include "pch.h"	
#include "World.h"

World::World()
: _player(nullptr)
, _computer(nullptr)
{
	Input();
	Init();
}

World::~World()
{
	if(_player != nullptr)
		delete _player;
	if(_computer != nullptr)
		delete _computer;
}

void World::Init()
{
}

bool World::End()
{
	if (_player->IsDead() || _computer->IsDead())
		return true;

	return false;
}

void World::SeletPlayer(int num, string name, Creature** creature)
{
	switch (num)
	{
	case PlayerType::NONE:
	{
		cout << "�ٽ� �Է����ּ���." << endl;
		break;
	}

	case PlayerType::KNIGHT:
	{
		*creature = new Knight(name, 500, 15);
	}
	break;
	case PlayerType::ARCHER:
	{
		*creature = new Archer(name, 300, 35);
	}
	break;

	default:
	{
		cout << "�ٽ� �Է����ּ���." << endl;
		break;
	}
	break;
	}
}

void World::Input()
{
	int playerNum = 0;
	int cumNum = 0;
	string name;
	
	cout << "�̸��� �Է����ּ���" << endl;
	cin >> name;
	cout << "1~2������ Ŭ������ �Է����ּ���." << endl;
	cin >> playerNum;
	cumNum = rand() % 2 + 1; // 1 ~ 2
	SeletPlayer(playerNum, name, &_player);
	SeletPlayer(cumNum, "computer", &_computer);
}

void World::Battle1()
{
	_player->Attack(_computer);
	_computer->Attack(_player);
}

void World::Battle2()
{
}
