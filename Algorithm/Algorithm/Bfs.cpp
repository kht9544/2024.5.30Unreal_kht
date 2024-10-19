#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;


vector<vector<bool>>adjacent;
vector<bool> discovered;
vector<int> parent;

void CreateGraph_AdjacentMatrix()
{
	adjacent = vector<vector<bool>>(7, vector<bool>(7, false));

	adjacent[0][0] = true;
	adjacent[0][1] = true;
	adjacent[0][2] = true;
	adjacent[0][4] = true;

	adjacent[1][0] = true;
	adjacent[1][1] = true;

	adjacent[2][0] = true;
	adjacent[2][2] = true;
	adjacent[2][3] = true;
	adjacent[2][4] = true;
	adjacent[2][5] = true;

	adjacent[3][2] = true;
	adjacent[3][3] = true;

	adjacent[4][0] = true;
	adjacent[4][2] = true;
	adjacent[4][4] = true;
	adjacent[4][6] = true;

	adjacent[5][2] = true;
	adjacent[5][5] = true;

	adjacent[6][4] = true;
	adjacent[6][6] = true;

}

void BFS(int start)
{
	int N = adjacent.size();
	discovered[start] = true;
	parent[start] = start;

	cout << start << "�湮" << '\n';

	queue<int> q;
	q.push(start);

	while (1)
	{
		if (q.empty())
			break;
		int here = q.front();
		q.pop();

		for(int there = 0; there < N; there++ )
		{
			if (!adjacent[here][there])
				continue;
			if (discovered[there])
				continue;

			q.push(there);
			cout << there << "�߰�"<<'\n';
			discovered[there] = true;
			parent[there] = here;
		}
	}
}

int edgeCount(int start, int dest)
{
	int res = 0;
	while (true)
	{
		if (dest == start)
			break;

		dest = parent[dest];
		res++;
	}
	return res;
}

int main()
{
	CreateGraph_AdjacentMatrix();
	int size = adjacent.size();
	discovered = vector<bool>(size, false);
	parent = vector<int>(size, -1);

	BFS(0);

	cout << edgeCount(0,5) << '\n';

	return 0;
}