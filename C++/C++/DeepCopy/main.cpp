#include <iostream>

using namespace std;

class Pet
{
private:
	int arr[100];
};

class Player
{
public:
	Player()
	: 
	_maxHp(150)
	,_hp(0)
	, _hpRef(_hp)
	, _target(nullptr)
	{
		_hp = _maxHp;
		_pet = new Pet();
		cout << "�⺻������ ȣ��" << endl;
	}
	Player(int hp) 
	:_maxHp(hp)
	, _hp(0)
	, _hpRef(_hp)
	, _target(nullptr)
	{
		_hp = _maxHp;
		_pet = new Pet();
		cout << "Ÿ�Ժ�ȯ ������ ȣ��" << endl;
	}

	Player(const Player& other)
	: _maxHp(other._maxHp)
	, _hp(other._hp)
	, _hpRef(other._hpRef)
	, _target(other._target)
	, _pet(nullptr)
	{
		_pet = new Pet(*other._pet);
		cout << "��������� ȣ��" << endl;
	}

	~Player() 
	{
		delete _pet;
	}

	void SetTarget(Player* other) { _target = other; }
	void Attack()
	{
		cout << "����" << endl;
		cout << _target->_hp << endl;
	}

private:
	int _hp;

	const int _maxHp;
	int& _hpRef;
	Player* _target;
	Pet* _pet; 
};

int main()
{
	Player a = Player(); 
	Player b = Player(5); 
	Player c = 2; 
	Player d = Player(c); 

	Player* a_player = new Player();
	Player* b_player = new Player(*a_player);


	delete a_player;
	delete b_player;

	return 0;
}