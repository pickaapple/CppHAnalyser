//
//  List.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/13.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef List_hpp
#define List_hpp

#include "Allocation.hpp"
#include <string.h>
namespace st{
    template <class T,class P = Mallocation>
    class List{
    public:
        inline T& At(unsigned int index){
            return operator[](index);
        };
        
        T&  Add(const T& element){
            if(_length >= _capacity)
            {
                unsigned int newCapacity = 1 + _capacity + (_capacity >> 1);
                T* newData = NewData(newCapacity);
                memcpy(newData,_data,_capacity * sizeof(T));
                DeleteData(_data);
                _data = newData;
                _capacity = newCapacity;
            }
            return _data[_length++] = element;
        };
        
        bool Move(const T elements[], size_t size){
            if(_capacity < size){
                size_t newCapacity =size + (_capacity >> 1);
                T* newData = NewData(newCapacity);
                DeleteData(_data);
                _data = newData;
                _capacity = newCapacity;
            }
            _length = size;
            memcpy(_data, elements, sizeof(T) * size);
            return true;
        };
        
        T   Remove(unsigned int index){
            T element = At(index);
            --_length;
            while (index < _length) {
                _data[index] = _data[index+1];
                ++index;
            }
            return element;
        };
        
        inline T* NewData(size_t n){
            return static_cast<T*>(P::New(n * sizeof(T)));
        };
        
        inline void DeleteData(T* data){
            P::Delete(data);
        };
        
        inline T& operator [](unsigned int index){
            return _data[index];
        };
        
    private:
        inline void Initialize(size_t capacity){
            _data = capacity > 0 ? NewData(capacity) : nullptr;
        };
        
        inline void Initialize(const T elements[],size_t length){
            Initialize(length);
            Move(elements, length);
        };
        
    public:
        inline explicit List(const T elements[],size_t length)
        :_capacity(length)
        ,_length(length)
        {
            Initialize(elements, length);
        };
        
        inline explicit List(size_t capacity)
        :_capacity(capacity){
            Initialize(capacity);
        };
        
        inline int length(){
            return _length;
        }
        
    private:
        T* _data;
        size_t _length;
        size_t _capacity;
    };
}
#endif /* List_hpp */
