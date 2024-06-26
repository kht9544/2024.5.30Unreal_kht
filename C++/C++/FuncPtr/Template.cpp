#include <iostream>

using namespace std;

// Template
// Class
// => 객체(건물)를 찍어내는 설계도
// Template ... 이 설계도를 찍어내는 얘

// 함수 템플릿 : 함수를 찍어내는 얘
// 템플릿 기본인자
// 템플릿의 특수화
template<typename T = int>
T Add(T a, T b)
{
	T c = a + b;

	return c;
}

template<>
double Add(double a, double b)
{
	double c = a + b;

	cout << "Double" << endl;

	return c;
}

// 클래스 템플릿
template <typename T = int> // 클래스 템플릿 기본인자
class Player
{
public:
	T GetHp()
	{
		return _hp;
	}

	void SetHp(const T& hp)
	{
		_hp = hp;
	}

	T _hp;
	int _mp;
};

// 클래스 템플릿 특수화
template<>
class Player<double>
{
public:
	double _hp;
};

int main()
{
	double c = Add<double>(1.2,2.7);
	
	Player<int> player;
	player.GetHp();


	Player<double> player2;
	player2._hp;

	return 0;
}