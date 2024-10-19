#include <iostream>

using namespace std; 

unsigned short u_aShort = 1;
unsigned int u_aInt = 5; 

struct Pos
{
	int x;
	int y;
};

int main() 
{
	short aShort = -32768 - 1; 
	int aInt = 1;
	__int64 aInt64 = 241313;

	float aFloat = 1.25f;
	double aDouble = 1.222;

	bool aBool = -1;

	char aChar = 97;

	Pos aPos;
	aPos.x = 1;
	aPos.y = 2;

	Pos bPos;
	bPos.x = 3;
	bPos.y = 3;

	cout << sizeof(aPos) << endl;

	int sum = aInt + 5;

	return 0;
}