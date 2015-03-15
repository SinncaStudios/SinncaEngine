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
	/*
	tree* tree::_instance = NULL;
	
	tree* tree::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<tree>();
		}
		
		return _instance;
	}
	*/

	namespace Tree
	{
		
		scene* root;
		scene* currentScene;
		
		void setup(const char* path)
		{
			/*
			 Script::newBlankTable();
			 
			 Script::pushValue(1);
			 Script::setMetaTable(-2);
			 
			 Script::pushValue(1);
			 Script::setField(1, "__index");
			 
			 root = (scene**)Script::newUserdata<scene>();
			 *root = Heap->allocateNew<scene>();
			 
			 Script::getGlobal("_root");
			 Script::setMetaTable(-2);
			 Script::getMetaTable("_root");
			 Script::setMetaTable(-2);
			 
			 Script::setField(-2, "__self");
			 Script::setGlobal("root");
			 */
			root = createScene("root");
			
			currentScene = root;
			
			root->entityStorage = NULL;
			//root.setName("root");
			
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
	
	
	static int l_dumptofile(lua_State* L)
	{
		
		Tree::root->dumpToFile(lua_tostring(L, 2));
		
		return 0;
	}
	
	static int l_loadfromfile(lua_State* L)
	{
		Tree::root->readFromFile(lua_tostring(L, 2));
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
		//Script::registerType<ree>(rootFuncs);
	}
}

