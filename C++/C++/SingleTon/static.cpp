#include <iostream>

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