//
//  FileReader.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp
#include "Instance.hpp"

class MFileReader:
public Instance<MFileReader>{
public:
    void ReadFile(const char* szFile);
public:
    char* _szText;
};

#endif /* FileReader_hpp */
