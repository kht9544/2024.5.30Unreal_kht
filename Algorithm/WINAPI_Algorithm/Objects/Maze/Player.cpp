#include "pch.h"
#include "Player.h"
#include "Maze.h"
#include "Block.h"

Player::Player(shared_ptr<Maze> maze)
{
	_maze = maze;
}

Player::~Player()
{
	_maze = nullptr;
}

void Player::BeginPlay()
{
	_maze->SetPlayerPos(_pos);
	_pos = _maze->GetStartPos();

	visited = vector<vector<bool>>(MAXCOUNT_Y, vector<bool>(MAXCOUNT_X, false));
	parent = vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));
	BFS(_pos);
}

void Player::DFS(Vector2 start)
{
	Vector2 frontPos[4] =
	{
		Vector2 {0,-1}, 
		Vector2 {-1,0}, 
		Vector2 {0,1},  
		Vector2 {1,0}   
	};

	stack<Vector2> s;
	s.push(start);
	visited[start._y][start._x] = true;
	parent[start._y][start._x] = start;

	Vector2 endPos = _maze->GetEndPos();
	bool found = false;

	while (!s.empty())
	{
		Vector2 here = s.top();
		s.pop();

		if (here == endPos)
		{
			found = true;
			break;
		}

		for (int i = 0; i < 4; i++)
		{
			Vector2 there = here + frontPos[i];

			if (!Cango(there._y, there._x))
				continue;

			if (visited[there._y][there._x])
				continue;

			s.push(there);
			visited[there._y][there._x] = true;
			parent[there._y][there._x] = here;
		}
	}

	if (found)
	{
		Vector2 check = endPos;
		_path.push_back(check);

		while (check != start)
		{
			check = parent[check._y][check._x];
			_path.push_back(check);
		}

		std::reverse(_path.begin(), _path.end());
	}


}

void Player::BFS(Vector2 start)
{
	//4방향
	Vector2 frontPos[4] =
	{
		Vector2(0,-1), 
		Vector2(-1,0), 
		Vector2(0,1), 
		Vector2(1,0), 
	};

	vector<vector<bool>>discovered = vector<vector<bool>>(MAXCOUNT_Y,vector<bool>(MAXCOUNT_X,false));
	vector<vector<Vector2>>parent = vector<vector<Vector2>>(MAXCOUNT_Y, vector<Vector2>(MAXCOUNT_X, Vector2(-1, -1)));

	Vector2 pos = start;
	Vector2 endPos = _maze->GetEndPos();

	discovered[start._y][start._x] = true;
	parent[start._y][start._x] = start;

	queue<Vector2> q;
	q.push(start);

	while (true)
	{
		if (q.empty())
			break;

		Vector2 here = q.front();
		q.pop();

		if (here == endPos)
			break;
		
		for (int i = 0; i < 4; i++)
		{
			Vector2 there = here + frontPos[i];

			if (!Cango(there._y, there._x))
				continue;
			
			if (discovered[there._y][there._x])
				continue;

			
			_maze->SetBlockType(there._y, there._x, Block::BlockType::PUT_PRINT);
			q.push(there);
			discovered[there._y][there._x] = true;
			parent[there._y][there._x] = here;
		}
	}
	Vector2 check = endPos;
	_path.push_back(check);
	while (true)
	{
		if (check == start) break;

		check = parent[check._y][check._x];
		_path.push_back(check);
	}
	std::reverse(_path.begin(), _path.end());
}

void Player::Djikstra(Vector2 start)
{

}

void Player::RightHand()
{

	enum Direction
	{
		UP,
		LEFT,
		BOTTOM,
		RIGHT,

		DIR_COUNT = 4
	};

	Vector2 pos = _pos;
	_path.push_back(pos);
	Vector2 endPos = _maze->GetEndPos();

	Direction dir = Direction::BOTTOM;

	Vector2 frontPos[4] =
	{
		Vector2(0,-1), 
		Vector2(-1,0), 
		Vector2(0,1), 
		Vector2(1,0),
	};

	while (true)
	{
		if (pos == endPos)
			break;

		int newDir = (dir + 1 + DIR_COUNT) % DIR_COUNT;
		Vector2 oldDirVector2 = frontPos[dir];
		Vector2 newDirVector2 = frontPos[newDir];

		Vector2 newPos = pos + newDirVector2;
		Vector2 oldPos = pos + oldDirVector2; 
	
		if (Cango(newPos._y, newPos._x)) 
		{
			dir = static_cast<Direction>(newDir);
			pos += newDirVector2;
			_path.push_back(pos);
		}

		else if (Cango(oldPos._y, oldPos._x))
		{
			pos += oldDirVector2;
			_path.push_back(pos);
		}

		else 
		{
			dir = static_cast<Direction>((dir - 1 + DIR_COUNT) % DIR_COUNT);
		}
	}

	stack<Vector2> s;
	for (int i = 0; i < _path.size()-1; i++)
	{
		if (!s.empty() && s.top() == _path[i + 1])
			s.pop();
		else 
			s.push(_path[i]);
	}
	s.push(_path.back());

	_path.clear();

	while (true)
	{
		if (s.empty() == true)
			break;

		_path.push_back(s.top());
		s.pop();
	}

	std::reverse(_path.begin(), _path.end());
}

bool Player::Cango(int y, int x)
{
	Block::BlockType blockType = _maze->GetBlockType(y,x);
	if(blockType == Block::BlockType::ABLE)
		return true;

	return false;
}

void Player::Update()
{
	if (_pathIndex >= _path.size())
	{
		_pathIndex = 0;
		_path.clear();

		return ;
	}

	_time += 0.3f;
	if (_time > 1.0f)
	{
		_time = 0.0f;
		_pos = _path[_pathIndex];

		if (_pathIndex != 0)
		{
			_maze->SetPlayerPos(_pos);
		}

		_pathIndex++;
	
	}
}
