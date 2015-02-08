//
//  DigitalButton.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/5/15.
//  Copyright (c) 2015 Ryan Oldis. All rights reserved.
//

#include "DigitalButton.h"

namespace sinnca
{
	void digitalButton::setDown(int s)
	{
		x = (float)s;
	}
	
	
	static const luaL_Reg buttonFuncs[] = {
		{"isDown", l_isDown},
		{"isUp", l_isUp},
		{"wasPressed", l_wasPressed},
		{"wasReleased", l_wasReleased},
		{"getPressure", l_getRawPressure},
		{NULL, NULL}
	};
	
	void registerButton(lua_State* L)
	{
		luaL_newmetatable(L, "button");
		
		luaL_register(L, 0, buttonFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		luaL_register(L, "button", buttonFuncs);
	}
	
}
