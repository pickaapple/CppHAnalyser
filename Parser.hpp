//
//  Parser.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/7/17.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Parser_hpp
#define Parser_hpp

#include "Instance.hpp"
#include "List.hpp"
#include "Lexer.hpp"

namespace st{
    struct Node{
        
    };
    class MParser
    {
    public:
        void Initialize();
        
        void Input(List<FlagWord> words);
        
        void Parser();
        
        List<Node> Output();
        
        void Show();
        
        MParser();
        
        virtual ~MParser();
    };
}
#endif /* Parser_hpp */
