#include "pch.h"
#include "Bullet.h"
#include "Cannon.h"
#include "Objects/Obstacle.h"

Bullet::Bullet()
{
	_radius = 7;
	_col = make_shared<CircleCollider>(CENTER, _radius);
}

Bullet::~Bullet()
{
}

void Bullet::Update()
{
	if (_isActive == false) return;

	//Attack_Cannon();


	_col->Update();
	_col->_center += _direction * _speed;

	bool isOut = false;
	if (isOut)
	{
		_isActive = false;
	}


}

void Bullet::Render(HDC hdc)
{
	if (_isActive == false) return;

	_col->Render(hdc);
}

void Bullet::Fire(Vector2 startPos, Vector2 direction)
{
	_isActive = true;
	_col->_center = startPos;
	_direction = direction;
	_direction.Normalize();
	_downVector = Vector2();
}

void Bullet::SetActive(bool isActive)
{
	_downVector = Vector2();
	_isActive = isActive;
}

bool Bullet::IsOut()
{
	if (_col->_center._x > WIN_WIDTH || _col->_center._x < 0)
		return true;

	if (_col->_center._y > WIN_HEIGHT || _col->_center._y < 0)
		return true;

	return false;
}

void Bullet::OutControll(shared_ptr<Obstacle> block)
{
	int lenx = _col->_center._x - block->GetCollider()->_center._x;
	if (lenx < 0)
	{
		lenx *= -1;
	}
	int leny = _col->_center._y - block->GetCollider()->_center._y;
	if (leny < 0)
	{
		leny *= -1;
	}
	lenx = block->GetLengthX() - lenx;
	leny = block->GetLengthY() - leny;

	int lengthx = _radius + block->GetLengthX();
	int lengthy = _radius + block->GetLengthY();

	bool In = (((_col->_center._x < block->GetCollider()->_center._x + block->GetLengthX()) && _col->_center._x > block->GetCollider()->_center._x - block->GetLengthX()) && ((_col->_center._y < block->GetCollider()->_center._y + block->GetLengthY()) && _col->_center._y > block->GetCollider()->_center._y - block->GetLengthY()));

	if (_col->IsCollision(block->GetCollider()))
	{
		if (In)
		{
			if (leny < lenx)
			{
				_col->_center._y = block->GetCollider()->_center._y + lengthy;
			}
			else
			{
				_col->_center._x = block->GetCollider()->_center._x + lengthx;
			}
		}
		else
		{
			if (_col->_center._y + lengthy > block->GetCollider()->_center._y || _col->_center._y - lengthy < block->GetCollider()->_center._y)
			{
				_direction._y *= -1.0f;
			}
			else if (_col->_center._x + lengthx < block->GetCollider()->_center._x || _col->_center._x - lengthx > block->GetCollider()->_center._x)
			{
				_direction._x *= -1.0f;
			}
		}
	}
	else
		return;
}

void Bullet::Attack_Cannon(shared_ptr<Cannon> cannon)
{
	if (IsActive() == false)
		return;

	// cannon을 어떻게 공격할 것인가
	// => cannon의 body
	if (cannon->GetCollider()->IsCollision(_col))
	{
		SetActive(false);
	}
}

void Bullet::Attack_Cannon()
{
	if (_target.expired() == false)
	{
		shared_ptr<Cannon> targetCannon = _target.lock();
		shared_ptr<Collider> targetCannonCol = targetCannon->GetCollider();
		if (targetCannonCol->IsCollision(_col))
		{
			SetActive(false);
		}
	}
}