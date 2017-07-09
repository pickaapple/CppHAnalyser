//
//  StateChart.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/27.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef StateChart_hpp
#define StateChart_hpp

#include "Macro.h"
#include "Allocation.hpp"
#include "List.hpp"
#include "String.hpp"

#define BASECHART_DEFUALT_ROAD_CAPACITY 4
#define SIMPLECHART_DEFUALT_CHILD_CAPACITY 12

#define ALTERNATIVECHART_DEFUALT_STATE_CAPACITY 12

namespace st{
    ////////////////////////////////////////////////////////////
    //Interface

    class State
    :public Malloced{

    public:
        virtual bool StateEquals(const State &state) const = 0;
        
        DECLARE_SELF_CONTROL_VIRTUAL(State)
        
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

        DECLARE_ATTRI_PTR(BaseChart, NextStop)
        DECLARE_ATTRI(int, Flag)
        DECLARE_ATTRI(Type, Type)
    };

    ////////////////////////////////////////////////////////////

    class AlternativeChart
    :public BaseChart{

    public:

        virtual bool Pass(const state_type &state) const override;
        
        bool AddState(const State* const state);
        
        bool RemoveState(const State* const state);
    public:
        AlternativeChart(Type type);

        explicit AlternativeChart(const State* const states[],const size_t length,const size_t capacity = ALTERNATIVECHART_DEFUALT_STATE_CAPACITY);

        virtual ~AlternativeChart();

    protected:
        List<State*> _states;
    };

    ////////////////////////////////////////////////////////////

    class Utf8State
    :public State
    {

    public:
        virtual bool StateEquals(const State& state) const override;
        
    public:
        Utf8State();
        Utf8State(utf8::uchar chr);
        void test();
    protected:
        DECLARE_ATTRI(utf8::uchar, Char)
        
        DECLARE_SELF_CONTROL_OVERRIDE(Utf8State,State)
    };

    ////////////////////////////////////////////////////////////

    class LetterChart
    :public AlternativeChart{

    public:
        LetterChart();

        virtual ~LetterChart(){};
    protected:
        const static int CHAR_LENGTH;
        static State* CHARS[];
    };

    ////////////////////////////////////////////////////////////

    class DigitChart
    :public AlternativeChart{

    public:
        DigitChart();

        virtual ~DigitChart(){};

    protected:
        const static int CHAR_LENGTH;
        static State* CHARS[];
    };

    ////////////////////////////////////////////////////////////

    class XDigitChart
    :public AlternativeChart{

    public:
        XDigitChart();

        virtual ~XDigitChart(){};

    protected:
        const static int CHAR_LENGTH;
        static State* CHARS[];
    };
}

#endif /* StateChart_hpp */
