#pragma once
class Creature
{
public:
	Creature(string name, int hp, int atk);
	virtual ~Creature();

	void Init();
	// 멤버함수 : 기능
	void PrintInfo();
	void PreAttack(Creature* other);
	virtual void Attack(Creature* other) abstract; // 순수가상함수

	void TakeDamage(int amount, Creature* attacker = nullptr);

	bool IsDead();

	bool isActive = false;

protected: // 멤버변수: 속성
	string _name;
	int _curHp;
	int _maxHp;
	int _atk;
};

