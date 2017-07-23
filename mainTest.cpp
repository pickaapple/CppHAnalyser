//
//  main.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include <iostream>

#include "FileReader.hpp"
#include "Lexer.hpp"
#include "Parser.hpp"

using namespace st;

int main(int argc, const char * argv[]) {
    
    MFileReader fReader;
	//string path = "C:\\Users\\Administrator\\Desktop\\hello.txt";
	string path = "/ys/text/hello.txt";
    if(!fReader.ReadFile(path.GetElements()))
    {
        std::cout << "read file fail" << std::endl;
        return 0;
    }
	string line;
	while (fReader.ReadLine(line)) {
	}
	MLexer lexer;
	lexer.Initialize();
	lexer.Input(line);
	lexer.Lexer();
	const List<FlagWord>& flagWords = lexer.Output();
	int i;
	foreachList(i, flagWords)
	{
		std::cout <<"flag:"<< (unsigned int)flagWords[i].flag <<" word:"<< flagWords[i].word.GetElements() << std::endl;
	}
	return 0;
}
