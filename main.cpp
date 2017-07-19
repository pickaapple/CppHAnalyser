//
//  main.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include <stdio.h>

#include "FileReader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace st;

// int main(int argc, const char * argv[]) {
//     
//     if(argc < 1)
//         return 0;
//     
//     MFileReader fReader;
//     fReader.ReadFile(argv[0]);
// 
//     MLexer lexer;
//     lexer.Initialize();
// 
//     MParser parser;
//     parser.Initialize();
//     
//     while(fReader.MoveNext())
//     {
//         lexer.Input(fReader.ReadCurrentLine());
//     }
//     lexer.Lexer();
//     
//     parser.Input(lexer.Output());
//     
//     parser.Show();
//     
//     return 0;
// }
