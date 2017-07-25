//
//  Lexer.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Lexer.hpp"
namespace st {
	const char* MLexer::PARTTEN_STRING[] = 
	{
		"template",
		"typename",
		"namespace",
		"class",
		"struct",
		"enum",
		"friend",
		"override",
		"explicit",
		"const",
		"volatile",
		"mutable",
		"public",
		"protected",
		"private",
		"auto",
		"register",
		"static",
		"extern",
		"thread_local",
		"void",
		"bool",
		"char",
		"wchar_t",
		"char16_t",
		"char32_t",
		"short",
		"long",
		"int",
		"long",
		"int",
		"float",
		"double",
		"signed",
		"unsigned",
		"short",
		"long long",
		"\0"
	};
	void MLexer::Initialize()
	{
		unsigned int i;
		foreachArray(i, PARTTEN_COUNT)
		{
			_ParttenTree.InjectNodes(PARTTEN_STRING[i], strsize(PARTTEN_STRING, '\0'));
		}
	}

	void MLexer::Input(const string& oneLine)
	{
		_BufferString.Append(oneLine);
	}

	unsigned char MLexer::FindFlagByWord(const string &word) const
	{
		return 1;
	}

	void MLexer::Lexer()
	{
		if (0 == _BufferString.length())
			return;
		int i;
		int wordLength = 0;
		const char* chrStart = _BufferString.GetElements();
		foreachArray(i, _BufferString.length() + 1) 
		{
			if (' '		== _BufferString[i]||
				'\0'	== _BufferString[i]||
				'\n'	== _BufferString[i])
			{
				if (0 == wordLength)
				{
					++chrStart;
					continue;
				}
				
				FlagWord flagWord;
				flagWord.word.Append(chrStart, wordLength);
				flagWord.flag = FindFlagByWord(flagWord.word);
				_WordsStore.AddAtLast(flagWord);

				//initialize for next word
				chrStart += (wordLength + 1);
				wordLength = 0;
			}
			else
			{
				++wordLength;
			}
		}
		_BufferString.Remove(0, i - wordLength - 1);
	}

	const List<FlagWord>& MLexer::Output() const
	{
		return _WordsStore;
	}

	MLexer::MLexer()
	{
		Initialize();
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
