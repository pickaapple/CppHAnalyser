//
//  Allocation.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/18.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Allocation.hpp"

void* Mallocation::New(size_t size){
    return malloc(size);
}

void Mallocation::Delete(void* p){
    free(p);
}
