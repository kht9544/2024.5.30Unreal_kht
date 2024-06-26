#include <iostream>
#include <algorithm>

using namespace std;

struct Item
{
	void PrintItem()
	{
		cout << "Price : " << price << endl;
		cout << "Tier  : " << tier << endl;
		cout << "Atk   : " << atk << endl;
	}

	int price;
	int tier;
	int atk;
};

struct Finder
{
	bool operator()(const Item& item)
	{
		if (tier == item.tier && price == item.price)
			return true;
		return false;
	}

	int price;
	int tier;
	int atk;
};

struct Finder_All
{
	bool operator()(const Item& item)
	{
		if (tier == item.tier && price == item.price && atk == item.atk)
			return true;
		return false;
	}

	int price;
	int tier;
	int atk;
};

struct Finder_Two
{
	bool operator()(const Item& item)
	{
		if (tier == item.tier && atk == item.atk)
			return true;
		return false;
	}

	int price;
	int tier;
	int atk;
};

template <typename I, typename T>
I* FindBy_Functor(I arr[], int size, T finder)
{
	I* result = nullptr;

	for (int i = 0; i < size; i++)
	{
		if (finder(arr[i]))
			result = &arr[i];
	}

	return result;
}


int main()
{
	Item items[10];
	for (int i = 0; i < 10; i++)
	{
		items[i].price = 500 * (i + 1) * 3;
		items[i].tier = (10 - i);
		items[i].atk = 10 * (i + 1);
	}

	// 함수 포인터를 사용해서
	// tier가 8인 얘를 찾아서 출력

	// 함수 객체를 사용해서
	// price가 9000이고 tier 5
	Finder finder;
	finder.price = 9000;
	finder.tier = 5;
	Item* item = FindBy_Functor<Item, Finder>(items, 10, finder);
	if (item != nullptr)
		item->PrintItem();
	item = nullptr;
	// 함수 객체를 사용해서
	// price 3000, tier 9, atk 20 얘를 찾아서 출력
	Finder_All finder_All;
	finder_All.price = 3000;
	finder_All.tier = 9;
	finder_All.atk = 20;
	item = FindBy_Functor<Item,Finder_All>(items, 10, finder_All);
	if (item != nullptr)
		item->PrintItem();

	// 함수 객체와 템플릿을 사용해서
	// tier 9, atk 20
	Finder_Two finder_two;
	finder_two.tier = 9;
	finder_two.atk = 20;
	item = FindBy_Functor<Item, Finder_Two>(items, 10, finder_two);
	if (item != nullptr)
		item->PrintItem();

	int arr[10] = { 5,2,3,24,13,5,2,3,21,4 };

	struct Comparer
	{
		bool operator()(const int& a, const int& b)
		{
			if (a <= 5)
				return false;

			return a > b;
		}
	};

	Comparer comparer;
	std::sort(&arr[0], &arr[9], comparer);

	return 0;
}