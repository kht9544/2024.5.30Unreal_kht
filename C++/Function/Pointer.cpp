#include <iostream>

using namespace std;

void AddOne(int num)
{
	num++;
}

void AddOne(int* ptr)
{
	(*ptr)++;
}


int main()
{
	int aInt = 5;	   

	int* aPtr = &aInt; 

	cout << "&aInt" << &aInt << endl;
	cout << "aInt" << aInt << endl;
	cout << "&aPtr" << &aPtr << endl;
	cout << "aPtr" << aPtr << endl;

	cout << *aPtr << endl; 
	*aPtr = 6;

	cout << aInt << endl;

	void* vPtr = &aInt;
	
	aInt = 0;
	AddOne(&aInt);

	cout << aInt << endl;

	return 0;
}