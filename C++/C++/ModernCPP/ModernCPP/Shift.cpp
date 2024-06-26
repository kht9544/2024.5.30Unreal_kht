#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

// 이동 (이사)
//

class Pet
{
};

class Player
{
public:
	Player() { cout << "기본 생성자 호출" << endl; _pet = new Pet(); }
	Player(int hp) { cout << "타입 변환 생성자 호출" << endl; _pet = new Pet(); }
	Player(const Player& other) 
	{
		cout << "복사생성자 호출" << endl;

		_pet = new Pet(*other._pet);
	}
	
	// && : 우측값 참조
	// 1. 원본을 전달
	// 2. 이사
	Player(Player&& other) noexcept 
	{ 
		cout << "이동생성자 호출" << endl; 
		if (_pet != nullptr)
			delete _pet;

		_pet = other._pet;
		other._pet = nullptr;
	}
	~Player() { cout << "소멸자 호출" << endl; if (_pet != nullptr) delete _pet; }

	Pet* _pet;
};

// Lvalue : 좌측값
// 수정될 수 있는 값 => 어딘가에 저장되어있다.
// 대표적으로 참조

// Rvalue : 우측값
// 수정될 수 없는 값, 상수
// 대표적으로 상수, const

// 1. Call by Value
// => 원본이 바뀌지 않는다.
// ==> 함수 내부에 어떤짓을해도 괜찮다.
// 매개변수의 크기는 자료형에 따라 다르다.
//void SetPlayer(Player p)
//{
//
//}

// 2. Call by Address
// => 원본이 바뀐다.
// 매개변수의 크기는 포인터의 크기에 따른다.
// 단점 : 쓰기 어렵다. 잘못쓰면 메모리 오염이 생길 수 있다.
void SetPlayer(Player* const p)
{

}

// 3. Call by Reference
// => 원본이 바뀐다.
// 매개변수의 크기는 포인터의 크기에 따른다.
// 장점 : 쓰기 편하다. 메모리 오염을 일으킬 가능성이 낮다.
// 단점 : 쓰기 편하지만 값전달과 동일한 방식, 범용성이 낮다.
void SetPlayer(Player& p)
{
	
}

// 4. 우측값 참조 전달
// => 원본에 접근 가능
// 매개변수의 크기는 포인터의 크기에 따른다.(X)
// - 이사(원본을 훼손할 수 있다.)를 한다.
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