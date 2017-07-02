//
//  Macro.h
//  CppAnalyser
//
//  Created by yhys on 2017/7/2.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

#define DECLARE_ATTRI(type,name) \
protected:\
    type _##name;\
public:\
    type    Get##name () const { return _##name;}\
    void    Set##name (type name) { _##name = name;}

#endif /* Macro_h */
