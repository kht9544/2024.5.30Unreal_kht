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


void Dijkstra(int start)
{
	parent = vector<int>(adjacent.size(), -1);
	vector<int> best(adjacent.size(),INT_MAX);
	priority_queue < Vertex, vector<Vertex>,greater<Vertex>> pq;
	
	Vertex startV = Vertex(0, 0);
	best[start] = 0;
	pq.push(startV);

	parent[start] = start;
	
	while (true)
	{
		if (pq.empty())
			break;
		
		Vertex hereV = pq.top();
		pq.pop();

		if (best[hereV.vertexNum < hereV.g])
		{
			cout << hereV.vertexNum << '\n';
			cout << hereV.g << '\n';
			cout << best[hereV.vertexNum] << '\n';
			continue;
		}

		for (int there = 0; there < adjacent.size(); there++)
		{
			if (hereV.vertexNum == there)continue;

			if (adjacent[hereV.vertexNum][there]==-1)continue;

			int newCost = best[hereV.vertexNum] + adjacent[hereV.vertexNum][there];
			if (newCost >= best[there])
				continue;

			Vertex thereV = Vertex(there, newCost);
			pq.push(thereV);
			best[there] = newCost;
			parent[there] = hereV.vertexNum;
		}
	}
	for (int i = 0; i < adjacent.size(); i++)
	{
		cout <<  parent[i] << '\n';
		cout  << i << "cost :" << best[i] << '\n';
	}

}



int main()
{
	CreateGraph_AdjacentMatrix();
	Dijkstra(0);



	return 0;

}