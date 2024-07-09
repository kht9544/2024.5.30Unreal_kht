#include "pch.h"
#include "CannonScene.h"
#include "Objects/Cannon.h"
#include "Objects/Bullet.h"
#include "Objects/Obstacle.h"

// 사양서
// 턴제 포트리스
// 각 cannon을 턴마다 서로 컨트롤을 받아서 공격
// cannon의 HP는 5
// 맞으면 hp - 1, hp가 0이면 cannon이 사라짐

CannonScene::CannonScene()
{
	for (int i = 0; i < 10; i++)
	{
		shared_ptr<Obstacle>_obstacle = make_shared<Obstacle>();
		_obstacle->GetCollider()->_center._x += 100 * i;
		_rocks.push_back(_obstacle);    
	}
	_cannon1 = make_shared<Cannon>();
	_cannon2 = make_shared<Cannon>();

	_cannon1->isControlled = true;

	// Attack2
	for (auto bullet : _cannon1->GetBullets())
	{
		bullet->SetTarget(_cannon2);
	}
	for (auto bullet : _cannon2->GetBullets())
	{
		bullet->SetTarget(_cannon1);
	}
}

CannonScene::~CannonScene()
{

}

void CannonScene::Update()
{
	_cannon1->Update();
	_cannon2->Update();

	for (int i = 0; i < 10; i++)
	{
		_rocks[i]->Update();
	}



}

void CannonScene::Render(HDC hdc)
{
	for (int i = 0; i < 10; i++)
	{
		_rocks[i]->Render(hdc);
	}
	_cannon1->Render(hdc);
	_cannon2->Render(hdc);
}
