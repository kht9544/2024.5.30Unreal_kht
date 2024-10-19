#include <iostream>

using namespace std;

int main()
{
	int aInt = 3;
	int bInt = 3;

#pragma region ���ǹ�
	if (aInt > bInt)
	{
		cout << "aInt> bInt." << endl;
	}
	else if (aInt == bInt)
	{
		cout << "aInt -- bInt." << endl;
	}
	else
	{
		cout << "bInt < aInt." << endl;
	}

	enum Test
	{
		ONE = 1,
		TWO,
		THREE
	};

	Test aTest = ONE;

	switch (aTest)
	{
	case ONE:
		break;
	case TWO:
		break;
	case THREE:
		break;
	default:
		break;
	}

	switch (aInt)
	{
	case 1:
	{
		cout << "aInt 1." << endl;
		break;
	}
	case 3:
	{
		cout << "aInt 3" << endl;
		break;
	}

	default:
	{
		cout << "aInt" << endl;
		break;
	}
	}

#pragma endregion

#pragma region �ݺ���

	aInt = 0;
	while (true)
	{
		if (aInt == 3)
		{
			aInt++;
			continue;
		}

		cout <<aInt << endl;

		aInt++; 
		if (aInt == 5)
			break;
	}

	for (int i = 0; i < 10; i++)
	{
		if (i == 3) continue;
		cout << i << endl;
		if (i == 5) break;
	}

#pragma endregion


	int input = 0;
	cin >> input;

	cout << input << endl;

	for (int i = 0; i < input; i++)
	{
		for (int j = 0; j < input; j++)
		{
			cout << "*";
		}
		cout << endl;
	}

	cout << endl;
	cout << "Hello World!" << endl;

	srand(time(NULL));

	int randNum = (rand() % 3) + 1; 
	cout << randNum << endl;


	return 0;
}