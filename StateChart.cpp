//
//  StateChart.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/27.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "StateChart.hpp"

namespace st{
    
    ////////////////////////////////////////////////////////////
    
    BaseChart::BaseChart()
    :_Type(NONE)
    ,_NextStop(nullptr)
    {
    }
    
    BaseChart::BaseChart(Type type)
    :_Type(type)
    ,_NextStop(nullptr)
    {
    }
  
    bool BaseChart::Pass(const st::State &state) const
    {
        return true;
    }
    
    ////////////////////////////////////////////////////////////
    
    AlternativeChart::AlternativeChart(Type type)
    :_states(ALTERNATIVECHART_DEFUALT_STATE_CAPACITY)
    ,BaseChart(type)
    {
    }
    
    
    AlternativeChart::AlternativeChart(const State* const states[],const size_t length,const size_t capacity)
    :_states(capacity)
    {
        int i;
        foreachArray(i, length)
        {
            State* const state = states[i] -> NewSelf();
            _states.Add(state);
        }
    }
    
    
    AlternativeChart::~AlternativeChart()
    {
        int i;
        foreachArray(i, _states.length())
        {
            _states[i] -> DeleteSelf();
            _states[i] = nullptr;
        }
    }
    
    bool AlternativeChart::Pass(const State &state) const
    {
        int i;
        foreachList(i,_states)
        {
            if(_states[i] -> StateEquals(state))
                return true;
        }
        
        return false;
    }
    
    ////////////////////////////////////////////////////////////
    
    Utf8State::Utf8State(utf8::uchar chr)
    :_Char(chr)
    {
    }
    
    bool Utf8State::StateEquals(const st::State &state) const
    {
        const Utf8State* utf8State = dynamic_cast<const Utf8State*>(&state);
        if(!utf8State)
            return false;
        return _Char == utf8State -> GetChar();
    }
    
    ////////////////////////////////////////////////////////////
    
    static Utf8State  utf8Char_A = 'A', utf8Char_B = 'B', utf8Char_C = 'C',
    utf8Char_D = 'D', utf8Char_E = 'E', utf8Char_F = 'F', utf8Char_G = 'G',
    utf8Char_H = 'H', utf8Char_I = 'I', utf8Char_J = 'J', utf8Char_K = 'K',
    utf8Char_L = 'L', utf8Char_M = 'M', utf8Char_N = 'N', utf8Char_O = 'O',
    utf8Char_P = 'P', utf8Char_Q = 'Q', utf8Char_R = 'R', utf8Char_S = 'S',
    utf8Char_T = 'T', utf8Char_U = 'U', utf8Char_V = 'V', utf8Char_W = 'W',
    utf8Char_X = 'X', utf8Char_Y = 'Y', utf8Char_Z = 'Z';
    
    static Utf8State  utf8Char_a = 'a', utf8Char_b = 'b', utf8Char_c = 'c',
    utf8Char_d = 'd', utf8Char_e = 'e', utf8Char_f = 'f', utf8Char_g = 'g',
    utf8Char_h = 'h', utf8Char_i = 'i', utf8Char_j = 'j', utf8Char_k = 'k',
    utf8Char_l = 'l', utf8Char_m = 'm', utf8Char_n = 'n', utf8Char_o = 'o',
    utf8Char_p = 'p', utf8Char_q = 'q', utf8Char_r = 'r', utf8Char_s = 's',
    utf8Char_t = 't', utf8Char_u = 'u', utf8Char_v = 'v', utf8Char_w = 'w',
    utf8Char_x = 'x', utf8Char_y = 'y', utf8Char_z = 'z';
    
    
    static Utf8State utf8Char_0 = '0', utf8Char_1 = '1', utf8Char_2 = '2',
    utf8Char_3 = '3', utf8Char_4 = '4', utf8Char_5 = '5', utf8Char_6 = '6',
    utf8Char_7 = '7', utf8Char_8 = '8', utf8Char_9 = '9';
    
    
    static Utf8State utf8Char_plus = '+', utf8Char_minus = '-',
    utf8Char_multip = '*', utf8Char_divided = '\\', Utf8Char_equals = '=',
    utf8Char_or = '|', utf8Char_and = '&', utf8Char_point = '.',
    utf8Char_not = '!', utf8Char_less = '<', utf8Char_more = '>',
    utf8Char_parenthesis_left = '(', utf8_parenthesis_right = ')',
    utf8Char_square_brackets_left = '[', utf8Char_square_brackets_right = ']',
    utf8Char_curly_braces_left = '{', utf8Char_curly_braces_right = '}';
    
    static Utf8State utf8Char_question = '?', utf8Char_dollar = '$',
    utf8Char_percent = '%', utf8Char_underline = '_';
    
    ////////////////////////////////////////////////////////////
    
    const int LetterChart::CHAR_LENGTH = 52;
    
    State* LetterChart::CHARS[] =
    {
        &utf8Char_A, &utf8Char_B, &utf8Char_C, &utf8Char_D, &utf8Char_E,
        &utf8Char_F, &utf8Char_G, &utf8Char_H, &utf8Char_I, &utf8Char_J,
        &utf8Char_K, &utf8Char_L, &utf8Char_M, &utf8Char_N, &utf8Char_O,
        &utf8Char_P, &utf8Char_Q, &utf8Char_R, &utf8Char_S, &utf8Char_T,
        &utf8Char_U, &utf8Char_V, &utf8Char_W, &utf8Char_X, &utf8Char_Y,
        &utf8Char_Z,
        &utf8Char_a, &utf8Char_b, &utf8Char_c, &utf8Char_d, &utf8Char_e,
        &utf8Char_f, &utf8Char_g, &utf8Char_h, &utf8Char_i, &utf8Char_j,
        &utf8Char_k, &utf8Char_l, &utf8Char_m, &utf8Char_n, &utf8Char_o,
        &utf8Char_p, &utf8Char_q, &utf8Char_r, &utf8Char_s, &utf8Char_t,
        &utf8Char_u, &utf8Char_v, &utf8Char_w, &utf8Char_x, &utf8Char_y,
        &utf8Char_z
    };

    LetterChart::LetterChart()
    :AlternativeChart(CHARS,CHAR_LENGTH){
    };

    ////////////////////////////////////////////////////////////
    
    const int DigitChart::CHAR_LENGTH = 10;
    
    State* DigitChart::CHARS[] =
    {
        &utf8Char_0, &utf8Char_1, &utf8Char_2, &utf8Char_3, &utf8Char_4,
        &utf8Char_5, &utf8Char_6, &utf8Char_7, &utf8Char_8, &utf8Char_9
    };
    
    DigitChart::DigitChart()
    :AlternativeChart(CHARS,CHAR_LENGTH){
    };
    
    ////////////////////////////////////////////////////////////
    
    const int XDigitChart::CHAR_LENGTH = 15;
    
    State* XDigitChart::CHARS[]  =
    {
        
        &utf8Char_0, &utf8Char_1, &utf8Char_2, &utf8Char_3, &utf8Char_4,
        &utf8Char_5, &utf8Char_6, &utf8Char_7, &utf8Char_8, &utf8Char_9,
        &utf8Char_A, &utf8Char_B, &utf8Char_C, &utf8Char_D, &utf8Char_E,
        &utf8Char_F, &utf8Char_a, &utf8Char_b, &utf8Char_c, &utf8Char_d,
        &utf8Char_e, &utf8Char_f
    };
    
    XDigitChart::XDigitChart()
    :AlternativeChart(CHARS,CHAR_LENGTH)
    {
    };
    
    ////////////////////////////////////////////////////////////
    
}
