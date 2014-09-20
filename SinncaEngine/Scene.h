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

// asset tracking
#include "Entity.h"
#include "Grid.h"
#include "Image.h"
#include "Texture.h"

namespace sinnca
{
	class scene : public node
	{
		float percLoaded;
		bool loadable, unloadOnSwitch;
		
		int perspective;
		
	public:
		
		// storage
		guiMenu* guiManager;
		pool* entityStorage;
		pool* sceneStorage;
		pool* imageStorage;
		pool* textureStorage;
		list* gridStorage;
		
		// reference keeping
		std::vector<node*> nodeRef;
		std::vector<entity*> entityRef;
		std::vector<grid*> gridRef;
		std::vector<scene*> sceneRef;
		std::vector<image*> imageRef;
		std::vector<color*> colorRef;
		std::vector<texture*> textureRef;
		
		
		scene();
		~scene();
		
		void onLoad();
		void unLoad();
		
		void update();
		void render();
		
		int pers();
		
		int readFromFile(std::string file);
		int dumpToFile(std::string file);
		
		
		//void* operator new(size_t s, std::string n);
		//void operator delete(void* p);
	};
	
	#define createScene(a) new(a)scene()
	void registerScene(lua_State* L);
}

#endif /* defined(__SinncaEngine__Scene__) */
