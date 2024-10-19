#include <iostream>

using namespace std;

template<typename T = int>
T Add(T a, T b)
{
	T c = a + b;

	return c;
}

template<>
double Add(double a, double b)
{
	double c = a + b;

	cout << "Double" << endl;

	return c;
}

template <typename T = int> 
class Player
{
public:
	T GetHp()
	{
		return _hp;
	}

	void SetHp(const T& hp)
	{
		_hp = hp;
	}

	T _hp;
	int _mp;
};

template<>
class Player<double>
{
public:
	double _hp;
};

int main()
{
	double c = Add<double>(1.2,2.7);
	
	Player<int> player;
	player.GetHp();


	Player<double> player2;
	player2._hp;

	return 0;
}