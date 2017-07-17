//
//  Scaner.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef MScaner_hpp
#define MScaner_hpp

#include "Instance.hpp"
#include "String.hpp"
namespace st{
    class MScaner
    {
    public:
        void NextLine();
        const string& getCurrentLine();
        const int getLineNumber();
    private:
        char* flag;
        int _lineNumber;
        string _currentLine;
    };
}
#endif /* Scaner_hpp */
