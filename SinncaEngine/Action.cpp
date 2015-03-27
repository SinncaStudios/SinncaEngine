//
//  Action.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/13/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Action.h"
#include "Tree.h"

namespace sinnca
{
	action::action(std::string n) :
	cooldown(0),
	overrideLimit(0),
	luaFunc("")
	{
		name = n;
	}
	
	
	int action::call()
	{
		
		if (t.getTicks() >= cooldown)
		{
			
			if (luaFunc != "")
			{
				Script::getGlobal(name);
			
				Script::getLocal(-1, luaFunc);
				Script::call(0, 0);
				
				t.start();
				
				return 0;
			}
		}
		
		// cooldown not met yet
		return -1;
	}
	
	int action::callOverride()
	{
		if (t.getTicks() >= overrideLimit)
		{
			if (luaFunc != "")
			{
				Script::getGlobal(name);
				
				Script::getLocal(-1, luaFunc);
				Script::call(0, 0);
				
				t.start();
				
				return 0;
			}
		}
		
		// override not allowed yet
		return -1;
	}
	
	void action::setCoolDown(uint cd)
	{
		cooldown = cd;
	}
	
	void action::setOverride(uint ov)
	{
		overrideLimit = ov;
	}
	
	void action::setFunction(std::string f)
	{
		luaFunc = f;
	}
	
	void* action::operator new(size_t s, std::string n)
	{
		//Create object in lua
		
		
		Script::newBlankTable();
		
		Script::pushValue(1);
		Script::setMetaTable(-2);
		
		Script::pushValue(1);
		Script::setField(1, "__index");
		
		action** ac = (action**)lua_newuserdata(Script::getState(), sizeof(action*));
		if (Tree::currentScene->assets.actionStorage != NULL)
		{
			*ac = (action*)Tree::currentScene->assets.actionStorage->allocate((unsigned int)s, __alignof(action));
			
		} else {
			
			*ac = (action*)Heap->allocate((unsigned int)s, __alignof(action));
		}
		
		//(*en)->name = n;
		
		Script::getMetaTable("buffer");
		Script::setMetaTable(-2);
		
		Script::setField(-2, "__self");
		
		
		Script::setGlobal(n);
		Tree::currentScene->assets.actionRef.push_back(*ac);
		return ((void*)*ac);
	}
	void action::operator delete(void *p)
	{
		if (Tree::currentScene->assets.actionStorage != NULL)
		{
			Tree::currentScene->assets.actionStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
	
	static int l_newAction(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n != 2)
		{
			return luaL_error(L, "You need to name this action...");
		}
		
		Script::checkTable(1);
		//new(luaL_checkstring(L, 2)) entity(luaL_checkstring(L, 2));
		createAction(luaL_checkstring(L, 2));
		return 0;
	}
	
	static const luaL_Reg actionFuncs[] = {
		{"new", l_newAction},
		{NULL, NULL}
	};
	
	void registerAction(lua_State* L)
	{
		luaL_newmetatable(L, "action");
		
		luaL_register(L, 0, actionFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		luaL_register(L, "action", actionFuncs);
	}
	
}