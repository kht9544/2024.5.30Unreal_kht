#pragma once

template<typename T>
class Vector
{  
public:    

	class Iterator
	{
	public:
		Iterator() : ptr(nullptr) {}
		Iterator(T* otherPtr) : ptr(otherPtr) {}

		Iterator(const Iterator& other) { ptr = other.ptr; }

		Iterator& operator=(const Iterator& other) { ptr = other.ptr; return *this; }

		bool operator != (const Iterator & other) { return ptr != other.ptr; }
		bool operator == (const Iterator & other) { return ptr == other.ptr; }

		Iterator& operator++()
		{
			++ptr;

			return *this;
		}

		Iterator operator++(int)
		{
			Iterator result = *this;
			++(this->ptr);

			return result;
		}
		T& operator*()
		{
			return (*ptr);
		}
	private:
		T* ptr;
	};



	Vector()
	:_size(0), _capacity(0), _data(nullptr) 
	{         

	}     
	~Vector()     
	{         
		delete[] _data; 
	}      
	void Reserve(int capacity)
	{    
		if (capacity <= _capacity) 
		{
			return;					
		}

		T* pData = new T[capacity];
		for (int i = 0; i < _size; i++)
		{
			pData[i] = _data[i];
		}

		delete[] _data;
		_data = pData;
		_capacity = capacity;
		     
	}      
	void PushBack(const T& value)
	{
		if (_size == _capacity) 
		{
			if (_capacity == 0)
			{
				Reserve(1);
			}		
			else
			{
				Reserve(_capacity * 2);
			}

		}
		_data[_size] = value;  
							
		_size++;			
	}      
	void PopBack()
	{
		if (_size == 0)
		{
			return;
		}
		_size--;
	}
	void Clear()
	{
		_size = 0;
	}


	const int& Size() { return _size; }     
	const int& Capacity() { return _capacity; }      
	
	T& operator[](int index)     
	{         
		if (index < 0 || index >= _size)
		{
			return _data[0];
		}
		return _data[index];     
	}

	Vector<T>::Iterator begin() { return Vector<T>::Iterator(_data); }
	Vector<T>::Iterator end() { return Vector<T>::Iterator(_data + _size); }

private:     
	unsigned int _size = 0;
	unsigned int _capacity = 0;

	T* _data = nullptr;

};
