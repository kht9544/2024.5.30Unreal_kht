#include "pch.h"
#include "Maze.h"

#include "Block.h"

Maze::Maze()
{
	Vector2 offSet = Vector2(500,200);

	_blocks.reserve(MAXCOUNT_Y);

	for (int i = 0; i < MAXCOUNT_Y; i++)
	{
		vector<shared_ptr<Block>> blocks_X;
		blocks_X.reserve(MAXCOUNT_X);

		for (int j = 0; j < MAXCOUNT_X; j++)
		{
			Vector2 blockOffset = offSet + Vector2(16.0f * j, 16.0f * i);

			shared_ptr<Block> block = make_shared<Block>();
			block->SetBlockType(Block::BlockType::DISABLE);
			block->SetPosition(blockOffset);
			blocks_X.push_back(block);
		}

		_blocks.push_back(blocks_X);
	}

	CreateMaze();
}

Maze::~Maze()
{
}

void Maze::Update()
{
	for (auto blocks_X : _blocks)
	{
		for (auto block : blocks_X)
		{
			block->Update();
		}
	}
}

void Maze::Render(HDC hdc)
{
	for (auto blocks_X : _blocks)
	{
		for (auto block : blocks_X)
		{
			block->Render(hdc);
		}
	}
}

void Maze::CreateMaze()
{

	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x % 2 == 0 || y % 2 == 0)
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::DISABLE);
			}
			else
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
			}
		}
	}

	for (int y = 0; y < MAXCOUNT_Y; y++)
	{
		for (int x = 0; x < MAXCOUNT_X; x++)
		{
			if (x == 1 && y == 1)
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
			}

			if (x == MAXCOUNT_X - 2 && y == MAXCOUNT_Y - 2) 
			{
				_blocks[y][x]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}

			if (x % 2 == 0 || y % 2 == 0)
				continue;

			if (x == MAXCOUNT_X - 2)
			{
				_blocks[y + 1][x]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}

			if (y == MAXCOUNT_Y - 2)
			{
				_blocks[y][x + 1]->SetBlockType(Block::BlockType::ABLE);
				continue;
			}


			int randValue = rand() % 2;
			if(randValue == 0)
				_blocks[y][x + 1]->SetBlockType(Block::BlockType::ABLE);
			else
				_blocks[y+1][x]->SetBlockType(Block::BlockType::ABLE);
		}
	}
}

Block::BlockType Maze::GetBlockType(int y, int x)
{
	return _blocks[y][x]->GetBlockType();
}

void Maze::SetBlockType(int y, int x, Block::BlockType type)
{
	_blocks[y][x]->SetBlockType(type);
}

void Maze::SetPlayerPos(Vector2 pos)
{
	_blocks[pos._y][pos._x]->SetBlockType(Block::BlockType::PLAYER_POS);
}
