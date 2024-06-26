#include <iostream>

using namespace std;

// 객체 지향 3속성
// 1. 은닉성
// - public    : 어디서나 접근 가능
// - private   : 내부(멤버함수)에서만 접근 가능
// - protected : 내부, 자식에서만 접근 가능
// 
// ...함부로 멤버변수를 건드리지마라.
// => 프로그래머가 만든 public 멤버함수(인터페이스)로만 멤버변수를 수정해라
// 
// 2. 다형성
// - 함수 오버로딩
// 
// - 함수 오버라이딩
// 
// 3. 상속성
// Animal ... Cat
// Cat은 Animal인가? (O)
// Animal은 Cat인가? (X)
//
// 4. 추상화

class Vector2
{
public:
	Vector2() { _x = 0; _y = 0; }
	Vector2(int x, int y) { _x = x; _y = y; }
	~Vector2() {}

	void PrintVector2()
	{
		// this 포인터 키워드
		// 이 함수를 호출한 객체를 가리키는 포인터
		cout << "x : " << (*this)._x << endl;
		cout << "y : " << this->_y << endl;
	}

	// 연산자 오버로딩
	// a + b : a와 b를 더하고 그 값을 반환한다.

	Vector2 operator+(const Vector2& other)
	{
		Vector2 result;
		result._x = this->_x + other._x;
		result._y = _y + other._y;

		return result;
	}

	// -
	Vector2 operator-(const Vector2& other)
	{
		Vector2 result;
		result._x = this->_x - other._x;
		result._y = _y - other._y;

		return result;
	}

	// vector * scalar
	Vector2 operator*(int value)
	{
		Vector2 result;
		result._x = _x * value;
		result._y = _y * value;

		return result;
	}
	// vector / scalar
	Vector2 operator/(int value)
	{
		Vector2 result;
		result._x = _x / value;
		result._y = _y / value;

		return result;
	}

	// a.operator=(b)
	// a = b : a에다가 b를 대입하고 a의 원본을 반환한다.
	// 정의하지않으면 암묵적으로 생성되는
	Vector2& operator=(const Vector2& other)
	{
		this->_x = other._x;
		this->_y = other._y;

		return (*this);
	}

	// a++
	// 임시로 a의 값을 반환하고 a를 1 더해준다.
	Vector2 operator++(int)
	{
		Vector2 result = *this;
		*this = (*this) + Vector2(1, 1);

		return result;
	}

	// ++a
	// a의 값을 1 더하고, a의 원본을 반환한다.
	Vector2& operator++()
	{
		(*this)++;
		return (*this);
	}

	// 내적, 외적
	float Dot(const Vector2& other)
	{
		// cosA * |a| * |b| = _x * other._x + _y * other._y;
		float result = 0.0f;
		result = _x * other._x + _y * other._y;
		return result;
	}

	// 외적
	float Cross(const Vector2& other)
	{
		float result = _x * other._y - _y * other._x;
		return result;
	}

	int _x;
	int _y;
};

// 상속
class Animal
{
public:
	Animal() { _mouth = 1; _leg = 4; }

	void Eat()
	{
		cout << "쩝쩝" << endl;
	}

protected:
	int _mouth;
	int _leg;
};

class Cat : public Animal
{
public:
	Cat() 
	{ 
		// :: : 범위지정연산자
		Animal::_mouth = 1;
		_tail = 123; 
	}

	// 함수 오버라이딩 : 시그니쳐가 완전히 동일하고 실행문을 재정의한다.
	void Eat()
	{
		cout << "냥냥" << endl;
	}

	// 함수 오버로딩
	void Eat(int temp)
	{
		cout << temp << endl;
		cout << "냥냥" << endl;
	}

private:
	int _tail;
};

int main()
{
	Animal animal = Animal();
	Cat cat = Cat();

	animal.Eat();
	cat.Animal::Eat();

	return 0;
}