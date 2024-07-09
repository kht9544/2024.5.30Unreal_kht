#include "pch.h"
#include "ArkanoidScene.h"
#include "Objects/Cannon.h"
#include "Objects/Bullet.h"
#include "Objects/Obstacle.h"

ArkanoidScene::ArkanoidScene()
{

	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 10; i++)
		{
			shared_ptr<Obstacle>_obstacle = make_shared<Obstacle>();
			_obstacle->GetCollider()->_center._x += 80 * i;
			_obstacle->GetCollider()->_center._y += 60 * j;
			_rocks.push_back(_obstacle);
		}	
	}

	_cannon1 = make_shared<Cannon>();

	_cannon1->isControlled = true;

	_ball = make_shared<Bullet>();

}

ArkanoidScene::~ArkanoidScene()
{
}

void ArkanoidScene::Update()
{
	_cannon1->Update();
	for (auto bullet : _cannon1->GetBullets())
	{
		for (auto block : _rocks)
		{
			bullet->OutControll(block);
		}
	}

	for (int i = 0; i < 30; i++)
	{
		_rocks[i]->Update();
	}
}

void ArkanoidScene::Render(HDC hdc)
{
	_cannon1->Render(hdc);
	for (int i = 0; i < 30; i++)
	{
		_rocks[i]->Render(hdc);
	}
}
