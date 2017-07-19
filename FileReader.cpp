//
//  FileReader.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/4.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include <iostream>

#include "FileReader.hpp"
#include "Checks.hpp"

namespace st{

	bool MFileReader::ReadLine(string& line)
	{
		ASSERT(_ifs.is_open());
		if (_ifs.eof())
			return false;
		const std::streamsize buffSize = 4;
		char buff[buffSize];
		do{	
			//buff full
			_ifs.clear();
			_ifs.getline(buff, buffSize);
			line.Append(buff, _ifs.gcount());
		}
		while (_ifs.fail());
		line.Append('\n');		//replace last character to '\n'
		return true;
	}

	bool MFileReader::ReadFile(const char *szFile)
	{
        _ifs.clear();
		_ifs.open(szFile);
        return !_ifs.fail();
    }

	MFileReader::MFileReader()
	{

	}

	MFileReader::~MFileReader()
	{
		_ifs.close();
	}

}
