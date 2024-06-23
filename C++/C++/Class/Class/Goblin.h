#pragma once
class Goblin : public Creature
{
public:
	Goblin();
	Goblin(int hp, int mp, int attack);
	virtual ~Goblin();

	// 함수 오버라이딩
	virtual void Attack(Creature* p) override;
private:

};

