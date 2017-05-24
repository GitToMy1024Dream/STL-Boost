//List.h
#pragma once
#include <iostream>
#include <Windows.h>
#include <cassert>
using namespace std;
template<class T>
struct ListNode
{
	ListNode(const T& x = T())//构造值为x的节点
		: _prev(0)
		, _next(0)
		, _value(x)
	{}
 
	ListNode<T>* _prev;//前驱指针
	ListNode<T>* _next;//后继指针
	T _value;//值域
};
 
template<class T, class Ref, class Ptr>
struct __ListIterator__  //双向迭代器类型的结构体
{
	typedef __ListIterator__<T, T&, T*> Iterator;//迭代器类型
	typedef __ListIterator__<const T, const T&, const T*> ConstIterator;//常量迭代器类型
	typedef __ListIterator__<T, Ref, Ptr> Self;//引用类型
	typedef T ValueType;//值域类型
	typedef Ref Reference;//引用类型
	typedef Ptr Pointer;//指针类型
	typedef ListNode<T>* LinkType;//链表指针类型
	typedef size_t SizeType;//无符号类型
	LinkType _node;//指向结点的指针
 
	__ListIterator__(LinkType x)//构造值为x的节点
		:_node(x)
	{}
	__ListIterator__()//构造空链表
	{}
	__ListIterator__(const Iterator& x)//拷贝x节点
	{
		_node = x._node;
	}
	bool operator==(const Iterator& x)//比较运算符==的重载
	{
		return _node == x._node;
	}
	bool operator!=(const Iterator& x)//比较运算符！=的重载
	{
		return _node != x._node;
	}
	Reference operator*()//重载*运算符
	{
		return _node->_value;
	}
	Pointer operator->()//重载->运算符
	{
		return &(_node->_value);
	}
	Self& operator++()//重载前置++运算符
	{
		_node = _node->_next;
		return *this;
	}
	Self operator++(int)//重载后置++运算符
	{
		Self tmp(*this);
		_node = _node->_next;
		return tmp;
	}
	Self& operator--()//重载前置--运算符
	{
		_node = _node->_prev;
		return *this;
	}
	Self operator--(int)//重载后置--运算符
	{
		Self tmp(*this);
		_node = _node->_prev;
		return tmp;
	}
};
 
template<class T>
class List  //双向循环链表类
{
public:
	typedef ListNode<T> Node;//双向循环链表的结点
	typedef T ValueType;//值域为T类型的结点
	typedef ValueType* Pointer;//指针类型
	typedef const ValueType* ConstPointer;//常量指针类型
	typedef ValueType& Reference;//引用类型
	typedef const ValueType& ConstReference;//常量引用类型
	typedef Node* LinkType;//结点指针类型
	typedef size_t SizeType;//无符号类型
	typedef __ListIterator__<T, T&, T*> Iterator;//迭代器类型
	typedef __ListIterator__<const T, const T&, const T*> ConstIterator;//常量迭代器类型
	List() //构造函数
		:_pHead(new Node(T()))
	{
		_pHead->_next = _pHead;
		_pHead->_prev = _pHead;
	}
	Iterator Begin()//返回第一个节点的下一个节点的迭代器(头结点的下一个节点)
	{
		return _pHead->_next;
	}
	ConstIterator Begin()const//返回第一个节点的下一个节点的常量迭代器(头结点的下一个节点)
	{
		return _pHead->_next;
	}
	Iterator End()//返回最后一个节点的下一个节点的迭代器(头结点)
	{
		return _pHead;
	}
	ConstIterator End()const//返回最后一个节点的下一个节点的常量迭代器(头结点)
	{
		return _pHead;
	}
	bool Empty()const//判断链表是否为空
	{
		return _pHead == _pHead->_next;
	}
	SizeType Size()const //返回链表节点个数
	{
		SizeType count = 0;
		for (Iterator it = Begin(); it != End(); it++)
		{
			count++;
		}
		return count;
	}
	Reference Front()//返回第一个节点的引用
	{
		return _pHead->_next->_value;
	}
	ConstReference Front()const //返回第一个节点的常量引用
	{
		return _pHead->_next->_value;
	}
	Reference Back()//返回最后一个节点的引用
	{
		return _pHead->_prev->_value;
	}
	ConstReference Back()const //返回最后一个节点的常量引用
	{
		return _pHead->_prev->_value;
	}
	Iterator Insert(Iterator pos, const T& x) //在pos位置前插入
	{
		LinkType NewNode = new Node(x);
		LinkType cur = pos._node;
		NewNode->_next = cur;
		cur->_prev->_next = NewNode;
		NewNode->_prev = cur->_prev;
		cur->_prev = NewNode;
		return Iterator(NewNode);
	}
	void PushFront(const T& x) //头差
	{
		Insert(Begin(), x);
	}
	void PushBack(const T& x)
	{
		Insert(End(), x);
	}
	Iterator Erase(Iterator pos) //删除pos位置的节点
	{
		assert(pos != End());
		LinkType pTemp = pos._node;
		LinkType pDel = pTemp;
		pTemp->_prev->_next = pTemp->_next;
		pTemp->_next->_prev = pTemp->_prev;
		delete pDel;
		pDel = NULL;
		return pTemp;
	}
	void PopFront() //头删
	{
		Erase(Begin());
	}
	void PopBack() //尾删
	{
		Erase(--End());
	}
	void Clear() //清空链表
	{
		while (!Empty())
		{
			PopBack();
		}
	}
	List(const List<T>& l) //构造函数
	{
		_pHead = new Node;
		LinkType pTmp = l.Begin();
		while (pTmp != l.End())
		{
			pTmp++;
			PushBack(pTmp->_value);
		}
	}
	List& operator=(const List& l) //赋值运算符的重载
	{
		_pHead = new Node;
		LinkType pTmp = l.Begin();
		while (pTmp != l.End())
		{
			pTmp++;
			PushBack(pTmp->_value);
		}
	}
	~List() //析构函数
	{
		Clear();
		delete _pHead;
		_pHead = NULL;
	}
 
protected:
	LinkType _pHead;//指向头结点的指针
};