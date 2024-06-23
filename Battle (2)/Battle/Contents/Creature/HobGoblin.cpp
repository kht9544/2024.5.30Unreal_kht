#include "pch.h"
#include "HobGoblin.h"

HobGoblin::HobGoblin(string name, int hp, int atk)
	:Monster(name,hp,atk)
{
	//Aggro.resize(1);
}

void HobGoblin::MultiAttack()
{
	Aggro.erase(std::remove_if(Aggro.begin(), Aggro.end(), [](pair<Creature*,int> creature)->bool
		{
			return creature.first->IsDead();
		}), Aggro.end());


	std::sort(Aggro.begin(), Aggro.end(), [](pair<Creature*, int>a, pair<Creature*, int>b)->bool
		{
			if (a.second > b.second)
				return true;
			return false;
		});
	
	cout << "----------플레이이별 누적데미지-----------" << '\n';

	for (int i = 0; i < Aggro.size(); i++)
	{
		cout << Aggro[i].first->GetName() << "의 누적 데미지" << Aggro[i].second << '\n';
	}

	if (Aggro.size() > 4)
	{
		for (int i = 0; i < 4; i++)
		{
			Attack(Aggro[i].first);
		}
	}
	else
	{
		for (int i = 0; i < Aggro.size(); i++)
		{
			Attack(Aggro[i].first);
		}
	}
	
	
}

void HobGoblin::TakeDamage(int amount,Creature* attacker)
{
	_curHp -= amount;

	if (_curHp < 0)
		_curHp = 0;

	PrintInfo();

	bool found = false;
	
	for (int i = 0; i < Aggro.size(); i++)
	{
		if (attacker == Aggro[i].first)
		{
			Aggro[i].second += amount;
			found = true;
			break;
		}
	}

	if (!found)
	{
		Aggro.push_back(make_pair(attacker, amount));
	}

}
