#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;

struct Vertex
{
	Vertex() {}
	Vertex(int vertexNum, int g) : vertexNum(vertexNum), g(g) {}

	int vertexNum = 0;
	int g = 0;

	bool operator<(const Vertex& other)const
	{
		if (g < other.g)
			return true;
		return false;
	}

	bool operator>(const Vertex& other)const
	{
		if (g > other.g)
			return true;
		return false;
	}
};

vector<vector<int>>adjacent;
vector<bool> discovered;
vector<int> parent;



void CreateGraph_AdjacentMatrix()
{
	adjacent = vector<vector<int>>(7, vector<int>(7, -1));

	adjacent[0][0] = 0;
	adjacent[0][1] = 3;
	adjacent[0][2] = 2;
	adjacent[0][4] = 10;

	adjacent[1][0] = 3;
	adjacent[1][1] = 0;

	adjacent[2][0] = 2;
	adjacent[2][2] = 0;
	adjacent[2][3] = 7;
	adjacent[2][4] = 3;
	adjacent[2][5] = 5;

	adjacent[3][2] = 7;
	adjacent[3][3] = 0;

	adjacent[4][0] = 10;
	adjacent[4][2] = 3;
	adjacent[4][4] = 0;
	adjacent[4][6] = 4;

	adjacent[5][2] = 5;
	adjacent[5][5] = 0;

	adjacent[6][4] = 4;
	adjacent[6][6] = 0;

}




int main()
{



	return 0;

}