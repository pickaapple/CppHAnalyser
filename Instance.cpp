//
//  Instance.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Instance.hpp"

template<class T>
T* Instance<T>::GetInstance(){
    static T t;
    return *t;
};
