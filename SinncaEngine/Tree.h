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

namespace sinnca
{
//#define Tree (tree::Instance())
	namespace Tree
	{
		extern scene* root;
		
	//public:
		
		extern scene* currentScene;
		
		//tree();
		//~tree();
		
		
		void setup(const char* path = "");
		void shutdown();
		scene* getRoot();
		//void render();
		
		//static tree* Instance();
		
	//protected:
		
		//static tree* _instance;
		
	};
	
	void registerTree(lua_State* L);
	
}

#endif /* defined(__SinncaEngine__Tree__) */
