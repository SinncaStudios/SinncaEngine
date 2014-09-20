//
//  Tree.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Tree.h"
#include "Heap.h"

#include "Computer.h"
#include "Script.h"
#include "Global.h"

namespace sinnca
{
	tree* tree::_instance = NULL;
	
	tree* tree::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<tree>();
		}
		
		return _instance;
	}
	
	tree::tree()
	{
		root = NULL;
		currentScene = this;
		
		entityStorage = NULL;
		name = "root";
		
	}
	
	tree::~tree()
	{
		
	}
	
	void tree::setup(const char* path)
	{
		/*
		Script->newBlankTable();
		
		Script->pushValue(1);
		Script->setMetaTable(-2);
		
		Script->pushValue(1);
		Script->setField(1, "__index");
		
		root = (scene**)Script->newUserdata<scene>();
		*root = Heap->allocateNew<scene>();
		
		Script->getGlobal("_root");
		Script->setMetaTable(-2);
		Script->getMetaTable("_root");
		Script->setMetaTable(-2);
		
		Script->setField(-2, "__self");
		Script->setGlobal("root");
		*/
		
#ifdef snMobile
		Script->doFile(path);
#else
		Script->doFile(Computer->getResourcePath() + "/" + "main.lua");
#endif
		
	}
	
	scene* tree::getRoot()
	{
		// I am root
		return *root;
	}
	
	/*
	void tree::render()
	{
		children.resetItr();
		for (int i = 0; i < noOfChildren; i++, children++)
		{
			if (children.getData())
			{
				children.getData()->render();
			}
		}
	}
	 */
	
	scene* checkRoot(int ind)
	{
		void* ud = 0;
		
		// check for table object
		luaL_checktype(Script->getState(), ind, LUA_TTABLE);
		
		// push the key we're looking for (in this case, it's "__self")
		lua_pushstring(Script->getState(), "__self");
		// get our table
		lua_gettable(Script->getState(), ind);
		
		// cast userdata pointer to "Node" type
		ud = dynamic_cast<scene*>((scene*)lua_touserdata(Script->getState(), -1));
		luaL_argcheck(Script->getState(), ud != 0, ind, "Incompatible 'entity' type...");
		
		return *((scene**)ud);
		
	}
	
	static int l_dumptofile(lua_State* L)
	{
		/*
		int n = lua_gettop(L);
		if (n == 2)
		{
			scene* rt = checkRoot(1);
			rt->dumpToFile(lua_tostring(L, 2));
		}
		 */
		Tree->dumpToFile(lua_tostring(L, 2));
		
		return 0;
	}
	
	static int l_loadfromfile(lua_State* L)
	{
		Tree->readFromFile(lua_tostring(L, 2));
		return 0;
	}
	
	static const luaL_Reg rootFuncs[] = {
		{"dumpToFile", l_dumptofile},
		{"loadFromFile", l_loadfromfile},
		{"setParent", l_setParent},
		{"addChild", l_addChild},
		{"removeChild", l_removeChild},
		
		{"setG", l_setG},
		{"setR", l_setR},
		{"setS", l_setS},
		
		{"movG", l_movG},
		{"movR", l_movR},
		{"movS", l_movS},
		
		{"getG", l_getPos},
		{"getR", l_getRot},
		{"getS", l_getScl},
		
		{"setCol", l_setColor},
		{NULL, NULL}
	};
	
	void registerTree(lua_State* L)
	{
		
		luaL_newmetatable(L, "_root");
		
		
		luaL_register(L, 0, rootFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "_root", rootFuncs);
		
	}
}

