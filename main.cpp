//
//  main.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//
#include "List.hpp"
#include "StateChart.hpp"

#include <stdio.h>

using namespace st;
int main(int argc, const char * argv[]) {
    DigitChart chart1;
    utf8::uchar testChar1 = '0';
    utf8::uchar testChar2 = 'x';
    printf("%s pass 0\n",chart1.Pass(testChar1)?"":"dont");
    printf("%s pass x\n",chart1.Pass(testChar2)?"":"dont");
    return 0;
}
