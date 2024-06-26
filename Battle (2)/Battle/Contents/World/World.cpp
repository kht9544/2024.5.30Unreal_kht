#include "pch.h"	
#include "World.h"

World::World()
	: _player(nullptr)
	, _computer(nullptr)
{
	Input();

	_monsters.reserve(10);

	for (int i = 0; i < 10; i++)
	{
		Monster* monster = new Monster("Goblin", 50, 10);
		_monsters.push_back(monster);
	}

	Creature* player = new Knight("Player", 500, 50);
	players.push_back(player);
	Creature* player1 = new Knight("Player1", 500, 90);
	players.push_back(player1);
	Creature* player2 = new Knight("Player2", 500, 80);
	players.push_back(player2);
	Creature* player3 = new Knight("Player3", 500, 70);
	players.push_back(player3);
	Creature* player4 = new Knight("Player4", 500, 40);
	players.push_back(player4);
	Creature* player5 = new Knight("Player5", 500, 30);
	players.push_back(player5);
	Creature* player6 = new Knight("Player6", 500, 10);
	players.push_back(player6);
	Creature* player7 = new Knight("Player7", 500, 80);
	players.push_back(player7);
	Creature* player8 = new Knight("Player8", 500, 150);
	players.push_back(player8);
	Creature* player9 = new Knight("Player9", 500, 30);
	players.push_back(player9);


	_hobgoblin = new HobGoblin("Hobgoblin", 50000, 300);
	Init();
}

World::~World()
{
	for (int i = 0; i < 10; i++)
	{
		delete players[i];
	}

	if (_player != nullptr)
		delete _player;
	if (_computer != nullptr)
		delete _computer;

	for (int i = 0; i < _monsters.size(); i++)
	{
		delete _monsters[i];
	}
}

void World::Init()
{
	/*_player->Init();
	_computer->Init();*/
	//_hobgoblin->Init();

	for (int i = 0; i < _monsters.size(); i++)
	{
		_monsters[i]->Init();
	}

	/*for (int i = 0; i < players.size(); i++)
	{
		players[i]->Init();
	}*/

}

bool World::End()
{
	if (_player->IsDead() || _computer->IsDead() || MonstersCheck() || _hobgoblin->IsDead())
		return true;

	return false;
}

bool World::MonstersCheck()
{
	for (int i = 0; i < _monsters.size(); i++)
	{
		if (!_monsters[i]->IsDead())
			return false;
	}


	return true;
}

bool World::playersWin()
{
	return false;
}

bool World::Battle3PlayerWin()
{

	if (_hobgoblin->IsDead())
	{
		return true;
	}


	return false;
}

bool World::Battle3BoosWin()
{
	for (int i = 0; i < 10; i++)
	{
		if (!players[i]->IsDead())
			return false;
	}
	return true;
}

void World::SelectPlayer(int num, string name, Creature** creature)
{
	switch (num)
	{
	case PlayerType::NONE:
	{
		cout << "다시 입력해주세요." << endl;
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
		cout << "다시 입력해주세요." << endl;
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
	cumNum = rand() % 2 + 1; // 1 ~ 2

	/*SelectPlayer(cumNum, "computer", &_computer);
	cout << "이름을 입력해주세요" << endl;
	cin >> name;
	cout << "1~2까지의 클래스를 입력해주세요." << endl;
	cin >> playerNum;
	SelectPlayer(playerNum, name, &_player);

	for (int i = 0; i < 10; i++)
	{
		SelectPlayer(cumNum, "computer", &_computer);
		cout << "이름을 입력해주세요" << endl;
		cin >> name;
		cout << "1~2까지의 클래스를 입력해주세요." << endl;
		cin >> playerNum;
		SelectPlayer(playerNum, name, &_player);
		players.push_back(_player);
	}*/

}

void World::Battle1()
{
	while (true)
	{
		_player->Attack(_computer);
		_computer->Attack(_player);

		if (End())
		{
			Init();
			break;
		}
	}
}

void World::Battle2()
{
	while (true)
	{
		Player* p = dynamic_cast<Player*>(_player);
		if (p == nullptr)
			continue;

		p->MultiAttack(_monsters);

		for (int i = 0; i < _monsters.size(); i++)
		{
			_monsters[i]->Attack(p);
		}

		if (End())
		{
			Init();
			break;
		}
	}
}

void World::Battle3()
{
	while (true)
	{
		for (int j = 0; j < 10; j++)
		{
			players[j]->Attack(_hobgoblin);
		}
		_hobgoblin->MultiAttack();

		if (Battle3PlayerWin() || Battle3BoosWin())
		{
			if (Battle3PlayerWin())
			{
				cout << "Player Win" << '\n';
				break;
			}
			else
			{
				cout << "HubGolbin Win" << '\n';
				break;
			}

		}
	}





}

