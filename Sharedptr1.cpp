#include <iostream>
using namespace std;

template<class T>
class SharedPtr
{
public:
	SharedPtr();
	SharedPtr(T* ptr);
	SharedPtr(const SharedPtr<T>& ap);
	~SharedPtr();
	SharedPtr<T>& operator=(SharedPtr<T> ap);
	T& operator*();
	T& operator*()const;
	T* operator->();
	T* operator->()const;
	long GetCount()const;
	T* GetPtr()const;
private:
	T* _ptr;
	long* _pCount;
};

template<class T>//构造函数
SharedPtr<T>::SharedPtr()
	:_ptr(NULL)
	,_pCount(new long(1))
{}

template<class T>//构造函数(带参数)
SharedPtr<T>::SharedPtr(T* ptr)
	:_ptr(ptr)
	,_pCount(new long(1))
{}

template<class T>//拷贝构造函数
SharedPtr<T>::SharedPtr(const SharedPtr<T>& ap)
	:_ptr(ap._ptr)
	,_pCount(ap._pCount)
{
	++(*this->_pCount);
}

template<class T>//析构函数
SharedPtr<T>::~SharedPtr()
{
	if (--(*this->_pCount) == 0)
	{
		delete this->_ptr;
		delete this->_pCount;
	}
}
//方法一
template<class T>//赋值运算符的重载
SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> ap)
{
	if (this != &ap)
	{
		if (--(*this->_pCount) == 0)
		{
			delete this->_ptr;
			delete this->_pCount;
		}
		this->_ptr = ap._ptr;
		this->_pCount = ap._pCount;
		++(*this->_pCount);
	}
	return *this;
}

//方法二
//template<class T>
//SharedPtr<T>& SharedPtr<T>::operator=(SharedPtr<T> ap)
//{
//	swap(this->_ptr, ap->_ptr);
//	swap(this->_pCount, ap->_pCount);
//	return *this;
//}

template<class T>//重载*运算符
T& SharedPtr<T>::operator*()
{
	return *(this->_ptr);
}
template<class T>//重载*运算符const
T& SharedPtr<T>::operator*()const
{
	return *(this->_ptr);
}

template<class T>//重载->运算符
T* SharedPtr<T>::operator->()
{
	return this->_ptr;
}
template<class T>//重载->运算符const
T* SharedPtr<T>::operator->()const
{
	return this->_ptr;
}

template<class T>//获取当前引用计数的个数
long SharedPtr<T>::GetCount()const
{
	return *(this->_pCount);
}

template<class T>
T* SharedPtr<T>::GetPtr()const//当前的对象指针
{
	return this->_ptr;
}

int main()
{
	SharedPtr<int> ap1(new int(2));
	SharedPtr<int> ap2(ap1);
	SharedPtr<int> ap3 = ap2;
	system("pause");
	return 0;
}
