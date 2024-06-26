#pragma once
class HobGoblin : public Monster
{
public:
	HobGoblin(string name, int hp, int atk);

	void MultiAttack();
	virtual void TakeDamage(int amount, Creature* attacker) override;

	bool compare(pair<Creature*, int>a, pair<Creature*, int>b) { return a.second > b.second; }

private:
	vector<pair<Creature*, int> > AggroTemp;
	vector<pair<Creature*, int> > Aggro;
};

