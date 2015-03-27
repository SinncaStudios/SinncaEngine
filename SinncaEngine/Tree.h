//
//  Tree.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Tree__
#define __SinncaEngine__Tree__

#include <iostream>
#include "Scene.h"
#include "PoolAlloc.h"

namespace sinnca
{
	
	namespace Tree
	{
		extern scene* root;
		
		extern scene* currentScene;
		
		void setup(const char* path = "");
		void shutdown();
		scene* getRoot();
		//void render();
		
		extern pool* sceneStorage;
		extern pool* guiStorage;
		
	};
	
	void registerTree(lua_State* L);
	
}

#endif /* defined(__SinncaEngine__Tree__) */
