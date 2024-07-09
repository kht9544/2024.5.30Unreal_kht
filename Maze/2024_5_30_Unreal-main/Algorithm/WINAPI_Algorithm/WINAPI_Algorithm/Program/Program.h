#pragma once
class Program
{
public:
	Program();
	~Program();

	void Update();

	void Render(HDC hdc);

	static HDC backBuffer;


private:
	shared_ptr<class Scene> _scene;

	HBITMAP _hBitMap;
};

