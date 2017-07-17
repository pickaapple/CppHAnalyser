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
    struct FlagWord{
        char flag;
        string word;
    };
    
    class MLexer
    {
    public:
        void Initialize();
        
        void Input(const string& oneLine);
        
        void Lexer();

        const List<FlagWord> Output() const;
        
        MLexer();
        
        virtual ~MLexer();
    private:
        
        List<FlagWord> wordsStore;
    };
}
#endif /* Lexer_hpp */
