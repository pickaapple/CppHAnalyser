//
//  Lexer.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Lexer.hpp"
namespace st {
	void MLexer::Initialize()
	{

	}

	void MLexer::Input(const string& oneLine)
	{
		_bufferString.Append(oneLine);
	}

	unsigned char MLexer::FindFlagByWord(const string &word) const
	{
		return 1;
	}

	void MLexer::Lexer()
	{
		if (0 == _bufferString.length())
			return;
		int i;
		int wordLength = 0;
		const char* chrStart = _bufferString.GetElements();
		foreachArray(i, _bufferString.length() + 1) 
		{
			if (' '		== _bufferString[i]||
				'\0'	== _bufferString[i]||
				'\n'	== _bufferString[i])
			{
				if (0 == wordLength)
				{
					++chrStart;
					continue;
				}
				
				FlagWord flagWord;
				flagWord.word.Append(chrStart, wordLength);
				flagWord.flag = FindFlagByWord(flagWord.word);
				_wordsStore.AddAtLast(flagWord);

				//initialize for next word
				chrStart += (wordLength + 1);
				wordLength = 0;
			}
			else
			{
				++wordLength;
			}
		}
		_bufferString.Remove(0, i - wordLength - 1);
	}

	const List<FlagWord>& MLexer::Output() const
	{
		return _wordsStore;
	}

	MLexer::MLexer()
	{

	}

	MLexer::~MLexer()
	{

	}
	
	//////////////////////////////////////////////////////////////////////////

	unsigned char LexerDiagram::CheckFlag(const string& str)
	{
        return 'a';
	}

	LexerDiagram::LexerDiagram()
	{

	}

	LexerDiagram::~LexerDiagram()
	{

	}

}
