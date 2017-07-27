//
//  Lexer.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "Lexer.hpp"
namespace st {

	

	//////////////////////////////////////////////////////////////////////////
	void FlagWord::AddFlag(char flag, int type)
	{
		_Flags.AddAtLast({ flag,type });
	}

	FlagWord::FlagWord()
	{
	}

	FlagWord::~FlagWord()
	{
	}
	//////////////////////////////////////////////////////////////////////////

	const MLexer::char_size* MLexer::PARTTEN_WORD[] =
	{
		//template
		"template",
		"class",
		"typename",

		//data space
		"namespace",

		//data structure
		"class",
		"struct",
		"enum",

		//classes relationship
		"friend",

		//class function specifiers
		"virtual",
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

		//end flag
		"\0"
	};
	const MLexer::char_size MLexer::PARTTEN_SYMBOL[] =
	{
		//
		'=',
		//
		'*',
		'&',
		//
		':',
		';',
		'(',
		')',
		'[',
		']',
		'{',
		'}',
		'<',
		'>',
		'\0'
	};

	const MLexer::char_size MLexer::PARTTEN_WORD_SPLIT[] =
	{
		'\0',
		'\n',
		' ',
		'e'
	};
	void MLexer::Initialize()
	{
		FlagNode::Flag flag;
		size_t i;
		size_t parttenCount = strsize(PARTTEN_WORD, '\0');
		foreachArray(i, parttenCount)
		{
			flag._Flag = i;
			flag._Type = EParttenType::WORD;
			INode<char_size>* node = _ParttenTree.InjectTreeNodes(PARTTEN_WORD[i], strlen(PARTTEN_WORD[i]));

			//set flag
			FlagNode* flagNode = FindFlagNodeUnderNode<char_size>(node);
			//if the node is not a flag before,create a flag node below it
			if (!flagNode)
			{
				flagNode = NewNode<FlagNode>();
				node->AddChild(flagNode);
			}
			flagNode->GetFlags().AddAtLast(flag);
		}
	}

	void MLexer::Input(const string& oneLine)
	{
		_BufferString.Append(oneLine);
	}

	bool MLexer::FindFlagByWord(FlagWord& flagWord) const
	{
		FlagNode* flagNode = FindFlagNodeInTrie<char_size>(flagWord.GetWord().GetElements(), flagWord.GetWord().length(), _ParttenTree);
		if (flagNode) 
		{
			int i;
			foreachList(i, flagNode->GetFlags())
			{
				FlagNode::Flag flag = flagNode->GetFlags()[i];
				flagWord.AddFlag(flag._Flag,flag._Type);
			}
		}
		return !!flagNode;
	}

	void MLexer::Lexer()
	{
		if (0 == _BufferString.length())
			return;
		bool IsSysmbolChar;
		char currentChar;
		int i, IndexSymbolChar;
		int wordLength = 0;
		const char_size* chrStart = _BufferString.GetElements();
		foreachArray(i, _BufferString.length() + 1) 
		{
			currentChar = _BufferString[i];
			// if the character is symbol,store it.
			if (IsSysmbolChar = IfElementInArray(PARTTEN_SYMBOL, strlen(PARTTEN_SYMBOL), currentChar, IndexSymbolChar))
			{
				FlagWord flagWord;
				flagWord.GetWord().Append(chrStart, 1);
				flagWord.AddFlag(PARTTEN_SYMBOL[IndexSymbolChar], EParttenType::SYMBOL);
				_WordsStore.AddAtLast(flagWord);
			}

			// if the character is symbol or word split,get the word when the length is bigger than zero
			if (IsSysmbolChar || IfElementInArray(PARTTEN_WORD_SPLIT,strlen(PARTTEN_WORD_SPLIT,'e'), currentChar))
			{
				if (0 == wordLength)
				{
					++chrStart;
					continue;
				}
				
				FlagWord flagWord;
				flagWord.GetWord().Append(chrStart, wordLength);
				FindFlagByWord(flagWord);
				_WordsStore.AddAtLast(flagWord);

				//initialize for next word
				chrStart += (wordLength + 1);
				wordLength = 0;
				continue;
			}
			++wordLength;
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


}
