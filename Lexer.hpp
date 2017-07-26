//
//  Lexer.hpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#ifndef Lexer_hpp
#define Lexer_hpp

#include "Instance.hpp"
#include "List.hpp"
#include "String.hpp"
#include "Tree.hpp"

namespace st
{
	/*
	template
	typename

	namespace
	class
	struct
	enum

	friend

	override
	explicit
	
	c v type qualifiers			//常变量修饰符
		|__const
		|__volatile
		|__mutable

	access specifiers			//访问修饰符
		|__public
		|__protected
		|__private

	storage duration specifiers	//存储时间修饰符
		|__auto			timeout
		|__register		timeout
		|__static
		|__extern
		|__thread_local	c++ 11

	fundamental types			//基础类型
		|__type
			|__void type
				|__void
			|__boolean type
				|__bool
			|__character type
				|__char
				|__wchar_t
				|__char16_t c++ 11
				|__char32_t	c++ 11
			|__integer type
				|__short
				|__long
				|__int
			|__floating point type
				|__float
				|__double
		|__modifiers
			|__signedness
				|__signed
				|__unsigned
			|__size
				|__short
				|__long
				|__long long

	*/
	class LexerDiagram
	{
	public:
		unsigned char CheckFlag(const string& str);

		LexerDiagram();

		virtual ~LexerDiagram();
	protected:

	};

	//////////////////////////////////////////////////////////////////////////

    struct FlagWord
	{
		unsigned char flag;
        string word;
    };
	
	//////////////////////////////////////////////////////////////////////////

    class MLexer
    {
    public:
        void Input(const string& oneLine);
        
		unsigned char FindFlagByWord(const string &word) const;

        void Lexer();

        const List<FlagWord>& Output() const;
        
        MLexer();
        virtual ~MLexer();
	private:
		void Initialize();

	protected:
		string			_BufferString;
        List<FlagWord>	_WordsStore;
		Tree<char>		_ParttenTree;
		static const char*		PARTTEN_STRING[];

		DECLARE_ATTRI(unsigned int,InvalidFlag)
	};

}
#endif /* Lexer_hpp */
