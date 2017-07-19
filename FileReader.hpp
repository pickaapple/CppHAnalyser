//
//  FileReader.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef FileReader_hpp
#define FileReader_hpp

#include <fstream>
#include "String.hpp"
namespace st{
    class MFileReader
    {
    public:
        bool ReadLine(string& line);
        
        void ReadFile(const char* szFile);
    
        MFileReader();
        
        virtual ~MFileReader();
    public:
        string _text;
		std::ifstream _ifs;
    };
}
#endif /* FileReader_hpp */
