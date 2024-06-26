#include <iostream>

using namespace std;

// Pet클래스가 추가되고 Player가 펫을 한마리 갖고있다.
class Pet
{
private:
	int arr[100];
};

class Player
{
public:
	Player()
	:  // 빠른초기화 영역
	_maxHp(150)
	,_hp(0)
	, _hpRef(_hp)
	, _target(nullptr)
	{
		_hp = _maxHp;
		_pet = new Pet();
		cout << "기본생성자 호출" << endl;
	}

	// 기본생성자, 타입변환생성자
	Player(int hp) // 타입변환 생성자
	:_maxHp(hp)
	, _hp(0)
	, _hpRef(_hp)
	, _target(nullptr)
	{
		_hp = _maxHp;
		_pet = new Pet();
		cout << "타입변환 생성자 호출" << endl;
	}

	// 복사생성자
	// 암묵적으로 만들어주는 생성자 => 제가 명시적으로 만들면 안만들어줌 ...Shallow Copy 얕은 복사
	// 암묵적으로 만들었을 때 모든 멤버변수를 복사한다.
	Player(const Player& other)
	: _maxHp(other._maxHp)
	, _hp(other._hp)
	, _hpRef(other._hpRef)
	, _target(other._target)
	, _pet(nullptr)
	{
		_pet = new Pet(*other._pet); // DeepCopy... 깊은 복사
		cout << "복사생성자 호출" << endl;
	}

	~Player() 
	{
		delete _pet;
	}

	void SetTarget(Player* other) { _target = other; }
	void Attack()
	{
		cout << "공격" << endl;
		//_target->_hp -= 10;
		cout << _target->_hp << endl;
	}

private:
	// 기본자료형
	int _hp;

	const int _maxHp;
	int& _hpRef;
	Player* _target;
	Pet* _pet; // 4바이트
};

int main()
{
	Player a = Player(); // 기본생성자 호출
	Player b = Player(5); // 타입변환생성자 호출
	Player c = 2; // 타입변환생성자 호출
	Player d = Player(c); // 복사생성자 호출

	Player* a_player = new Player();
	Player* b_player = new Player(*a_player);


	delete a_player;
	delete b_player;

	return 0;
}