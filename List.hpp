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

template <class T,class P = Mallocation>
class List{
public:
    explicit List(int capacity);
    
    inline void Initialize(int capacity);
    
    inline T& At(int index);
    
    T&  Add(const T& element);
    
    T   Remove(int index);
    
    inline T* NewData(int n);
    
    inline void DeleteData(T* data);
    
    inline T& operator [](int index){
        return _data[index];
    };
private:
    T* _data;
    int _length;
    int _capacity;
};

#endif /* List_hpp */
