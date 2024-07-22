#pragma once
class Player : public Creature
{
public:
	Player(string name, int hp, int atk);
	virtual ~Player();

	void MultiAttack(vector<Creature*> arr);
	void GainExp(int exp);
	void LevelUp();

protected:
	/*int _needexp[10] = { 10,20,30,40,50,60,70,80,90 };
	int _level;*/
	
	const int _maxExp = 100;
	int _exp;

};

