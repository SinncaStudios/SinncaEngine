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

extern "C"
{
#include <Lua/lua.h>
#include <Lua/lualib.h>
#include <Lua/lauxlib.h>
}

namespace sinnca
{
		
	

	
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
		
		uint createReference();
		void getReference(uint r);
		void unReference(uint r);
		
		template <class t>
		t* createObject( uint *ref = nullptr, Memory* allocator = nullptr)
		{
			if (allocator == nullptr)
				allocator = Heap;
			
			
			newBlankTable();
			
			pushValue(1);
			setMetaTable(-2);
			
			pushValue(1);
			setField(1, "__index");
			
			
			t** ob = newUserdata<t*>();
			
			*ob = (t*)allocator->allocate(sizeof(t), alignof(t));
			
			
			getMetaTable(t::metatable);
			setMetaTable(-2);
			
			setField(-2, "__self");
			if (ref)
			{
				pushValue(-1);
				*ref = createReference();
			}
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
			if (ud == nullptr)
			{
				return nullptr;
			}
			
			return *((T**)ud);
		}
		
		template<typename T>
		T* checkTypeUnprotected(int ind)
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
			if (ud == nullptr)
			{
				return nullptr;
			}
			
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
