#pragma once

class ArkanoidScene : public Scene
{
public:
	ArkanoidScene();
	~ArkanoidScene();

	void Update() override;
	void Render(HDC hdc) override;
private:
	vector<shared_ptr<class Obstacle>> _rocks;
	shared_ptr<class Cannon> _cannon1;

	shared_ptr<class Bullet> _ball;
	

};

