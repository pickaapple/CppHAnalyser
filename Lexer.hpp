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
        char flag;
        string regulerExp;
    };
    class MLexer
    :public Instance<MLexer>{
    public:
        void Initialize();
        void LexOneLine(const string& line);
    private:
        BTreeOfChar _formatTree;
        List<XLexical> _lexicalsBuffer;
    };
}
#endif /* Lexer_hpp */
