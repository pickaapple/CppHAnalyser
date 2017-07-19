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
    //fReader.ReadFile("C:\\Users\\Administrator\\Desktop\\hello.txt");
    if(!fReader.ReadFile("/ys/text/hello.txt"))
    {
        std::cout << "read file fail" << std::endl;
        return 0;
    }
	string line;
	while (fReader.ReadLine(line)) {
	}
	std::cout << line.GetElements();
    return 0;
}
