#include "pch.h"
#include "Obstacle.h"

Obstacle::Obstacle()
{
	_lengx = 30;
	_lengy = 10;

	_block = make_shared<RectCollider>(Vector2(WIN_WIDTH*0.5 - 300,10), Vector2(_lengx,_lengy));
}

Obstacle::~Obstacle()
{

}

void Obstacle::Update()
{
	_block->Update();
}

void Obstacle::Render(HDC hdc)
{
	_block->Render(hdc);
}
