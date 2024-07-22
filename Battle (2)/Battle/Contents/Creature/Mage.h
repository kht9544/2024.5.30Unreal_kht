#pragma once
class Mage : public Player
{
public:
	Mage(string name, int hp, int atk, int maxmp);
	virtual ~Mage();
	virtual void Attack(Creature* other)override;

private:
	int _maxmp;
	int _mp;

};

