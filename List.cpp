//
//  List.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/13.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "List.hpp"

template <class T, class P>
List<T,P>::List(int capacity)
:_capacity(capacity){
    Initialize(capacity);
}

template <class T, class P>
void List<T,P>::Initialize(int capacity){
    _data = capacity > 0 ? NewData(capacity) : nullptr;
}

template <class T, class P>
T& List<T,P>::At(int index) {
    return operator[](index);
}

template <class T, class P>
T& List<T,P>::Add(const T& element) {
    if(_length>=_capacity)
    {
        int newCapacity = 1 + _capacity + (_capacity >> 1);
        T* newData = NewData(newCapacity);
        memcopy(newData,_data,_capacity * sizeof(T));
        DeleteData(_data);
        _data = newData;
        _capacity = newCapacity;
    }
    return _data[_length++] = element;
}

template <class T, class P>
T List<T,P>::Remove(int index) {
    T element = At(index);
    --_length;
    while (index < _length) {
        _data[index] = _data[index+1];
        ++index;
    }
    return element;
}

template <class T, class P>
T* List<T,P>::NewData(int n){
    return static_cast<T*>(P::New(n * sizeof(T)));
}

template <class T, class P>
void List<T,P>::DeleteData(T* data) {
    P::Delete(data);
}
