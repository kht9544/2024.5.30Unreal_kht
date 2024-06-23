#include <iostream>

using namespace std;

// 함수도 어딘가에는 저장되어있지 않을까?
// 예) vftable...

// 함수 이름이 포인터와 동일하게 동작한다.
// 배열

// 콜백함수
// - 인자로 전달되어 호출되는 함수

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

// 함수 포인터
// 함수 선언 방법 : (반환자료형) 함수이름 (매개변수) => 함수 시그니쳐

// (반환 자료형) (* 포인터이름) (매개변수)
void(*func)(void);
void(*funcInt)(int);

class Pet;
// 멤버 함수 포인터
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