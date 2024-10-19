#include <iostream>

using namespace std;

unsigned char state = 0;
unsigned char sturn = 0b1000; 
unsigned char sleep = (1 << 2);
unsigned char airbone = 2;
unsigned char invinsible = 1;


int main()
{
#pragma region ������
	int aInt = 10;
	int bInt = 3;
	int cInt = 0;

	cInt = (aInt + bInt) % bInt;
	cout << cInt << endl;

	float aFloat = 0.0f;
	float cFloat = 10.0f / aFloat;
	cout << cFloat << endl;

	aInt += 1; 

	cout << ++aInt << endl; 
	cout << aInt++ << endl; 
	cout << aInt << endl; 

	aInt = ++bInt;
	aInt = bInt++;
	cout << aInt << endl; 
	cout << (aInt > bInt) << endl;
	cout << ((aInt < bInt) > (aInt == bInt)) << endl; 

	aInt = 2;
	bInt = 3;
	cInt = ++bInt;

	bool check1 = (aInt > bInt);
	bool check2 = (cInt != aInt);
	bool check3 = !check1;

	bool check4 = check3 || check2;
	bool check5 = check2 && (check3 || check4);

	cout << (1 & 2) << endl;
	cout << (1 | 3) << endl;

	aInt = 1;
	bInt = 3;
	cInt = (aInt ^ bInt);
	cout << (cInt ^ bInt) << endl;

	unsigned char u_aChar = 3;
	unsigned char u_bChar = (1 << 4);
	unsigned char u_cChar = (u_aChar | u_bChar);
	unsigned char u_dChar = (1 << 3) | (1 << 2);
	unsigned char u_fChar = (u_cChar & u_dChar);
#pragma endregion

#pragma region ��Ʈ�÷���
	state |= (sturn | sleep);
	if (state & sturn)
	{
		cout << "Stun" << endl;
	}

	if (state & sleep)
	{
		cout << "sleep " << endl;
	}

	if (state & (sleep | sturn))
	{
		cout << "sleep stun" << endl;
	}

#pragma endregion

	return 0;
}