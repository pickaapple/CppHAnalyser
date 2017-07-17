//
//  Instance.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Instance_hpp
#define Instance_hpp
template<class T>
class Instance {
public:
    T* GetInstance();

};

template<class T>
T* Instance<T>::GetInstance(){
    static T t;
    return *t;
};

#endif /* Instance_hpp */
