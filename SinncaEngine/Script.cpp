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
	
	namespace Script
	{
		lua_State* L;
		
		void setup()
		{
			// Execute the script
			L = lua_open();
			
			
			// start lua
			luaL_openlibs(L);
		}
		
		void shutdown()
		{
			lua_close(L);
		}
		
		lua_State* getState()
		{
			return L;
		}
		
		void doFile(std::string file)
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
		
		void doString(std::string str)
		{
			luaL_dostring(L, str.c_str());
		}
		
		
		void setVar(std::string var, int i)
		{
			lua_pushinteger(L, i);
			lua_setglobal(L, var.c_str());
			//lua_pop(L, 1);
		}
		void setVar(std::string var, float i)
		{
			lua_pushnumber(L, i);
			lua_setglobal(L, var.c_str());
			//lua_pop(L, 1);
		}
		void setVar(std::string var, std::string i)
		{
			lua_pushstring(L, i.c_str());
			lua_setglobal(L, var.c_str());
			//lua_pop(L, 1);
		}
		void setMetaTable(int i)
		{
			lua_setmetatable(L, i);
		}
		void getMetaTable(std::string m)
		{
			luaL_getmetatable(L, m.c_str());
		}
		
		void setTable(int i)
		{
			lua_settable(L, i);
		}
		
		
		
		void getGlobal(std::string glb)
		{
			lua_getglobal(L, glb.c_str());
		}
		void getLocal(int ind,std::string loc)
		{
			/*
			 luaL_checktype(L, ind, LUA_TTABLE);
			 
			 lua_pushstring(L, loc.c_str());
			 lua_gettable(L, ind);
			 */
			lua_getfield(L, ind, loc.c_str());
		}
		
		
		
		void push(int i)
		{
			lua_pushinteger(L, i);
		}
		void push(float f)
		{
			lua_pushnumber(L, f);
		}
		void push(std::string str)
		{
			lua_pushstring(L, str.c_str());
		}
		void pushValue(int i)
		{
			lua_pushvalue(L, i);
		}
		
		void checkTable(int ind)
		{
			luaL_checktype(L, ind, LUA_TTABLE);
		}
		std::string checkString(int ind)
		{
			return luaL_checkstring(L, ind);
		}
		
		bool call(int args, int results)
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
		
		
		void newBlankTable()
		{
			lua_newtable(L);
		}
		void setTableField(const char* key, int i)
		{
			lua_pushstring(L, key);
			lua_pushinteger(L, i);
			
			lua_settable(L, -3);
		}
		void setTableField(const char* key, float i)
		{
			lua_pushstring(L, key);
			lua_pushnumber(L, i);
			
			lua_settable(L, -3);
		}
		void setTableField(const char* key, const char* str)
		{
			lua_pushstring(L, key);
			lua_pushstring(L, str);
			
			lua_settable(L, -3);
		}
		void setField(int i, const char * key)
		{
			lua_setfield(L, i, key);
		}
		
		
		void setGlobal(std::string name)
		{
			lua_setglobal(L, name.c_str());
		}
	}
	
}


