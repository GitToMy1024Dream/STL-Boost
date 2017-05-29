#include "Vector.h"
void Vector::_CheckCapacity()
{
	if(_size >= _capacity)
	{
		_pData = (DataType*)realloc(_pData,_capacity * sizeof(DataType) * 2);
		assert(_pData);
		_capacity *= 2;
	}
}
void Vector::PushBack(const DataType& data)
{
	_CheckCapacity();
	_pData[_size] = data;
	_size += 1;
}
void Vector::PopBack()
{
	assert(_size > 0);
	--_size;
}
void Vector::Insert(size_t pos,const DataType& data)
{
	_CheckCapacity();
	assert(pos >= 0 && pos <= _size);
	for(size_t idx = _size - 1;idx >= pos;--idx)
	{
		_pData[idx+1] = _pData[idx];
	}
	_pData[pos] = data;
	_size += 1;
}
void Vector::Erase(size_t pos)
{
	assert(pos >= 0 && pos <= _size);
	for(size_t idx = pos;idx < _size;++idx)
	{
		_pData[idx] = _pData[idx+1];
	}
	_size -= 1;
}
int Vector::Find(const DataType& data)const
{
	for(size_t idx = 0;idx < _size;)
	{
		if(_pData[idx] == data)
			return idx;
		++idx;
	}
	return 0;
}
void Vector::Clear()
{
	if(_size == 0)
		return;
	_size = 0;
}
size_t Vector::Size()const
{
	return _size;
}
void Vector::ReSize(size_t size,const DataType& data)
{
	_CheckCapacity();
	if(size < _size)
		_size = size;
	if(size > _size)
	{
		for(size_t idx = _size;idx < size;++idx)
		{
			_pData[idx] = data;
		}
		_size = size;
	}
}
size_t Vector::Capacity()const
{
	return _capacity;
}
bool Vector::Empty()const
{
	if(_size == 0)
		return true;
	if(_size > 0)
		return false;
}
DataType& Vector::Front()
{
	return (*this)._pData[0];
}
const DataType& Vector::Front()const
{
	return (*this)._pData[0];
}
DataType& Vector::Back()
{
	return (*this)._pData[_size - 1];
}
const DataType& Vector::Back()const
{
	return (*this)._pData[_size];
}
void Vector::Assign(size_t n,const DataType& data)
{
	free(_pData);
	_pData = NULL;
	_pData = (DataType*)malloc(_capacity * sizeof(DataType));
	for(size_t idx = 0;idx < n;++idx)
	{
		_pData[idx] = data;
	}
	_size = n;
	_capacity = n;
}
DataType& Vector::operator[](size_t index)
{
	return _pData[index];
}
const DataType& Vector::operator[](size_t index)const
{
	return _pData[index];
}
DataType& Vector::At(size_t index)
{
	assert(index <= _size);
	return _pData[index];
}
const DataType& Vector::At(size_t index)const
{
	assert(index <= _size);
	return _pData[index];
}
ostream& operator<<(ostream& _cout,const Vector& c)
{
	for(size_t idx = 0;idx < c._size;++idx)
	{
		_cout<<c._pData[idx]<<"  ";
	}
	return _cout;
}