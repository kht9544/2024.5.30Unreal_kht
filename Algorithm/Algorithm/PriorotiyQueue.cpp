
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>
#include <concurrent_priority_queue.h>

using namespace std;


class Priority_queue
{
public:
	void push(const int& value)
	{
		int now = _container.size()-1;

		_container.push_back(value);
		
		while (true)
		{
			if (now <= 0)
				break;
			int parent = (now-1) / 2;
		
			if (_container[parent] > _container[now])
				break;

			std::swap(_container[now], _container[parent]);
			now = parent;
		}
		
	}
	void pop()
	{
		_container[0] = _container.back();
		_container.pop_back();

		int now = 0;
		while (true)
		{
			int leftChild = now * 2 + 1;
			int rightChild = now * 2 + 2;

			if (leftChild >= (int)_container.size())
			{
				break;
			}
			int next = now;
			if (_container[next] < _container[leftChild])
			{
				next = leftChild;
			}

			if (_container[next] < _container[rightChild] && rightChild < (int)_container.size())
			{
				next = rightChild;
			}

			if (next == now)
			{
				break;
			}

			std::swap(_container[now], _container[next]);
			now = next;

		}
	}

	const int& top()
	{
		return _container.front();
	}

	bool empty()
	{
		return _container.size()==0;
	}

private:
	vector<int> _container;
};


int main()
{

	Priority_queue pq;

	pq.push(5);
	pq.push(10);
	pq.push(50);
	pq.push(100);
	pq.push(70);
	pq.push(30);
	pq.push(40);


	while (true)
	{
		if (pq.empty())
			break;

		int top = pq.top();

		pq.pop();
		cout << top << '\n';
	}

	return 0;
}

