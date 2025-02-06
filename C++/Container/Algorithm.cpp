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


	return 0;
}