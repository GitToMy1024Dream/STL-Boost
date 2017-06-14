#include <iostream>
#include <deque>
using namespace std;
template<class T,class Sequeue = deque<T>>
class Myqueue
{
public:
	Myqueue()
		:s()
	{}
	void Push(const T& x)//入队列 头插
	{
		s.push_back(x);
	}
	void Pop()//出队列 尾删
	{
		s.pop_front();
	}
	bool Empty()//判断队列是否为空
	{
		return s.empty();
	}
	size_t Size()const//队列大小
	{
		return s.size();
	}
	T& Front()//返回队头的引用
	{
		return s.front();
	}
	const T& Front()const
	{
		return s.front();
	}
	T& Back()//返回队尾的引用
	{
		return s.back();
	}
	const T& Back()const
	{
		return s.back();
	}
private:
	//重载==运算符
	friend bool operator==(const Myqueue&x, const Myqueue& y);
	//重载小于运算符
	friend bool operator<(const Myqueue&x, const Myqueue&y);
	deque<T> s;
};
 
template<class T,class Sequence>
bool operator==(const Myqueue<T, Sequence>&x, const Myqueue<T, Sequence>& y)
{
	return x.s == y.s;
}
template<class T, class Sequence>
bool operator<(const Myqueue<T, Sequence>&x, const Myqueue<T, Sequence>& y)
{
	return x.s < y.s;
}