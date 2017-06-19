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
#include "String.hpp"
#include "Tree.hpp"
namespace st{
    struct XLexical{
        short flag;
        string regulerExp;
    };
    class MLexer
    :public Instance<MLexer>{
    public:
        void lexOneLine(const string& line);
    private:
        void Initialize();
        BTreeOfChar formatTree;
        List<XLexical> _lexicalsBuffer;
    };
}
#endif /* Lexer_hpp */
