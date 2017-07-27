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
	string path = "C:\\Users\\Administrator\\Desktop\\hello.txt";
	//string path = "/ys/text/hello.txt";
	if (!fReader.ReadFile(path.GetElements()))
	{
		std::cout << "read file fail" << std::endl;
		return 0;
	}
	string line;
	while (fReader.ReadLine(line)) {
	}
	MLexer lexer;
	lexer.Input(line);
	lexer.Lexer();
	const List<FlagWord>& flagWords = lexer.Output();
	int i, j;
	foreachList(i, flagWords)
	{
		foreachList(j, flagWords[i].GetFlags())
		{
			std::cout << "flag" << j << ":" << (int)flagWords[i].GetFlags()[j]._Flag << " ";
			std::cout << "type" << j << ":" << (int)flagWords[i].GetFlags()[j]._Type << " ";
		}
		if(0 == j)
			std::cout << "flag:do not know";
		std::cout << " word:" << flagWords[i].GetWord().GetElements() << std::endl;
	}
	return 0;
}
