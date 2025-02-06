#include <iostream>

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

Item* FindItem_Price(Item* arr, int size, int price)
{
	Item* result = nullptr;

	for (int i = 0; i < size; i++)
	{
		if (arr[i].price == price)
			result = &arr[i];
	}

	return result;
}


Item* FindItem_FuncPtr(Item* arr, int size ,bool(*func)(const Item&))
{
	Item* result = nullptr;
	for (int i = 0; i < size; i++)
	{
		if (func(arr[i]))
			result = &arr[i];
	}

	return result;
}

bool FindItemPtr_Price(const Item& item)
{
	if (item.price == 1500)
		return true;
}

bool FindItemPtr_Tier(const Item& item)
{
	if (item.tier == 5)
		return true;
	return false;
}

struct Finder
{
	bool operator()(const Item& item)
	{
		if (itemPrice == item.price)
			return true;
		return false;
	}

	int itemPrice;
	int itemTier;
	int itemAtk;
};

Item* FindItem_Functor(Item* arr, int size, Finder finder)
{
	Item* result = nullptr;
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

	Item* findItem = FindItem_Price(items, 10,100);
	if (findItem != nullptr)
		findItem->PrintItem();

	findItem = nullptr;
	findItem = FindItem_FuncPtr(items, 10, &FindItemPtr_Tier);
	if (findItem != nullptr)
		findItem->PrintItem();

	Finder finder;

	finder.itemPrice = 1500;
	findItem = FindItem_Functor(items, 10, finder);
	if (findItem != nullptr)
		findItem->PrintItem();

	return 0;
}