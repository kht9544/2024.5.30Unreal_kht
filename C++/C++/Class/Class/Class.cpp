#include <iostream>

using namespace std;

#include "Player.h"

struct Temp
{
private:
	int hp;
};

class Car
{
public:
	Car()
	{
		cout << "기본 생성자 호출" << endl;
		_handle = 0;
		_wheels = 4;
		_doors = 4;
		_engine = 1;
	}

	Car(int doors)
	{
		cout << "타입 변환 생성자 호출" << endl;
		_doors = doors;
		_handle = 0;
		_wheels = 4;
		_engine = 1;
	}

	~Car()
	{
		cout << "소멸자 호출" << endl;
	}

public: 
	int _handle;

private: 
	int _wheels;
	int _doors;

protected:
	int _engine;
};

int main()
{
	Creature p = Creature(50, 10);
	p.TakeDamage(5);
	p.Print();

	return 0;
}