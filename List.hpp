//
//  List.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/13.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include <string.h>

#include "Allocation.hpp"
#include "Checks.hpp"

#define foreachList(i,list) for(i = 0 ; i < list.length() ; ++i)
#define foreachArray(i,l) for(i = 0 ; i < l ; ++i)

namespace st{
    template <class E /*Element*/,class MA /*Memry Allocation*/ = Mallocation>
    class List
	{
        
    public:
		typedef E	element_type;
		typedef MA	memry_allocation;
		const E* GetElements() const
		{
			return _data;
		};
        inline size_t length() const
		{
            return _length;
        }
        
        inline bool IsEmpty() const
		{
            return 0 == _length;
        }
        
        inline element_type& At(size_t index) const
		{
            return operator[](index);
        };
		// add one element at first
		inline element_type& AddAtFirst(const element_type &element)
		{
			if (_length >= _capacity)
			{
				size_t newCapacity = 1 + _capacity + (_capacity >> 1);
				element_type* newData = NewData(newCapacity);
				memcpy(newData + 1, _data, sizeof(element_type) * _capacity);
				DeleteData(_data);
				_data = newData;
				_capacity = newCapacity;
			}
			return _data[0] = element;
		};

		// add one element at last
        inline element_type& AddAtLast(const element_type &element)
		{
            if(_length >= _capacity)
            {
                size_t newCapacity = 1 + _capacity + (_capacity >> 1);
                element_type* newData = NewData(newCapacity);
                memcpy(newData,_data,_capacity * sizeof(element_type));
                DeleteData(_data);
                _data = newData;
                _capacity = newCapacity;
            }
            return _data[_length++] = element;
        };

		inline bool Injure(const element_type elements[], size_t size) 
		{
			if (_capacity < size + _length) 
			{
				size_t newCapacity = size + _length + (_capacity >> 1);
				element_type* newData = NewData(newCapacity);
				memcpy(newData, _data, sizeof(element_type) * _length);
				DeleteData(_data);
				_data = newData;
				_capacity = newCapacity;
			}
			memcpy(_data + _length, elements, sizeof(element_type) * size);
			_length += size;
			return true;
		}

		// replace all data
		inline bool ReplaceByIndex(const element_type& elements, size_t index)
		{
			if (index >= _length) 
			{
				return false;
			}
			_data[index] = elements;
			return true;
		};

        // replace all data
        inline bool ReplaceAll(const element_type elements[], size_t size)
		{
            if(_capacity < size){
                size_t newCapacity =size + (_capacity >> 1);
                element_type* newData = NewData(newCapacity);
                DeleteData(_data);
                _data = newData;
                _capacity = newCapacity;
            }
            _length = size;
            memcpy(_data, elements, sizeof(element_type) * size);
            return true;
        };

        inline element_type Remove(size_t index)
		{
            element_type element = At(index);
            --_length;
            while (index < _length) {
                _data[index] = _data[index+1];
                ++index;
            }
            return element;
        };
		inline element_type RemoveLast()
		{
			return _data[--_length];
		};

        inline element_type* NewData(size_t n)
		{
            return static_cast<element_type*>(memry_allocation::New(n * sizeof(element_type)));
        };
        
        inline void DeleteData(element_type* data)
		{
			memry_allocation::Delete(data);
        };
        
        inline element_type& operator [] (size_t index) const
        {
            ASSERT(index < _length);
            return _data[index];
        };
        
        inline bool operator == (const List& list) const
        {
            size_t i;
            foreachArray(i,_length)
            {
                if(At(i) != list.At(i))
                    return false;
            }
            return true;
        }
        
    private:
        inline void Initialize(size_t capacity){
            _data = NewData(capacity);
        };
        
        inline void Initialize(const element_type elements[],size_t length, size_t capacity){
			ASSERT(elements);
			ASSERT(length <= capacity);
            Initialize(capacity);
            ReplaceAll(elements, length);
        };
        
    public:
        inline explicit List(const element_type elements[], size_t length, size_t capacity)
        :_capacity(capacity)
        ,_length(length)
        ,_data(nullptr)
        {
            Initialize(elements, length, capacity);
        };
        
        inline explicit List(size_t capacity)
        :_capacity(capacity)
        ,_data(nullptr){
            Initialize(capacity);
        };

		inline explicit List()
			:_capacity(10)
			, _data(nullptr) {
			Initialize(_capacity);
		};
    protected:
        element_type* _data;
        size_t _length;
        size_t _capacity;
    };
}
#endif /* List_hpp */
