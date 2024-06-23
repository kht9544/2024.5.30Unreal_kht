#pragma once
class World
{
public:
	enum PlayerType
	{
		NONE = 0,
		KNIGHT = 1,
		ARCHER = 2
	};

	World();
	~World();
	void Init(); // 초기화

	bool End();
	bool MonstersCheck();
	bool playersWin() ;
	bool Battle3PlayerWin();
	bool Battle3BoosWin();

	void Battle1();
	void Battle2(); // 과제
	void Battle3();

private:
	void SelectPlayer(int num, string name, Creature** creature);
	void Input();

	Creature* _player;
	Creature* _computer;
	HobGoblin* _hobgoblin;
	vector<Creature*> _monsters;
	vector<Creature*> players;
};

