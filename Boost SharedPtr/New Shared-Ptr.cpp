template<class T, class Deleter = Del<T>>
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
	long* _pCount;
	Deleter _del;
};
 
template<class T, class Deleter = Del<T>>
SharedPtr<T, Deleter>::SharedPtr(T* ptr)
	:_ptr(ptr)
	, _pCount(new long(1))
{}
 
template<class T, class Deleter = Del<T>>//构造函数
SharedPtr<T, Deleter>::SharedPtr(T* ptr, Deleter del)
	: _ptr(ptr)
	, _del(del)
	, _pCount(new long(1))
{}
 
template<class T, class Deleter = Del<T>>//拷贝构造函数
SharedPtr<T, Deleter>::SharedPtr(const SharedPtr<T, Deleter>& ap)
	:_ptr(ap._ptr)
	, _pCount(ap._pCount)
	, _del(ap._del)
{
	++(*this->_pCount);
}
 
template<class T, class Deleter = Del<T>>
SharedPtr<T, Deleter>::~SharedPtr()//析构函数
{
	if (--(*this->_pCount) == 0)
	{
		_del(_ptr);
		delete this->_pCount;
	}
}
//第一种方法
template<class T,class Deleter=Del<T>>//赋值运算符重载
SharedPtr<T, Deleter>& SharedPtr<T, Deleter>::operator=(SharedPtr<T, Deleter> ap)
{
	if (this != &ap)
	{
		if (--(*this->_pCount) == 0)
		{
			_del(_ptr);
			delete this->_pCount;
		}
		this->_ptr = ap._ptr;
		this->_pCount = ap._pCount;
		++(*this->_pCount);
	}
	return *this;
}
//第二种方法
//template<class T, class Deleter = Del<T>>
//SharedPtr<T, Deleter>& SharedPtr<T, Deleter>::operator=(SharedPtr<T, Deleter> ap)
//{
//	swap(this->_ptr, ap._ptr);
//	swap(this->_pCount, ap._pCount);
//	swap(this->_del, ap._del);
//	return *this;
//}
 
template<class T,class Deleter=Del<T>>//重载*运算符
T& SharedPtr<T, Deleter>::operator*()
{
	return *(this->_ptr);
}
template<class T, class Deleter = Del<T>>
T& SharedPtr<T, Deleter>::operator*()const
{
	return *(this->_ptr);
}
 
template<class T,class Deleter=Del<T>>//重载->运算符
T* SharedPtr<T, Deleter>::operator->()
{
	return this->_ptr;
}
template<class T, class Deleter = Del<T>>
T* SharedPtr<T, Deleter>::operator->()const
{
	return this->_ptr;
}
 
template<class T,class Deleter=Del<T>>//获取引用计数
long SharedPtr<T, Deleter>::GetCount()const
{
	return *(this->_pCount);
}
 
template<class T,class Deleter=Del<T>>//获取对象指针
T* SharedPtr<T, Deleter>::GetPtr()const
{
	return this->_ptr;
}