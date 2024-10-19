#include <iostream>

using namespace std;

void HelloWorld()
{
	cout << "Hello World" << endl;
}

void PrintHello()
{
	cout << "안녕하세요." << endl;
}

void PrintNum(int number)
{
	cout << number << endl;
}

void(*func)(void);
void(*funcInt)(int);

class Pet;
void(Pet::* func1)(void);

class Pet
{
public:
	static void DogSound()
	{
		cout << "멍멍" << endl;
	}

	void Sound()
	{
		cout << "냐옹" << endl;
	}
private:
	
};

class Player
{
public:

	void Excute()
	{
		// 공격

		if (_func != nullptr)
			_func();
	}

	void PetExcute()
	{
		if (_petFunc != nullptr && _pet != nullptr)
			(_pet->*_petFunc)();
	}

	void SetFunc(void(*func)(void))
	{
		_func = func;
	}

	void SetPetFunc(Pet* pet,void(Pet::* func)(void))
	{
		_petFunc = func;
		_pet = pet;
	}

private:
	void(*_func)(void) = nullptr;
	void(Pet::* _petFunc)(void) = nullptr;
	Pet* _pet = nullptr;
};

int main()
{
	func = &HelloWorld;
	funcInt = &PrintNum;
	func();

	Player* p = new Player();
	p->SetFunc(&HelloWorld);
	p->SetFunc(&PrintHello);
	p->SetFunc(&Pet::DogSound);
	p->Excute();

	Pet* pet = new Pet();
	p->SetPetFunc(pet,&Pet::Sound);
	p->PetExcute();

	p->Excute();

	return 0;
}