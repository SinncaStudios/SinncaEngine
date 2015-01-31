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
		std::string luaFunc, name;
		
	public:
		
		action(std::string n);
		~action();
		
		// call the function if cooldown allows
		virtual int call();
		// call the function regardless of cooldown
		int callOverride();
		
		void setCoolDown(uint cd);
		void setOverride(uint ov);
		void setFunction(std::string);
		
	};
	
	#define createAction(a) new(a)action(a)
	action* checkAction(int ind);
	
	void registerAction(lua_State* L);
}

#endif /* defined(__SinncaEngine__Action__) */
