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
namespace st{
    class Mallocation{
    public:
        static void* New(size_t size);
        static void Delete(void* p);
        static void FatalProcessOutOfMemory();
    };
    class Malloced
    {
    public:
        void* operator new(size_t size);
        void operator delete(void* p);
    };
}
#endif /* Allocation_hpp */
