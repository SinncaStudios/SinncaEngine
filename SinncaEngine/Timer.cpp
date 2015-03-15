//
//  Timer.cpp
//  Sinnca Engine
//
//  Created by Ryan Oldis on 2/21/12.
//  Copyright (c) 2012 Sinnca Studios. All rights reserved.
//

#include "Timer.h"


namespace sinnca
{
	
	sinncaTime getCurrentTicks()
	{
		#ifdef snApple
		return CFAbsoluteTimeGetCurrent();
		#elif snWindows
		sinncaTime temp;
		QueryPerformanceFrequency(&temp);
		return temp;
		#endif
	}
	
	timer::timer()
	{
		startTicks = 0;
		pauseTicks = 0;
		
		started = false;
		paused = false;
		
	}

	void timer::setName(std::string n)
	{
		name = n;
	}

	void timer::start()
	{
		started = true;
		paused = false;
		
		startTicks = getCurrentTicks();
	}

	void timer::pause()
	{
		if ((started == true) && (paused == false))
		{
			paused = true;
			pauseTicks = getCurrentTicks() - startTicks;
		}
	}

	void timer::resume()
	{
		if (paused == true)
		{
			paused = false;
			
			startTicks = getCurrentTicks() - pauseTicks;
			
			pauseTicks = 0;
		}
	}


	sinncaTime timer::getTicks()
	{
		if (started == true)
		{
			if (paused == true)
			{
				return pauseTicks;
			} else {
				
				return getCurrentTicks() - startTicks;
			}
		}
		
		return 0;
	}


	/*
	 lua functions
	 */

	timer* checkTimer(lua_State* L, int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(L, ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(L, "__self");
		// get our table
		lua_gettable(L, ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<timer*>((timer*)lua_touserdata(L, -1));
		luaL_argcheck(L, ud != 0, ind, "Incompatible 'timer' type...");
		
		return *((timer**)ud);
	}

	static int l_newTimer(lua_State* L)
	{
		int n = lua_gettop(L);
		
		if (n == 2)
		{
			luaL_checktype(L, 1, LUA_TTABLE);
			
			lua_newtable(L);
			
			lua_pushvalue(L, 1);
			lua_setmetatable(L, -2);
			lua_pushvalue(L, 1);
			lua_setfield(L, 1, "__index");
			
			timer** t = (timer**)lua_newuserdata(L, sizeof(timer*));
			*t = new timer();
			
			(*t)->setName(luaL_checkstring(L, 2));
			
			luaL_getmetatable(L, "timer");
			lua_setmetatable(L, -2);
			
			lua_setfield(L, -2, "__self");
			
			
			lua_setglobal(L, luaL_checkstring(L, 2));
		}
		
		return 1;
	}

	static int l_start(lua_State* L)
	{
		int n = lua_gettop(L);
		timer* t;
		
		if (n == 1)
		{
			t = checkTimer(L, 1);
			t->start();
		}
		
		return 1;
	}

	static int l_pause(lua_State* L)
	{
		int n = lua_gettop(L);
		timer* t;
		
		if (n == 1)
		{
			t = checkTimer(L, 1);
			t->pause();
		}
		
		return 1;
	}

	static int l_resume(lua_State* L)
	{
		int n = lua_gettop(L);
		timer* t;
		
		if (n == 1)
		{
			t = checkTimer(L, 1);
			t->resume();
		}
		
		return 1;
	}

	static int l_getTicks(lua_State* L)
	{
		int n = lua_gettop(L);
		timer* t;
		
		if (n == 1)
		{
			t = checkTimer(L, 1);
			lua_pushnumber(L, t->getTicks());
		}
		return 1;
	}


	static const luaL_Reg timerFuncs[] = {
		
		{"new", l_newTimer},
		{"start", l_start},
		{"pause", l_pause},
		{"resume", l_resume},
		{"getRawTime", l_getTicks},
		{NULL, NULL}
	};

	void registerTimer(lua_State* L)
	{
		luaL_newmetatable(L, "timer");
		
		luaL_register(L, 0, timerFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		luaL_register(L, "timer", timerFuncs);
	}

}
