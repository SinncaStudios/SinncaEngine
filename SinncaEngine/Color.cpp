//
//  Color.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 7/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Color.h"
#include "Script.h"

namespace sinnca
{
	// duplicate symbols appear if this is defined in color.h
	
	color* checkColor(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<color*>((color*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'color' type...");
		
		return *((color**)ud);
	}
}