#include <iostream>

using namespace std;

// 함수객체
// 객체이고, 함수처럼 쓸 수있는(()함수 연사자를 오버로드해서 쓸 수 있다) 객체
// 콜백개념으로 쓸 수 있다.
// => 근데 함수 포인터와 다른 점
// - 속성(멤버변수)을 가질 수 있다.

struct Functor
{
	Functor()
	: _aInt(0), _bInt(0)
	{
		cout << "Functor 생성" << endl;
	}

	// 연산자 오버로딩
	void operator()() //() 함수 연산자
	{
		cout << "HelloWorld" << endl;
		cout << _aInt + _bInt << endl;
	}

	void operator()(int number)
	{
		cout << number << endl;
	}

	int _aInt;
	int _bInt;
};

class Player
{
public:
	void Excute()
	{
		if (_functor != nullptr)
			(*_functor)();
	}

	void SetFunctor(Functor* functor)
	{
		_functor = functor;
	}

private:
	Functor* _functor;
};

int main()
{
	Functor functor;
	functor._aInt = 1;
	functor._bInt = 5;
	functor();
	functor(1);

	return 0;
}