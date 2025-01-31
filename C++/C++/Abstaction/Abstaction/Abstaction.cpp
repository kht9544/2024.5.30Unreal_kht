#include <iostream>

using namespace std;

class Bank
{
public:
	virtual void ShowAccount() abstract;
};


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