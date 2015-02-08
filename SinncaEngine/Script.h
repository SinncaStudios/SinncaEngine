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

namespace sinnca
{
		
	extern "C"
	{
		
		#include<Lua/lua.h>
		#include<Lua/lualib.h>
		#include<Lua/lauxlib.h>
		
	}


	#define Script (luaScript::Instance())
	class luaScript
	{
		
	public:
		
		// the lua state
		lua_State* L;
		lua_State* getState();
		
		static luaScript* Instance();
		
		luaScript();
		
		void bindFunctions();
		
		void doFile(std::string file);
		void doString(std::string str);
		
		
		void setVar(std::string var, int i);
		void setVar(std::string var, float i);
		void setVar(std::string var, std::string i);
		void setMetaTable(int i);
		void getMetaTable(std::string m);
		void setTable(int i);
		
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
			
			// cast userdata pointer to "Node" type
			ud = lua_touserdata(L, -1);
			luaL_argcheck(L, ud != 0, ind, "The object given cannot be cast into the required type...");
			
			return *((T**)ud);
		}
		
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
		t* createObject(Memory* allocator = Heap)
		{
			
			Script->newBlankTable();
			
			Script->pushValue(1);
			Script->setMetaTable(-2);
			
			Script->pushValue(1);
			Script->setField(1, "__index");
			
			//entity** en = Script->newUserdata<entity*>();
			t** ob = newUserdata<t*>();
			
			*ob = (t*)allocator->allocate(sizeof(t), alignof(t));
			
			
			//(*en)->name = n;
			
			luaL_getmetatable(L, t::metatable);
			Script->setMetaTable(-2);
			
			Script->setField(-2, "__self");
			
			return *ob;
		}
		
		
		~luaScript();
		
	protected:
		
		
		
		static luaScript* _instance;
		
	};
	
}

#endif /* defined(__SinncaEngine__Script__) */
