#include <iostream>

using namespace std;


struct Functor
{
	Functor()
	: _aInt(0), _bInt(0)
	{
		cout << "Functor ����" << endl;
	}

	void operator()() 
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