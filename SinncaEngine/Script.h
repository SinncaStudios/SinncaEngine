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
		
		bool checkType(int ind, int t);
		
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
		
		void newBlankTable();
		void setTableField(const char* key, int i);
		void setTableField(const char* key, float i);
		void setTableField(const char* key, const char* str);
		void setField(int i, const char* key);
		
		void setGlobal(std::string name);
		
		
		~luaScript();
		
	protected:
		
		
		
		static luaScript* _instance;
		
	};
	
}

#endif /* defined(__SinncaEngine__Script__) */
