#pragma once
class Obstacle
{
public:
	Obstacle();
	~Obstacle();

	void Update();
	void Render(HDC hdc);

	shared_ptr<Collider> GetCollider() { return _block; }
	int GetLengthX() { return _lengx; }
	int GetLengthY() { return _lengy; }


private:
	shared_ptr<Collider> _block;
	int _lengx;
	int _lengy;


};

