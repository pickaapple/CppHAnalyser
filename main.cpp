//
//  main.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//
//#include "List.hpp"
#include "StateChart.hpp"

#include <stdio.h>

using namespace st;
class TEST
{
public:
    TEST(){printf("TEST()");};
    ~TEST(){printf("~TEST()");};
    void* operator new(size_t size){ printf("new");return malloc(size);}
    void  operator delete(void* p) { printf("delete"); free(p); }
};
int main(int argc, const char * argv[]) {
    TEST* t = new TEST();
    delete t;
    return 0;
}
