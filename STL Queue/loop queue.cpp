#pragma once
#include <iostream>
using namespace std;
template<class T>
class Queue
{
public:
	Queue(size_t capacity = 5)//构造函数
		:_capacity(capacity + 1)
		, _count(0)
		, _front(0)
		, _rear(0)
	{
		_pData = new T[capacity];//申请空间
	}
	void Push(const T& x)//队列尾插
	{
		//队满
		if (((_rear + 1) % _capacity) == _front && (Size() == _capacity))
		{
			cout << "Queue Full." << endl;
			return;
		}
		_pData[_count] = x;
		_count++;
		_rear = (_rear + 1) % _capacity;
	}
	void Pop()//队列头删
	{
		if (_front == _rear)//队空
		{
			cout << "Queue Empty" << endl;
			return;
		}
		T temp = _pData[_front];
		_pData[_front] = NULL;
		_front = (_front + 1) % _capacity;
		_count--;
	}
	T& Front()//返回队头的引用
	{
		if (Empty())
		{
			cout << "Queue Empty!" << endl;
		}
		return _pData[_front];
	}
	const T& Front()const
	{
		if (Empty())
		{
			cout << "Queue Empty!" << endl;
		}
		return _pData[_front];
	}
	T& Back()//返回队尾的引用
	{
		return _pData[_rear-1];
	}
	const T& Back()const
	{
		return _pData[_rear-1];
	}
	size_t Size()const//队列的大小
	{
		return _count;
	}
	bool Empty()const//判断队列是否为空
	{
		return _front == _rear ;
	}
	~Queue()//析构函数
	{
		if (_pData)
		{
			delete[] _pData;
			_pData = NULL;
			_count = 0;
			_rear = _front = 0;
		}
	}
 
private:
	T* _pData;//保存数据的指针
	size_t _capacity;//容量
	size_t _front;//队头
	size_t _rear;//队尾
	size_t _count;//有效元素个数
};