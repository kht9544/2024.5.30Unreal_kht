#include <iostream>

using namespace std;

// Singleton
// 1. 전역으로 접근이 가능해야한다.
// 2. 프로그램에 단 하나만 존재해야한다.
// 3. 동적할당되어야한다.

class SoundManager
{
private:
	SoundManager() {}
	~SoundManager() {}

public:
	// private 접근할 수 있는 방법 : public 멤버함수
	//
	static void Create()
	{
		if(instance == nullptr)
			instance = new SoundManager();
	}

	static void Delete()
	{
		if (instance != nullptr)
			delete instance;
	}

	static SoundManager* GetInstance()
	{
		if (instance != nullptr)
			return instance;
		return nullptr;
	}

	void PrintAllSound()
	{
		cout << _warriorSound << endl;
		cout << _archerSound << endl;
	}

	void PrintWarriorSound()
	{
		cout << _warriorSound << endl;
	}

private:
	static SoundManager* instance;
	string _warriorSound = "워리워 등장!";
	string _archerSound = "아쳐 등장!";
};

SoundManager* SoundManager::instance = nullptr;

class Warrior
{
public:
	Warrior() { SoundManager::GetInstance()->PrintWarriorSound(); }
};

int main()
{
	SoundManager::Create();
	
	Warrior* warrior = new Warrior();

	delete warrior;

	SoundManager::Delete();

	return 0;
}