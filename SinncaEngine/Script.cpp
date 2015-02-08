//
//  Script.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#include "Script.h"
#include "MemoryManager.h"
#include "Heap.h"

namespace sinnca
{

	luaScript* luaScript::_instance = NULL;

	luaScript::luaScript()
	{
		// Execute the script
		L = lua_open();
		
		
		// start lua
		luaL_openlibs(L);
		
		bindFunctions();
		
	}


	luaScript* luaScript::Instance()
	{
		if (_instance == NULL)
		{
			//_instance = new luaScript();
			//_instance = memoryManager->systems->allocateNew<luaScript>();
			//_instance = new (memoryManager->systems->allocateNew<luaScript>()) luaScript();
			_instance = new (Heap->allocateNew<luaScript>()) luaScript();
		}
		return _instance;
	}
	
	lua_State* luaScript::getState()
	{
		return L;
	}

	void luaScript::doFile(std::string file)
	{
		luaL_dofile(L, file.c_str());
		/*
		 try
		 {
		 
		 luaL_dofile(L, file.c_str());
		 
		 }
		 catch (const std::exception &TheError)
		 {
		 
		 std::cout << TheError.what();
		 
		 }
		 */
	}

	void luaScript::doString(std::string str)
	{
		luaL_dostring(L, str.c_str());
	}


	void luaScript::setVar(std::string var, int i)
	{
		lua_pushinteger(L, i);
		lua_setglobal(L, var.c_str());
		//lua_pop(L, 1);
	}
	void luaScript::setVar(std::string var, float i)
	{
		lua_pushnumber(L, i);
		lua_setglobal(L, var.c_str());
		//lua_pop(L, 1);
	}
	void luaScript::setVar(std::string var, std::string i)
	{
		lua_pushstring(L, i.c_str());
		lua_setglobal(L, var.c_str());
		//lua_pop(L, 1);
	}
	void luaScript::setMetaTable(int i)
	{
		lua_setmetatable(L, i);
	}
	void luaScript::getMetaTable(std::string m)
	{
		luaL_getmetatable(L, m.c_str());
	}
	
	void luaScript::setTable(int i)
	{
		lua_settable(L, i);
	}
	


	void luaScript::getGlobal(std::string glb)
	{
		lua_getglobal(L, glb.c_str());
	}
	void luaScript::getLocal(int ind,std::string loc)
	{
		/*
		 luaL_checktype(L, ind, LUA_TTABLE);
		 
		 lua_pushstring(L, loc.c_str());
		 lua_gettable(L, ind);
		 */
		lua_getfield(L, ind, loc.c_str());
	}



	void luaScript::push(int i)
	{
		lua_pushinteger(L, i);
	}
	void luaScript::push(float f)
	{
		lua_pushnumber(L, f);
	}
	void luaScript::push(std::string str)
	{
		lua_pushstring(L, str.c_str());
	}
	void luaScript::pushValue(int i)
	{
		lua_pushvalue(L, i);
	}
	
	void luaScript::checkTable(int ind)
	{
		luaL_checktype(L, ind, LUA_TTABLE);
	}
	std::string luaScript::checkString(int ind)
	{
		return luaL_checkstring(L, ind);
	}

	bool luaScript::call(int args, int results)
	{
		if (!lua_isfunction(L, -1))
		{
			lua_pop(L, 1);
			return false;
		}
		if (lua_pcall(L, args, results, 0) != 0)
		{
			printf("error running function `f': %s", lua_tostring(L, -1));
			return false;
		}
		return true;
	}
	

	void luaScript::newBlankTable()
	{
		lua_newtable(L);
	}
	void luaScript::setTableField(const char* key, int i)
	{
		lua_pushstring(L, key);
		lua_pushinteger(L, i);
		
		lua_settable(L, -3);
	}
	void luaScript::setTableField(const char* key, float i)
	{
		lua_pushstring(L, key);
		lua_pushnumber(L, i);
		
		lua_settable(L, -3);
	}
	void luaScript::setTableField(const char* key, const char* str)
	{
		lua_pushstring(L, key);
		lua_pushstring(L, str);
		
		lua_settable(L, -3);
	}
	void luaScript::setField(int i, const char * key)
	{
		lua_setfield(L, i, key);
	}


	void luaScript::setGlobal(std::string name)
	{
		lua_setglobal(L, name.c_str());
	}


	luaScript::~luaScript()
	{
		
		lua_close(L);
		
	}
}