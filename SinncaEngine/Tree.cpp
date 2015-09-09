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

#include <new>

namespace sinnca
{

	namespace Tree
	{
		
		scene* root;
		scene* currentScene;
		
		pool* sceneStorage;
		pool* guiStorage;
		
		void setup(const char* path)
		{
			sceneStorage = new pool(sizeof(scene), alignof(scene), sizeof(scene) * 25);
			guiStorage = new pool(sizeof(guiWidget), alignof(guiWidget), sizeof(guiWidget) * 50);
			
			root = new scene();
			root->setRetain(true);
			
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
			delete guiStorage;
			delete sceneStorage;
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
	static int l_rootInitAllocators(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n == 1)
		{
			Tree::root->assets.init();
			Tree::root->alloced = true;
		}
		
		return 0;
	}
	
	static int l_rootSetParent(lua_State* L)
	{
		std::cout << "Root scene cannot have a parent" << std::endl;
		return 0;
	}
	
	static int l_rootAddChild(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n < 2)
		{
			std::cout << "You need to provide at least one other node to add. This function can handle batch adding of nodes." << std::endl;
			return 0;
		}
		for (int i = 2; i < n; i++)
		{
			Tree::root->addChild(Script::checkType<node>(i));
		}
		return 0;
	}
	
	static int l_switchScene(lua_State* L)
	{
		Tree::root->switchTo();
		return 0;
	}
	
	static int l_rootRemoveChild(lua_State* L)
	{
		int n = lua_gettop(L);
		if (n < 2)
		{
			std::cout << "You need to provide at least one other node to remove. This function can handle batch removal of nodes." << std::endl;
			return 0;
		}
		for (int i = 2; i < n; i++)
		{
			Tree::root->removeChild(Script::checkType<node>(i));
		}
		
		return 0;
	}
	
	static const luaL_Reg rootFuncs[] = {
		//{"dumpToFile", l_dumptofile},
		//{"loadFromFile", l_loadfromfile},
		{"initAllocators", l_rootInitAllocators},
		{"setParent", l_rootSetParent},
		{"addChild", l_rootAddChild},
		{"removeChild", l_rootRemoveChild},
		/*
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
		 */
		{"switchTo", l_switchScene},
		{NULL, NULL}
	};
	
	void registerTree(lua_State* L)
	{
		luaL_newmetatable(L, "root");
		
		luaL_register(L, 0, rootFuncs);
		lua_pushvalue(L, -1);
		
		lua_setfield(L, -2, "__index");
		
		
		
		luaL_register(L, "root", rootFuncs);
	}
}

