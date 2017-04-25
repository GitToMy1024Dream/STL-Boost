template<class T>
class AutoPtr
{
public:
	AutoPtr();
	AutoPtr(T* ptr);
	AutoPtr(AutoPtr<T>& ap);
	AutoPtr<T>& operator=(AutoPtr<T>& ap);
	~AutoPtr();
	T& operator*();
	T& operator*()const;
	T* operator->();
	T* operator->()const;
protected:
	T* _ptr;
};

template<class T>//构造函数
AutoPtr<T>::AutoPtr()
	:_ptr(NULL)
{}
template<class T>
AutoPtr<T>::AutoPtr(T* ptr) // 不能写成const T* ptr，const类型的赋值不能给非const类型
	:_ptr(ptr)
{}
template<class T>//拷贝构造
AutoPtr<T>::AutoPtr(AutoPtr<T>& ap)
	:_ptr(ap._ptr)
{
	ap._ptr = NULL;
}

template<class T>//赋值运算符的重载
AutoPtr<T>& AutoPtr<T>::operator=(AutoPtr<T>& ap)
{
	if (this != &ap)
	{
		delete this->_ptr;
		this->_ptr = ap._ptr;
		ap._ptr = NULL;
	}
	return *this;
}
template<class T>//析构函数
AutoPtr<T>::~AutoPtr()
{
	if (this->_ptr)
	{
		delete this->_ptr;
		this->_ptr = NULL;
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
template<class T>
T* AutoPtr<T>::operator->()const
{
	return this->_ptr;
}
