#pragma once
template<class T>
class Vector
{
public:
	typedef T ValueType;//对象类型T，存储在vector中
	typedef ValueType* Pointer;//指向T的指针
	typedef const ValueType* ConstPointer;
	typedef ValueType* Iterator;//访问vector的迭代器
	typedef const ValueType* ConstIterator;//访问vector的常量迭代器
	typedef ValueType& Reference;//T的一个引用
	typedef const ValueType& ConstReference;//T的常量引用
	typedef size_t SizeType;//正整数类型
 
 
public:
	Vector()//构造函数
		: _start(0)
		, _end(0)
		, _endOfStorage(0)
	{}
 
	Vector(SizeType n, const T& value)//创建一个vector，数量为n，大小为value
	{
		FillAndInit(n, value);
	}
 
	Vector(SizeType n)//创建一个vector，元素数量为n
	{
		FillAndInit(n, T());
	}
 
	Vector(const Vector<T>& v)//拷贝构造函数
	{
		CheckCapacity();
		_start = new T[v.Capacity()];
		_end = _start + v.Size();
		_endOfStorage = _start + v.Capacity();
 
		for (size_t idx = 0; idx < v.Size(); ++idx)
			_start[idx] = v[idx];
	}
 
	Vector<T>& operator=(const Vector<T>& v)//赋值运算符的重载
	{
		if (this != &v)
		{
			_start = v._start;
			_end = v._end;
			_endOfStorage = v._endOfStorage;
		}
		return *this;
	}
	~Vector()//析构函数
	{
		delete[] _start;
		_start = _end = 0;
	}
 
 
	/////////////////////Capacity//////////////////////
	SizeType Capacity()const//返回当前所能容纳的最多元素的个数
	{
		return SizeType(_endOfStorage - Begin());
	}
	SizeType Size()const//返回vector的元素数量
	{
		return SizeType(End() - Begin());
	}
	SizeType MaxSize()const//返回最大可允许的vector元素数量值
	{
		return (SizeType(-1) / sizeof(T));
	}
	bool Empty()const//判断vector是否为空
	{
		if (Size() == 0)
			return true;
		return false;
	}
 
	//////////////Acess/////////////////////
	Reference operator[](size_t index)//返回第n个元素
	{
		return *(Begin() + index);
	}
	ConstReference operator[](size_t index)const
	{
		return *(Begin() + index);
	}
	Reference Front()//返回第一个元素
	{
		return *Begin();
	}
	ConstReference Front()const
	{
		return *Begin();
	}
	Reference Back()//返回最后一个元素
	{
		return *(End() - 1);
	}
	ConstReference Front()const
	{
		return *(End() - 1);
	}
 
 
	/////////////Iterator//////////////////
	Iterator Begin()//返回vector的头指针
	{
		return _start;
	}
	ConstIterator Begin()const
	{
		return _start;
	}
	Iterator End()//返回vector的尾指针
	{
		return _end;
	}
	ConstIterator End()const
	{
		return _end;
	}
 
	//////////////Modify///////////////////
	void PushBack(const T& value)//尾插
	{
		CheckCapacity();
		Insert(End(), value);
	}
	void PopBack()
	{
		Iterator pos = End();
		Erase(--pos);
	}
 
	// 在position位置插入元素data
	Iterator Insert(Iterator position, const T& data)
	{
		CheckCapacity();
		for (Iterator index = End(); index != position; index--)
		{
			*index = *(index - 1);
		}
		*position = data;
		_end++;
	}
 
	// 删除position位置的元素
	Iterator Erase(Iterator position)
	{
		Iterator end = End();
		for (Iterator index = position; index != End(); ++index)
		{
			*index = *(index + 1);
		}
		_end--;
	}
	//清空
	void clear()
	{
		Erase(Begin(), End());
	}
	
protected:
	void FillAndInit(SizeType n, const T& value)
	{
		_start = new T[n];
		for (size_t index = 0; index < _end; ++index)
		{
			_start[index] = value;
		}
	}
	void CheckCapacity()
	{
		if (_end == _endOfStorage)
		{
			Iterator NewStart = new T[2 * Size()];
			Iterator NewEnd = NewStart;
			for (Iterator i = Begin(); i != End(); i++, NewEnd++)
			{
				*NewEnd = *i;
			}
			delete[] _start;
			_start = NewStart;
			_end = NewEnd;
			_endOfStorage = _start + 2 * Size();
		}
	}
protected:
	Iterator _start;
	Iterator _end;
	Iterator _endOfStorage;
 
};