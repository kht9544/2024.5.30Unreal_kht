
#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <stack>

using namespace std;


template<typename T>
class Stack
{
public:
    void push(T num) 
    {
        v.push_back(num);
    }
    void pop()
    {
        v.pop_back();
    }
    bool empty()
    {
        return v.size() == 0;
    }
    T top() 
    {
        return v[v.size()-1];
    }

private:
    vector<T> v;
};



int main()
{ 

    Stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);

    while (true)
    {
        if (s.empty())
        {
            break;
        }
        cout << s.top() << '\n';
        s.pop();
    }

    return 0;
}

