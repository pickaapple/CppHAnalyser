//
//  StateChart.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/27.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef StateChart_hpp
#define StateChart_hpp

#include "String.hpp"
#include "List.hpp"

namespace st{
    
    ////////////////////////////////////////////////////////////
    
    template<class S>
    class BaseChart{
        typedef S state_type;
    public:
        void AddState(const state_type& state){
            _states.Add(state);
        };
        bool Pass(const state_type state){
            for (int i = _states.length() - 1 ; i >= 0 ; --i) {
                if(state == _states[i])
                    return true;
            }
            return false;
        };
    public:
        BaseChart();
        explicit BaseChart(const state_type states[],const unsigned int size);
        virtual ~BaseChart(){};
    protected:
        int _size;
        List<state_type> _states;
    };
    
    ////////////////////////////////////////////////////////////
    
    class CharacterChart
    :public BaseChart<utf8::uchar>{
    public:
        CharacterChart();
        virtual ~CharacterChart(){};
    protected:
        const static int CHAR_LENTH = 52;
        static utf8::uchar CHARS[];
    };
    
    ////////////////////////////////////////////////////////////
    
    class DigitChart
    :public BaseChart<utf8::uchar>{
    public:
        DigitChart();
        virtual ~DigitChart(){};
    protected:
        const static int DIGIT_LENTH = 10;
        static utf8::uchar CHARS[];
    };
    
    ////////////////////////////////////////////////////////////
    
    class XDigitChart
    :public BaseChart<utf8::uchar>{
    public:
        XDigitChart();
        virtual ~XDigitChart(){};
    protected:
        const static int XDIGIT_LENTH = 22;
        static utf8::uchar CHARS[];
    };
}

#endif /* StateChart_hpp */
