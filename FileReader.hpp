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

public Instance<MFileReader>{
#include "String.hpp"
namespace st{
    class MFileReader:
    public Instance<MFileReader>{
    public:
        void ReadFile(const char* szFile);
    public:
        string _text;
    };
}
#endif /* FileReader_hpp */
