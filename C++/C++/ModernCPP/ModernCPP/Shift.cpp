#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Pet
{
};

class Player
{
public:
	Player() {  _pet = new Pet(); }
	Player(int hp) { _pet = new Pet(); }
	Player(const Player& other) 
	{
		_pet = new Pet(*other._pet);
	}

	Player(Player&& other) noexcept 
	{ 
		if (_pet != nullptr)
			delete _pet;

		_pet = other._pet;
		other._pet = nullptr;
	}
	~Player() { if (_pet != nullptr) delete _pet; }

	Pet* _pet;
};


void SetPlayer(Player&& p, Player&& p2)
{
	delete p._pet;
	p._pet = nullptr;
}

int main()
{
	Player* playerB = new Player();
	Player* playerA = new Player(std::move(*playerB));

	unique_ptr<Player> pPtr = make_unique<Player>();
	unique_ptr<Player> pPtr2 = std::move(pPtr);

	delete playerA;
	delete playerB;

	return 0;
}