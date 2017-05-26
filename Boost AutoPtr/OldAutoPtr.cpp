template<class T>
class AutoPtr
{
public:
	AutoPtr(T* ptr = NULL);
	AutoPtr(AutoPtr<T>& ap);
	AutoPtr<T>& operator=(AutoPtr<T>& ap);
	~AutoPtr();
	T& operator*();
	T& operator*()const;
	T* operator->();
	T* operator->()const;
protected:
	T* _ptr;
	mutable bool _owner;
};
 
template<class T>//构造函数
AutoPtr<T>::AutoPtr(T* ptr)
	:_ptr(ptr)
	,_owner(true)
{}
 
template<class T>//拷贝构造
AutoPtr<T>::AutoPtr(AutoPtr<T>& ap)
	:_ptr(ap._ptr)
	,_owner(true)
{
	ap._owner = false;
}
 
template<class T>//赋值运算符的重载
AutoPtr<T>& AutoPtr<T>::operator=(AutoPtr<T>& ap)
{
	if (this != &ap)
	{
		delete this->_ptr;
		this->_ptr = ap._ptr;
		this->_owner = true;
		ap._owner = false;
	}
	return *this;
}
 
template<class T>//析构函数
AutoPtr<T>::~AutoPtr()
{
	if (this->_ptr)
	{
		this->_owner = false;
		delete this->_ptr;
	}
}
 
template<class T>//重载*
T& AutoPtr<T>::operator*()
{
	return *(this->_ptr);
}
template<class T>
T& AutoPtr<T>::operator*()const
{
	return *(this->_ptr);
}
 
template<class T>//重载->
T* AutoPtr<T>::operator->()
{
	return this->_ptr;
}
template<class T>//重载->const
T* AutoPtr<T>::operator->()const
{
	return this->_ptr;
}