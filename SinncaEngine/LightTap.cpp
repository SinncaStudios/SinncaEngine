//
//  LightTap.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/19/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "LightTap.h"
#include "TimeKeeping.h"

namespace sinnca
{

	// a button tap quicker then the time limit will trigger this
	
	void lightTap::update()
	{
		if (cause->x > 0.0)
		{
			if (cause->didChange)
			{
				durration = TimeKeeper::getTicks();
			}
			
			if ((TimeKeeper::getTicks() - durration) > durration)
			{
				if (effect)
				{
					effect->call();
					wasCaused = true;
					return;
				}
			}
			wasCaused = false;
		}
		wasCaused = false;
	}
	
	
	
	// lua stuff
	static const luaL_Reg tapFuncs[] = {
		
		{NULL, NULL}
	};
	
	void registerLightTap(lua_State* L)
	{
		luaL_newmetatable(L, "lightTap");
		
		luaL_register(L, 0, tapFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		luaL_register(L, "lightTap", tapFuncs);
	}
	
	
}