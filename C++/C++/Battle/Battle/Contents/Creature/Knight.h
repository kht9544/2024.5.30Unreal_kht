#pragma once
class Knight : public Player
{
public:
	Knight(string name, int hp, int atk);
	virtual ~Knight();
	
	virtual void Attack(Creature* other) override;
private:
};

