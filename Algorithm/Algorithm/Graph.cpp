#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;

vector<vector<int>> adjacent_list;

void CreateGraph_Adjacent()
{
	adjacent_list = vector<vector<int>>(7, vector<int>());

	adjacent_list[0].push_back(1);
	adjacent_list[0].push_back(2);
	adjacent_list[0].push_back(4);
	
	adjacent_list[1].push_back(0);

	adjacent_list[2].push_back(0);
	adjacent_list[2].push_back(3);
	adjacent_list[2].push_back(5);

	adjacent_list[3].push_back(2);

	adjacent_list[4].push_back(0);
	adjacent_list[4].push_back(6);
	
	adjacent_list[5].push_back(2);
	
	adjacent_list[6].push_back(4);
}

vector<vector<bool>>adjacent_Matrix;

void CreateGraph_AdjacentMatrix()
{
	// -- 0 1 2 3 4 5 6
	//  0 T T T 0 T 0 F
	//  1 T T F F F F F 
	//  2 1 0 1 1 0 1 0
	//  3 
	//  4
	//  5
	//  6
	
	adjacent_Matrix = vector<vector<bool>>(7,vector<bool>(7,false));

	adjacent_Matrix[0][0] = true;
	adjacent_Matrix[0][1] = true;
	adjacent_Matrix[0][2] = true;
	adjacent_Matrix[0][4] = true;

	adjacent_Matrix[1][0] = true;
	adjacent_Matrix[1][1] = true;
	
	adjacent_Matrix[2][0] = true;
	adjacent_Matrix[2][2] = true;
	adjacent_Matrix[2][3] = true;
	adjacent_Matrix[2][5] = true;
	
	adjacent_Matrix[3][2] = true;
	adjacent_Matrix[3][3] = true;
	
	adjacent_Matrix[4][0] = true;
	adjacent_Matrix[4][4] = true;
	adjacent_Matrix[4][6] = true;

	adjacent_Matrix[5][2] = true;
	adjacent_Matrix[5][5] = true;

	adjacent_Matrix[6][4] = true;
	adjacent_Matrix[6][6] = true;

}




int main() 
{
	CreateGraph_Adjacent();
	CreateGraph_AdjacentMatrix();

	for (auto i : adjacent_list[5])
	{
		if (i == 4)
		{
			cout << "4발견" << '\n';
		}
	}

	if (adjacent_Matrix[0][2])
		cout << "0,2발견" << '\n';

	if (adjacent_Matrix[5][4])
		cout << "5,4발견" << '\n';


	return 0;
}