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

	namespace Tree
	{
		
		scene* root;
		scene* currentScene;
		
		void setup(const char* path)
		{
			root = new scene();
			currentScene = root;
			
			//root->assets.entityStorage = NULL;
			
			
#ifdef snMobile
			Script::doFile(path);
#else
			Script::doFile(Computer::getResourcePath() + "/" + "main.lua");
#endif
			
		}
		
		void shutdown()
		{
			delete root;
		}
		
		scene* getRoot()
		{
			// I am root
			return root;
		}
		
	}
	
	
	/*
	static int l_dumptofile(lua_State* L)
	{
		//Tree::root->dumpToFile(lua_tostring(L, 2));
		return 0;
	}
	
	static int l_loadfromfile(lua_State* L)
	{
		//Tree::root->readFromFile(lua_tostring(L, 2));
		return 0;
	}
	 */
	
	/*
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
	*/
	void registerTree(lua_State* L)
	{
		//Script::registerType<ree>(rootFuncs);
	}
}

