#include <iostream>

using namespace std;

// 조건문
// if문
// if(조건절(true / false))
// {
//		실행문
// }
// else if(조건절)
// {
//		실행문
// }
// else
// {
//		실행문
// }

// switch 문
// switch(양의 정수형 변수)
// {
//		case 1: { 실행문 break; }
//		case 2: { 실행문 break; }
//      case ...:
// 
//		default:
//      {
//		}
// }

// 반복문
// while
// while(조건절)
// {
//		if문(제어식)
//			continue; 실행문이 실행되기 전에 다음 루프 타주세요.
//		실행문
//		제어식
//		break;
// }
// 
// for문
// for(초기식; 조건식; 제어식)
// {
//		continue;
//		실행문
//		break;
// }

int main()
{
	int aInt = 3;
	int bInt = 3;

#pragma region 조건문
	if (aInt > bInt)
	{
		cout << "aInt가 bInt보다 큽니다." << endl;
	}
	else if (aInt == bInt)
	{
		cout << "aInt가 bInt와 동일합니다." << endl;
	}
	else
	{
		cout << "aInt가 bInt보다 작거나 같습니다." << endl;
	}

	// 열거형 (자료형)
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
		cout << "aInt가 1입니다." << endl;
		break;
	}
	case 3:
	{
		cout << "aInt가 3입니다." << endl;
		break;
	}

	default:
	{
		cout << "aInt가 뭔지 잘모르겠습니다." << endl;
		break;
	}
	}

#pragma endregion

#pragma region 반복문

	aInt = 0;
	while (true)
	{
		if (aInt == 3)
		{
			aInt++;
			continue;
		}

		cout << "반복!" << aInt << endl;

		aInt++; // 제어식
		if (aInt == 5)
			break;
	}

	for (int i = 0; i < 10; i++)
	{
		if (i == 3) continue;
		cout << i << "번 반복!" << endl;
		if (i == 5) break;
	}

#pragma endregion

	// 실습
	int input = 0;
	cin >> input;

	cout << input << endl;

	// 실습 1
	// 5 입력하면
	// *
	// *
	// *
	// *
	// *


	// 실습 2번 정사각형 만들기
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



	// 컴퓨터가 난수를 갖게하는 방법
	srand(time(NULL));

	// 1 ~ 3
	// 0 ~ 2 + 1
	int randNum = (rand() % 3) + 1; // 
	cout << randNum << endl;


	return 0;
}