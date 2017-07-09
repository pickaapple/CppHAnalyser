//
//  Allocation.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/18.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//
#include <stdio.h>

#include "Allocation.hpp"
#include "platform.hpp"

namespace st
{
    ////////////////////////////////////////////////////////////
    
    void* Mallocation::New(size_t size)
    {
        return malloc(size);
    }
    
    void Mallocation::Delete(void* p)
    {
        free(p);
    }
    
    void Mallocation::FatalProcessOutOfMemory()
    {
        printf("Fatal Process Out Of Memory");
        OS::Abort();
    }
    
    ////////////////////////////////////////////////////////////
    
    void* Malloced::operator new(size_t size)
    {
        void* p = Mallocation::New(size);
        if(p == NULL) Mallocation::FatalProcessOutOfMemory();
        return p;
    }
    
    void Malloced::operator delete(void *p)
    {
        Mallocation::Delete(p);
    }
}
