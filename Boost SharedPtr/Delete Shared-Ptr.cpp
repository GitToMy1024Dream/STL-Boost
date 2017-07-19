#include <iostream>
using namespace std;
#pragma warning (disable:4996)
//关闭文件
struct Fclose
{
	void operator()(void* ptr)
	{
		fclose((FILE*)ptr);
		cout << "fclose()" << endl;
	}
};
//释放malloc
struct Free
{
	void operator()(void *ptr)
	{
		free(ptr);
		cout << "free()" << endl;
	}
};
//默认为delete
struct DefaultDelete
{
	void operator()(void *ptr)
	{
		delete ptr;
		cout << "delete()" << endl;
	}
};

template<class T,class Deleter = DefaultDelete>
class SharedPtr
{
public:
	SharedPtr(T* ptr);
	SharedPtr(T* ptr, Deleter del);
	SharedPtr(const SharedPtr<T, Deleter>& ap);
	~SharedPtr();
	SharedPtr<T, Deleter>& operator=(SharedPtr<T, Deleter> ap);
	T& operator*();
	T& operator*()const;
	T* operator->();
	T* operator->()const;
	long GetCount()const;
	T* GetPtr()const;
private:
	T* _ptr;
	long* _count;
	Deleter _del;
};

template<class T,class Deleter = DefaultDelete>
SharedPtr<T, Deleter>::SharedPtr(T* ptr)//构造函数
	:_ptr(ptr)
	,_count(new long(1))
{}
template<class T, class Deleter = DefaultDelete>
SharedPtr<T, Deleter>::SharedPtr(T* ptr,Deleter del)//构造函数
	: _ptr(ptr)
	, _count(new long(1))
	,_del(del)
{}

template<class T,class Deleter = DefaultDelete>
SharedPtr<T, Deleter>::SharedPtr(const SharedPtr<T, Deleter>& sp)//拷贝构造
	:_ptr(sp._ptr)
	,_count(sp._count)
	,_del(sp._del)
{
	++(*_count);
}

template<class T,class Deleter = DefaultDelete>
SharedPtr<T, Deleter>::~SharedPtr()//析构函数
{
	if (--(*_count) == 0)
	{
		_del(_ptr);
		delete _count;
	}
}
template<class T, class Deleter = DefaultDelete>//赋值运算符的重载
SharedPtr<T, Deleter>& SharedPtr<T, Deleter>::operator=(SharedPtr<T, Deleter> sp)
{
	std::swap(_ptr, sp._ptr);
	std::swap(_count, sp._count);
	std::swap(_del, sp._del);
	return *this;
}

template<class T,class Deleter = DefaultDelete>
T& SharedPtr<T, Deleter>::operator*()//重载接引用
{
	return *_ptr;
}

template<class T, class Deleter = DefaultDelete>
T& SharedPtr<T, Deleter>::operator*()const
{
	return *_ptr;
}

template<class T, class Deleter = DefaultDelete>
T* SharedPtr<T, Deleter>::operator->()//重载间接运算符
{
	return _ptr;
}

template<class T, class Deleter = DefaultDelete>
T* SharedPtr<T, Deleter>::operator->()const
{
	return _ptr;
}

template<class T,class Deleter = DefaultDelete>
long SharedPtr<T, Deleter>::GetCount()const//获取引用计数
{
	return *_count;
}

template<class T,class Deleter = DefaultDelete>
T* SharedPtr<T, Deleter>::GetPtr()const//获取对象指针
{
	return _ptr;
}

int main()
{
	SharedPtr<int> sp1(new int(1));//默认为delete
	SharedPtr<FILE, Fclose> sp2(fopen("1.txt", "w+"), Fclose());//文件操作
	SharedPtr<string, Free> sp3((string *)malloc(sizeof(string)), Free());//字符串操作
	system("pause");
	return 0;
}