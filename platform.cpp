//
//  platform.cpp
//  CppAnalyser
//
//  Created by yhys on 2017/7/2.
//  Copyright © 2017年 STRAWBERRY STUDIO. All rights reserved.
//

#include "platform.hpp"

#include <stdlib.h>

namespace st{
    namespace OS{
        void Abort(){
            abort();
        };
    }
}
