#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct Item
{
	Item(int price, int tier, int atk) : price(price), tier(tier), atk(atk) {}

	int price;
	int tier;
	int atk;
};


int main()
{
	srand(time(nullptr));

	vector<Item*> items;

	for (int i = 0; i < 10; i++)
	{
		int tier = rand() % 10;
		Item* item = new Item(tier * 100, tier, tier * 5);

		items.push_back(item);
	}

	struct ItemFinder_Tier
	{
		bool operator()(Item* item)
		{
			if (item->tier == tier)
				return true;
			return false;
		}

		int tier;
	};

	ItemFinder_Tier finder;
	finder.tier = 0;

	items.erase(std::remove_if(items.begin(), items.end(), finder), items.end());

	int capture = 1;
	int* capture_ptr = new int(1);
	items.erase(std::remove_if(items.begin(), items.end(), [capture](const Item* item) -> bool
	{
			if (item->tier == capture)
				return true;
			return false;

	}), items.end());

	std::sort(items.begin(), items.end(), [](Item* a, Item* b) -> bool
		{
			if (a->price > b->price)
				return true;
			return false;
		});

	return 0;
}