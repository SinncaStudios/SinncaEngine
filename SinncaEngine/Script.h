//
//  Script.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 12/12/13.
//  Copyright (c) 2013 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Script__
#define __SinncaEngine__Script__

#include <iostream>
#include "Memory.h"
#include "Heap.h"
#include <sstream>

namespace sinnca
{
		
	extern "C"
	{
		
		#include<Lua/lua.h>
		#include<Lua/lualib.h>
		#include<Lua/lauxlib.h>
		
	}

	
	namespace Script
	{
		
		// the lua state
		extern lua_State* L;
		

		lua_State* getState();
		
		void setup();
		void shutdown();
		
		void bindFunctions();
		
		void doFile(std::string file);
		void doString(std::string str);
		
		
		void setVar(std::string var, int i);
		void setVar(std::string var, float i);
		void setVar(std::string var, std::string i);
		void setMetaTable(int i);
		void getMetaTable(std::string m);
		void setTable(int i);
		
		
		void getGlobal(std::string glb);
		void getLocal(int ind, std::string loc);
		
		void push(int i);
		void push(float f);
		void push(std::string str);
		void pushValue(int i);
		
		void checkTable(int ind);
		std::string checkString(int ind);
		
		bool call(int args, int results);
		
		template <class t>
		t* newUserdata()
		{
			return (t*)lua_newuserdata(L, sizeof(t));
		}
		template <class t>
		t* toUserdata(int ind)
		{
			return (t*)lua_touserdata(L, ind);
		}
		
		void newBlankTable();
		void setTableField(const char* key, int i);
		void setTableField(const char* key, float i);
		void setTableField(const char* key, const char* str);
		void setField(int i, const char* key);
		
		void setGlobal(std::string name);
		
		template <class t>
		t* createObject(Memory* allocator = nullptr)
		{
			
			if (allocator == nullptr)
			{
				allocator = Heap;
			}
			
			// get the asset tracker
			getGlobal("___AssetTracker_");
			// push field
			std::stringstream ss;
			ss << t::metatable << '_' << allocator->getNoOfAllocations();
			push(ss.str());
			
			// create the object
			newBlankTable();
			
			pushValue(1);
			setMetaTable(-2);
			
			pushValue(1);
			setField(1, "__index");
			
			
			t** ob = newUserdata<t*>();
			*ob = (t*)allocator->allocate(sizeof(t), alignof(t));
			
			
			luaL_getmetatable(L, t::metatable);
			setMetaTable(-2);
			
			setField(-2, "__self");
			
			
			#warning figure this area out!
			// copy
			//pushValue(1);
			//lua_insert(L, 1);
			// put into asset tracker
			lua_settable(L, -3);
			setGlobal("___AssetTracker_");
			
			// retrive again...
			getGlobal("___AssetTracker_");
			push(ss.str());
			lua_gettable(L, -2);
			
			return *ob;
		}
		
		template<typename T>
		T* checkType(int ind)
		{
			void* ud = 0;
			
			// check for table object
			luaL_checktype(L, ind, LUA_TTABLE);
			
			// push the key we're looking for (in this case, it's "__self")
			lua_pushstring(L, "__self");
			// get our table
			lua_gettable(L, ind);
			
			// cast userdata pointer to whatever type
			ud = lua_touserdata(L, -1);
			luaL_argcheck(L, ud != 0, ind, "The object given cannot be cast into the required type...");
			
			return *((T**)ud);
		}
		
		template<class T>
		void registerType(const luaL_Reg funcs[])
		{
			luaL_newmetatable(L, T::metatable);
			
			luaL_register(L, 0, funcs);
			lua_pushvalue(L, -1);
			
			lua_setfield(L, -2, "__index");
			
			
			
			luaL_register(L, T::metatable, funcs);
		}
		
	};
	
}

#endif /* defined(__SinncaEngine__Script__) */
