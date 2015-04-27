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
	
	timer::timer() :
	startTicks(0),
	pauseTicks(0),
	started(false),
	paused(false)
	{
		
	}

	timer::~timer()
	{
		Script::unReference(ref);
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
	
	void* timer::operator new(size_t s, bool l)
	{
		timer* tm;
		
		if (!l)
		{
			//not being created through lua
			tm = (timer*)Heap->allocate(sizeof(timer), alignof(timer));
			
		} else {
			
			tm = Script::createObject<timer>();
			tm->ref = Script::makeReference();
		}
		
		return (void*)tm;
	}
	
	void timer::operator delete(void* p)
	{
		Heap->deallocate(p);
	}


	/*
	 lua functions
	 */


	static int l_newTimer(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 1)
		{
			return luaL_error(L, "You need to name this timer...");
		}
		
		Script::checkTable(1);
		new(true) timer();
		return 0;
	}

	static int l_start(lua_State* L)
	{
		int n = lua_gettop(L);
		timer* t;
		
		if (n == 1)
		{
			t = Script::checkType<timer>(1);
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
			t = Script::checkType<timer>(1);
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
			t = Script::checkType<timer>(1);
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
			t = Script::checkType<timer>(1);
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
		Script::registerType<timer>(timerFuncs);
	}

}
