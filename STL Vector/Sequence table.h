#pragma once
#include <iostream>
#include <Windows.h>
#include <assert.h>
using namespace std;
typedef int DataType;
class Vector
{
public:
	explicit Vector(size_t capacity = 3)
	{
		_pData = (DataType*)malloc(capacity * sizeof(DataType));
		_capacity += 3;
		_size = 0;
	}
	//构造函数 有size个值为data的元素
	Vector(size_t n, const DataType& data)
	{
		_pData = (DataType*)malloc(_capacity * sizeof(DataType));
		_size = n;
		_capacity = n;
		for(size_t idx = 0;idx < _size;++idx)
		{
			_pData[idx] = data;
		}
	}
	//拷贝构造
	Vector(const Vector& v)
		: _capacity(v._capacity)//容量
		, _size(v._size)//有效元素的个数
	{
		_pData = new DataType[_capacity];
		// 比较1和2的优缺点？
		// 1 memcpy如果src与dst指向的内存空间重叠，则不能保证是否内容覆盖
		//memcpy(_pData, v._pData, sizeof(DataType)*_size);
		// 2 效率较低，但比较安全
		for(size_t idx = 0; idx < _size; ++idx)
			_pData[idx] = v._pData[idx];
	}
	//重载赋值运算符
	Vector& operator=(const Vector& v)
	{
		if(this != &v)
		{
			_pData = v._pData;
			_size = v._size;
			_capacity = v._capacity;
		}
	}
	//析构函数
	~Vector()
	{
		if(_pData != NULL)
		{
			free(_pData);
			_pData = NULL;
			_size = 0;
			_capacity = 0;
		}
	}
	void PushBack(const DataType& data);//尾插
	void PopBack();//尾删
	void Insert(size_t pos, const DataType& data);//在pos位置后面插入值为data的元素
	void Erase(size_t pos);//删除pos位置上的元素
	int Find(const DataType& data)const;//寻找值为data的元素返回下标
	void Clear();//清空顺序表
	size_t Size()const;//计算顺序表的大小
	void ReSize(size_t size, const DataType& data);//将_size 到 size之间的元素赋值为data
	size_t Capacity()const;//顺序表容量的大小
	bool Empty()const;//判断顺序表是否为空
	DataType& Front();//返回第一个元素的引用
	const DataType& Front()const;//同上 成对出现
	DataType& Back();//返回最后一个元素的引用
	const DataType& Back()const;//同上
	//赋n个值为data的元素到vector中.这个函数将会清除掉为vector赋值以前的内容.
	void Assign(size_t n, const DataType& data);
	DataType& operator[](size_t index);//下标访问界定符
	const DataType& operator[](size_t index)const;//同上
	DataType& At(size_t index);//
	const DataType& At(size_t index)const;//同上
 
private:
	void _CheckCapacity();
	friend std::ostream& operator<<(std::ostream& _cout, const Vector& v);
private:
	DataType* _pData;//空间首地址
	size_t _capacity;//容量
	size_t _size;//有效元素的个数
};