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
	//////////////////////////////////////////////////////////////////////////

	class FlagWord
	{
	public:
		struct Flag
		{
			char _Flag;
			int _Type;
		};

		void AddFlag(char flag,int type);

		FlagWord();

		virtual ~FlagWord();
	protected:
		DECLARE_ATTRI_REF(List<Flag>,Flags)

		DECLARE_ATTRI_REF(string, Word)
	};

	//////////////////////////////////////////////////////////////////////////

	class MLexer
	{
	public:

		typedef char char_size;

		enum EParttenType
		{
			WORD,
			SYMBOL,
			SPLIT
		};

		void Input(const string& oneLine);

		bool FindFlagByWord(FlagWord& flagWord) const;

		void Lexer();

		const List<FlagWord>& Output() const;

		MLexer();
		virtual ~MLexer();
	private:
		void Initialize();

	protected:
		String<char_size>			_BufferString;

		List<FlagWord>	_WordsStore;

		Tree<char_size>		_ParttenTree;

		static const char_size*		PARTTEN_WORD[];

		static const char_size		PARTTEN_SYMBOL[];

		static const char_size		PARTTEN_WORD_SPLIT[];
	};

}
#endif /* Lexer_hpp */
