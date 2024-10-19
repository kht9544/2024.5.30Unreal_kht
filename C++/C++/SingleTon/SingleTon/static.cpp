#include <iostream>

// 디자인 패턴
// ... 프로그래밍 하면서 공통된 문제들을 해결하는 패턴을 정형화 해놓은 것

// 1. 싱글톤(Singleton)
// - 객체를 단 하나만.게임 로직을 담당하는 얘들, 시스템적인 면을 담당하는 
// - SoundManager :  여기에 전사 10명의 목소리, 도적 10명의 목소리


using namespace std;

class Marine
{
public:
	void Print()
	{
		cout << _hp << endl; 
		cout << atk << endl;
	}

	void Set(int hp, int atk)
	{
		_hp = hp;
		this->atk = atk;
	}

	static void Print_S()
	{
		cout << atk << endl;
	}

	int _hp = 0;
	static int atk;
	int data[100];
};

int Marine::atk = 1;

Marine* marines[100];

int main()
{
	for (int i = 0; i < 100; i++)
	{
		marines[i] = new Marine();
	}

	Marine::atk++;

	marines[0]->Set(100, 50);
	Marine::Print_S();

	cout << marines[5]->atk << endl;

	return 0;
}