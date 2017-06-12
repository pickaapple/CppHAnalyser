//
//  MFileReader.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef MFileReader_hpp
#define MFileReader_hpp
#include "Instance.hpp"

class MFileReader:
public Instance<MFileReader>{
    char* _szText;
    
public:
    void ReadFile(const char* szFile);
};

#endif /* MFileReader_hpp */
