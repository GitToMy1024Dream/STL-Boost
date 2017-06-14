#include <iostream>
#include <list>
using namespace std;
template<class T,class Sequeue = list<T>>
class Myqueue
{
public:
	Myqueue()
		:s()
	{}
	void Push(const T& x)//入队列，尾插
	{
		s.push_back(x);
	}
	void Pop()//出队列，头插
	{
		s.pop_front();
	}
	size_t Size()const//队列大小
	{
		return s.size();
	}
	T& Back()//返回队尾的引用
	{
		return s.back();
	}
	const T& Back()const
	{
		return s.back();
	}
	T& Front()//返回队头的引用
	{
		return s.front();
	}
	const T& Front()const
	{
		return s.front();
	}
	bool Empty()//判断队列是否为空
	{
		return s.empty();
	}
private:
	list<T> s;
};