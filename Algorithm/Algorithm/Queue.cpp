
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>
#include <queue>

using namespace std;


template<typename T, typename Container = list<T>>
class Queue 
{
public:
    void push(const T& num)
    {
        v.push_back(num);
    }

    void pop()
    {
        v.pop_front();
    }

    T front()
    {
        return v.front();
    }

    bool empty()
    {
        if (v.empty())
            return true;
        else
            return false;
    }

private:
    Container v;
};


int main()
{
    queue<int,list<int>> q;
    q.push(423);
    q.push(433);
    q.push(43);
    q.push(3);

    while (1)
    {
        if (q.empty())
        {
            break;
        }
        cout << q.front() << '\n';
        q.pop();
    }



    return 0;
}

