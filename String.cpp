//
//  String.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/6/19.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "String.hpp"
namespace st{

	size_t strlen(const char *str)
	{
		if (0 == str)
			return 0;
		size_t length = 0;
		while ('\0' != *(str++))
			++length;
		return length;
	}

}
