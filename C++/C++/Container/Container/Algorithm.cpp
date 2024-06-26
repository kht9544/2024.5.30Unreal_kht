#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool Func(const int& value)
{
	if (value > 15)
		return true;

	return false;
}

int main()
{
	vector<int> myV;

	myV.push_back(3);
	myV.push_back(5);
	myV.push_back(1);
	myV.push_back(7);
	myV.push_back(11);

	myV.push_back(21);
	myV.push_back(2);
	myV.push_back(4);
	myV.push_back(3);
	myV.push_back(3);

	int index = 0;
	vector<int>::iterator iter;
	// 1이 있는지 찾아주세요. 그리고 index나 혹은 iterator자리를 찾아주세요

	for (int i = 0; i < myV.size(); i++)
	{
		if (myV[i] == 1)
		{
			index = i;
			break;
		}
	}

	for (iter = myV.begin(); iter != myV.end(); iter++)
	{
		if (*iter == 1)
			break;
	}

	cout << myV[index] << endl;
	cout << (*iter) << endl;
	
	iter = std::find(myV.begin(), myV.end(), 1);
	if (iter != myV.end())
		cout << *iter << endl;


	// 15보다 큰 수가 있는지 찾아주세요. 그리고 index나 혹은 iterator 자리를 찾아주세요.
	struct Finder_1
	{
		bool operator()(const int& value)
		{
			if (value > compareNum)
				return true;
			return false;
		}
		int compareNum = 0;
	};

	Finder_1 finder_1;
	finder_1.compareNum = 15;

	iter = std::find_if(myV.begin(), myV.end(), finder_1);
	cout << *iter << endl;

	// 모든 수가 50보다 작은지 bool으로 알려주세요.

	// 하나라도 30보다 큰 수가 있는지 bool으로 알려주세요.

	// 원소가 3인 원소들의 개수를 알려주세요.

	// 원소가 5보다 큰 원소들의 개수를 알려주세요.

	// 모든 원소에 3을 곱해주세요.

	// 중복된 원소들을 '제거'해주세요.

	// 원소가 12인 원소를 지워주세요.

	// 원소가 10보다 작은 원소들을 지워주세요.

	return 0;
}