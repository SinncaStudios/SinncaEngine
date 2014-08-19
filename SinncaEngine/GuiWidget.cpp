//
//  GuiWidget.c
//  SinncaEngine
//
//  Created by Ryan Oldis on 3/17/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "GuiWidget.h"

namespace sinnca
{
	
	void registerWidget(lua_State* L)
	{
		luaL_register(L, "widget", widgetFuncs);
		
		lua_pushvalue(L, -1);
		lua_setfield(L, -2, "__index");
	}
}
