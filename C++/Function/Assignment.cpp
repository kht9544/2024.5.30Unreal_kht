#include <iostream>

using namespace std;


int aInt = 0;
short aShort = 1;

float aFloat = 4.0f;

char aChar = 1;

int HelloWorld(int arg)
{
	int hello = 5;
	aChar = 2;

	return 0;
}

int main()
{ 
	int bInt = 2;
	float bFloat = 1.1f;

	{
		int cInt = 2;
		bInt = 3;
	}

	return 0;
} 