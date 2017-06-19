//
//  Lexer.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include "Instance.hpp"
#include "List.hpp"

struct XLexical{
    short flag;
    char regularExp[];
};

class MLexer
:public Instance<MLexer>{
    List<XLexical> lexicals;
};

#endif /* Lexer_hpp */
