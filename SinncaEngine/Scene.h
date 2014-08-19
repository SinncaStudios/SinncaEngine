//
//  Scene.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Scene__
#define __SinncaEngine__Scene__

#include <iostream>
#include "Node.h"
#include "PoolAlloc.h"
#include "GuiMenu.h"

namespace sinnca
{
	class scene : public node
	{
		float percLoaded;
		bool loadable, unloadOnSwitch;
		
		int perspective;
		
	public:
		
		guiMenu* guiManager;
		pool* entityStorage;
		pool* imageStorage;
		pool* textureStorage;
		list* gridStorage;
		
		scene();
		~scene();
		
		void onLoad();
		void unLoad();
		
		void update();
		void render();
		
		int pers();
	};
}

#endif /* defined(__SinncaEngine__Scene__) */
