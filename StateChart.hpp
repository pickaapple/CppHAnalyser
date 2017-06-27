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
    struct State{
        char flag;
    };
    class BaseChart{
        enum EStateStep{
            STATE_STEP_START,
            STATE_STEP_IN,
            STATE_STEP_END
        };
    public:
        void Initialize(const State states[],const int size);
        bool Pass(const string& str);
    public:
        BaseChart();
        virtual ~BaseChart();
    protected:
        EStateStep _step;
        int _size;
        List<State> _states;
    };
    class LetterChart
    :public BaseChart{
    public:
        LetterChart();
        virtual ~LetterChart();
    };
}

#endif /* StateChart_hpp */
