//
//  StateChart.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/27.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "StateChart.hpp"

namespace st{
#define BASECHART_DEFUALT_CAPACITY 12
    
    ////////////////////////////////////////////////////////////
    
    template <class S>
    BaseChart<S>::BaseChart()
    :_states(BASECHART_DEFUALT_CAPACITY)
    {
    }
    
    template <class S>
    BaseChart<S>::BaseChart(const state_type states[],const unsigned int size)
    :_states(states,size)
    {
    };
    
    ////////////////////////////////////////////////////////////
    
    utf8::uchar CharacterChart::CHARS[] =
    {
        'a','b','c','d','e',
        'f','g','h','i','j',
        'k','l','m','n','o',
        'p','q','r','s','t',
        'u','v','w','x','y',
        'z',
        'A','B','C','D','E',
        'F','G','H','I','J',
        'K','L','M','N','O',
        'P','Q','R','S','T',
        'U','V','W','X','Y',
        'Z',
    };
    
    CharacterChart::CharacterChart()
    :BaseChart<utf8::uchar>(CHARS,CHAR_LENTH){
    };
    
    ////////////////////////////////////////////////////////////
    
    utf8::uchar DigitChart::CHARS[] =
    {
        '0','1','2','3','4',
        '5','6','7','8','9'
    };
    
    DigitChart::DigitChart()
    :BaseChart<utf8::uchar>(CHARS,DIGIT_LENTH){
    };
    
    ////////////////////////////////////////////////////////////
    
    utf8::uchar XDigitChart::CHARS[]  =
    {
        '0','1','2','3','4',
        '5','6','7','8','9',
        'A','B','C','D','E',
        'F','a','b','c','d',
        'e','f'
    };
    
    XDigitChart::XDigitChart()
    :BaseChart<utf8::uchar>(CHARS,XDIGIT_LENTH){
    };
    
    ////////////////////////////////////////////////////////////
    
}
