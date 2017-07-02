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
#include "Macro.h"

#define BASECHART_DEFUALT_ROAD_CAPACITY 4
#define SIMPLECHART_DEFUALT_CHILD_CAPACITY 12

#define ALTERNATIVECHART_DEFUALT_STATE_CAPACITY 12

namespace st{
    ////////////////////////////////////////////////////////////
    //Interface
    
    class State{
        
    public:
        virtual bool StateEquals(const State &state) const = 0;
    };
    
    ////////////////////////////////////////////////////////////
    
    class BaseChart{
        
    public:
        enum Type{
            NONE,
            INITIAL,
            SIMPLE,
            OVER,
            CIRCLE,
            OVER_CIRCLE,
            FINAL
        };
        
    protected:
        typedef State state_type;
        
    public:
        virtual bool Pass(const state_type &state) const;
        
        bool operator == (const BaseChart& chart);
        
    protected:
        BaseChart();
        BaseChart(Type type);
        
        virtual ~BaseChart(){}
        
    protected:
        
        DECLARE_ATTRI(BaseChart*, NextStop)
        DECLARE_ATTRI(int, Flag)
        DECLARE_ATTRI(Type, Type)
    };
  
    ////////////////////////////////////////////////////////////
    
    class AlternativeChart
    :public BaseChart{
        
    public:
        
        virtual bool Pass(const state_type &state) const override;
        
    public:
        AlternativeChart(Type type);
        
        explicit AlternativeChart(State* const states[], size_t length, size_t capacity = ALTERNATIVECHART_DEFUALT_STATE_CAPACITY);
        
        virtual ~AlternativeChart(){};
        
    protected:
        List<State*> _states;
    };
    
    ////////////////////////////////////////////////////////////
    
    class Utf8State
    :public State{
        
    public:
        virtual bool StateEquals(const State& state) const override;

    public:
        Utf8State(utf8::uchar chr);
    protected:
        DECLARE_ATTRI(utf8::uchar, Char)
    };
    
    ////////////////////////////////////////////////////////////
    
    class LetterChart
    :public AlternativeChart{
        
    public:
        LetterChart();
        
        virtual ~LetterChart(){};
    protected:
        const static int CHAR_LENTH = 52;
        static State* CHARS[];
    };
    
    ////////////////////////////////////////////////////////////
    
    class DigitChart
    :public AlternativeChart{
        
    public:
        DigitChart();
        
        virtual ~DigitChart(){};
        
    protected:
        const static int DIGIT_LENTH = 10;
        static State* CHARS[];
    };
    
    ////////////////////////////////////////////////////////////
    
    class XDigitChart
    :public AlternativeChart{
        
    public:
        XDigitChart();
        
        virtual ~XDigitChart(){};
        
    protected:
        const static int XDIGIT_LENTH = 22;
        static State* CHARS[];
    };
}

#endif /* StateChart_hpp */
