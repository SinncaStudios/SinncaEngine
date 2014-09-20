//
//  Action.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/13/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Action__
#define __SinncaEngine__Action__

#include <iostream>
#include "Types.h"
#include "Timer.h"

namespace sinnca
{
	class action
	{
		uint cooldown, overrideLimit;
		timer t;
		std::string luaFunc;
		
	public:
		
		action(std::string n);
		~action();
		
		// call the function if cooldown allows
		bool call();
		// call the function regardless of cooldown
		bool callOverride();
		
	};
}

#endif /* defined(__SinncaEngine__Action__) */
