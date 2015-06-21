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
		
		pool* sceneStorage;
		pool* guiStorage;
		
		void setup(const char* path)
		{
			sceneStorage = new pool(sizeof(scene), alignof(scene), sizeof(scene) * 25);
			guiStorage = new pool(sizeof(guiWidget), alignof(guiWidget), sizeof(guiWidget) * 50);
			
			root = new("root") scene();
			/*
			Script::newBlankTable();
			
			Script::pushValue(1);
			Script::setMetaTable(-2);
			
			Script::pushValue(1);
			Script::setField(1, "__index");
			
			
			scene** ob = Script::newUserdata<scene*>();
			
			*ob = (scene*)Heap->allocate(sizeof(scene), alignof(scene));
			
			
			luaL_getmetatable(Script::getState(), "scene");
			Script::setMetaTable(-2);
			
			Script::setField(-2, "__self");
			Script::setGlobal("root");
			root = *ob;
			*/
			
			currentScene = root;
			
			root->assets.entityStorage = NULL;
			
			
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

