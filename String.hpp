//
//  String.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef String_hpp
#define String_hpp

#include "List.hpp"
#include "Allocation.hpp"

namespace st {
    namespace utf8{
        typedef unsigned int uchar;
        typedef unsigned char byte;        
    }
    template <class T,class P>
    class String:
    public List<T,P>{
    public:
        String(const char* str, unsigned int length);
        virtual ~String(){};
    };
    
    typedef String<char,Mallocation> string;
}

#endif /* String_hpp */
