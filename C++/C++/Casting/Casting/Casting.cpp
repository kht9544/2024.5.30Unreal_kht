﻿#include <iostream>

using namespace std;

// 1. static cast
// => 상식적인 변환만 허용
// => 컴파일 시간에 캐스팅
// 2. dynamic cast
// => 상속구조에서 다형성(vftable)이 있어야 사용가능한 cast
// => 이 때 캐스팅이 실패하면 nullptr을 반환
// => 런타임에 캐스팅
// 3. const cast
// => 상수객체를 비상수객체로 캐스팅
// 4. reinterpret_cast
// => 모든 캐스팅 통과

class Player
{
public:
	virtual void PrintPlayer() { cout << "Player입니다." << endl; }
};

class Knight : public Player
{
public:
	virtual void PrintPlayer() override { cout << "Knight 입니다." << endl; }
};

class Mage : public Player
{
public:
	virtual void PrintPlayer() override { cout << "Mage 입니다." << endl; }
	int _mana;
};

void ManaUp(Player* player)
{
	Mage* mage = dynamic_cast<Mage*>(player);

	if (mage == nullptr)
	{
		cout << "Mage가 아닙니다." << endl;
		return;
	}

	mage->PrintPlayer();
	cout << "최대마나가 증가되었습니다." << endl;
}

enum PacketID
{
	NONE = 0,
	LOG_IN,
	LOG_SUCCESS,
	CREATE_ACCOUNT,
	PLAER_RUN
};

struct Protocol_test_S
{
	PacketID pkt_Id = PacketID::LOG_IN;
	int id;
	int password;
};

struct Protocol_test_C
{
	PacketID pkt_Id = PacketID::LOG_SUCCESS;
	bool success;
};

int main()
{
	int aInt = 5;
	float aFloat = static_cast<float>(aInt);
	bool aBool = static_cast<bool>(aInt);
	Player* player1 = new Knight();
	Player* player2 = new Mage();
	
	ManaUp(player2);

	char* str1 = const_cast<char*>("Hello"); 

	Protocol_test_S pkt;
	pkt.id = PacketID::LOG_IN;
	pkt.id = 12345;
	pkt.password = 12345;

	Protocol_test_S* s_pkt = reinterpret_cast<Protocol_test_S*>(&pkt);

	return 0;
}