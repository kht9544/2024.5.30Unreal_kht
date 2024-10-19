#include <iostream>
#include <vector>
#include <list>

using namespace std;

#include "Vector.h"
#include "List.h"

template<typename T, typename Container>
void PrintTemp(T t, Container container)
{
	t = container.begin();
	for (t; t != container.end(); t++)
	{
		cout << *t << endl;
	}
}

int main()
{
	List<int> myList;

	myList.PushBack(5);
	myList.PushBack(3);
	myList.PushBack(2);
	myList.PushBack(1);

	List<int>::Iterator myIter = myList.begin();

	for (myIter; myIter != myList.end(); myIter++)
	{
		cout << *myIter << endl;
	}

	PrintTemp<List<int>::Iterator, List<int>>(myIter, myList);

	return 0;
}