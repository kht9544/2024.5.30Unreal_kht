#include <iostream>

using namespace std;

// 개념
// 추상클래스
// => 이 설계도로 객체화 시킬 수 없음
// => 기능(멤버함수)이 아직 구현이 안되어있음.
// => 순수가상함수를 단 하나 이상이라도 포함하는 클래스

// 순수가상함수를 구현하지 않으면 객체화 시킬 수 없다.
// ==> 자식에서 무조건 순수가상함수를 구현해줘
class Bank
{
public:
	virtual void ShowAccount() abstract; // 순수가상함수
};

// 순수가상함수를 구현하지 않으면 이 클래스는 객체화 시킬 수 없다.
// 은행이라는 개념의 실질적인 객체가 될 수 있는 설계도
class KaKaoBank : public Bank
{
public:
	virtual void ShowAccount() override 
	{
		cout << "안녕하세요 KaKao 은행입니다." << endl;
	}
};

class ShinHanBank : public Bank
{
public:
	virtual void ShowAccount() override 
	{
		cout << "신한은행에 오신 걸 환영합니다. " << endl;
	}
};

class KBBank : public Bank
{
public:
	virtual void ShowAccount() override 
	{
		cout << "KB은행 입니다." << endl;
	}
};

int main()
{
	ShinHanBank shBank;
	KBBank kbBank;

	return 0;
}