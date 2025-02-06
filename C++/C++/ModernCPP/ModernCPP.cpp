#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;


class Player
{
public:
	virtual void PrintP() {}

	int _hp = 0;
};

class Knight : public Player
{
public:
	friend class KnightHelper;

	virtual void PrintP() final override {}

private:
	int _stamina = 0;
};

class HolyKnight : public Knight
{
public:
};

class KnightHelper
{
public:
	void PrintK(Knight* k) { k->_stamina; }
};

typedef void(*FuncPtr)(void);
typedef unsigned int UINT;

using UINT2 = unsigned int;
using FuncPtr2 = void(*)(void);

void Hello()
{
	cout << "Hello" << endl;
}

enum class PlayerType
{
	NONE,
	KNIGHT,
	ARCHER,
	MAGE
};

enum class WarriorType
{
	NONE,
	HOLLYKNIGHT,
	WARRIOR,
	KNIGHT
};

int main()
{
	auto aInt = { 5 };

	auto aDoble = { 1.4 };

	vector<int> tempV = { 1,2,3,4,5,56,67,88888,23 };

	auto vIter = tempV.begin();

	for (vIter; vIter != tempV.end(); vIter++)
	{

	}

	unordered_map<int, int> temp_uM;
	temp_uM[0] = 1;
	temp_uM[2] = -1;
	temp_uM[4] = 311;
	temp_uM[7] = 100;
	temp_uM[9] = 123;

	auto umIter = temp_uM.begin();
	for (umIter; umIter != temp_uM.end(); umIter++)
	{

	}

	for (auto& p : temp_uM)
	{
		p.second *= 5;
		cout << "Key : " << p.first << "Value : " << p.second << endl;
	}


	UINT aUInt = 5;

	FuncPtr funcPtr;
	funcPtr = &Hello;
	funcPtr();

	int type = static_cast<int>(WarriorType::KNIGHT);


	return 0;
}