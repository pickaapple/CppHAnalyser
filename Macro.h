//
//  Macro.h
//  CppAnalyser
//
//  Created by yhys on 2017/7/2.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Macro_h
#define Macro_h

#include "Checks.hpp"

#define DECLARE_ATTRI(type,attri)                                   \
protected:                                                          \
    type _##attri;                                                  \
public:                                                             \
    type&    Get##attri () const { return _##attri;}                 \
    void    Set##attri (const type& attri) { _##attri = attri;}     \


#define DECLARE_ATTRI_PTR(type,attri)                               \
protected:                                                          \
    type _##attri;                                                  \
public:                                                             \
    type&    Get##attri () const { return _##attri;}                 \
    void    Set##attri (type const attri) { _##attri = attri;}      \


#define DECLARE_ATTRI_QUICKLY(class,type,attri)                             \
protected:                                                                  \
    type _##attri;                                                          \
public:                                                                     \
    type&    Get##attri () const { return _##attri;}                        \
    class*  Set##attri (const type& attri) { _##attri = attri;return this;} \




#define DECLARE_SELF_CONTROL_VIRTUAL(class)                 \
public:                                                     \
    virtual class * NewSelf() const = 0;                    \
    virtual void DeleteSelf() = 0;                          \


#define DECLARE_SELF_CONTROL_OVERRIDE(class,parrent)        \
public:                                                     \
    virtual parrent * NewSelf() const override              \
    {                                                       \
        class * pclass = new class();                       \
        ASSERT(pclass);                                     \
        return pclass;                                      \
    }                                                       \
                                                            \
    virtual void DeleteSelf() override                      \
    {                                                       \
        delete this;                                        \
    }                                                       \


#define foreachList(i,list) for(i = 0 ; i < list.length() ; ++i)
#define foreachArray(i,l) for(i = 0 ; i < l ; ++i)

#endif /* Macro_h */
