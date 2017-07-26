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
		//keyword
		"template",
		"typename",
		"namespace",
		"class",
		"struct",
		"enum",
		"friend",
		"override",
		"explicit",
		//c v type qualifiers			//常变量修饰符
		"const",
		"volatile",
		"mutable",
		//access specifiers				//访问修饰符
		"public",
		"protected",
		"private",
		//storage duration specifiers	//存储时间修饰符
		"auto",				//timeout
		"register",			//timeout
		"static",
		"extern",
		"thread_local",		//c++ 11
		//fundamental types				//基础类型
		//| __type
		//		|__void type
		"void",
		//		|__boolean type
		"bool",
		//		|__character type
		"char",
		"wchar_t",
		"char16_t",
		"char32_t",
		//		|__integer type
		"short",
		"long",
		"int",
		//		| __floating point type
		"float",
		"double",
		//		| __signedness
		"signed",
		"unsigned",
		//		|__size
		"short",
		"long",
		"\0"
	};
	void MLexer::Initialize()
	{
		unsigned int i;
		unsigned int parttenCount = strsize(PARTTEN_STRING, '\0');
		foreachArray(i, parttenCount)
		{
			_ParttenTree.InjectNodes(PARTTEN_STRING[i], strlen(PARTTEN_STRING[i]));
		}
		SetInvalidFlag(parttenCount + 1);
	}

	void MLexer::Input(const string& oneLine)
	{
		_BufferString.Append(oneLine);
	}

	unsigned char MLexer::FindFlagByWord(const string &word) const
	{
		TreeNode<char> flagNode;
		if (!FindFlagNodeInTrie(word.GetElements(), word.length(), _ParttenTree, flagNode))
			return _InvalidFlag;
		return (unsigned char)flagNode.GetPayload();
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
		:_ParttenTree('R')
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
