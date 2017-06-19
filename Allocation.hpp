//
//  Allocation.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/18.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Allocation_hpp
#define Allocation_hpp

#include <stdlib.h>

class Mallocation{
public:
    static void* New(size_t size);
    static void Delete(void* p);
};

#endif /* Allocation_hpp */
