#include <iostream>

using namespace std;


enum RSP
{
	SCISSORS = 1,
	ROCK = 2,
	PAPER = 3
};

int main()
{
	srand(time(NULL));
	
	int playerNum = 0;
	int cumNum = 0;
	cin >> playerNum;

	cumNum = (rand() % 3) + 1;

	return 0;
}