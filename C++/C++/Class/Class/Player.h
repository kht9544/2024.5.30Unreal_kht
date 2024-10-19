#pragma once

#include <iostream>

using namespace std;

class Player
{
public:
	Player() { _hp = 0; _mp = 0; }
	Player(int hp, int mp) { _hp = hp; _mp = mp; }
	~Player() {}
	void Print()
	{
		cout << "Player�� hp : " << _hp << endl;
		cout << "Player�� mp : " << _mp << endl;
	}

	void TakeDamage(int amount)
	{
		_hp -= amount;

		if (_hp < 0)
		{
			_hp = 0;
		}
	}

private:
	int _hp;
	int _mp;
};

