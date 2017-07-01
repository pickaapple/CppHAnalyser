//
//  String.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "String.hpp"
namespace st{
    template<class T,class P>
    String<T, P>::String(const char* str,unsigned int length){
        List<T,P>::Initialize(str,length);
    }
}
