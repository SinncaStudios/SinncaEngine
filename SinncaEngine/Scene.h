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
#include "AssetManager.h"
#include "Camera.h"


namespace sinnca
{
	class scene : public node
	{
		float percLoaded;
		bool loadable, retain;
		
		std::string file;
		
	public:
		
		static constexpr auto metatable = "scene";
		
		camera mainCamera;
		pool* cameraStorage;
		
		assetManager assets;
		guiMenu* guiManager;
		guiMenu* loadingScreen;
		
		bool alloced;
		
		/*
		// storage
		guiMenu* guiManager;
		pool* entityStorage;
		pool* sceneStorage;
		pool* colorStorage;
		pool* imageStorage;
		pool* textureStorage;
		pool* sourceStorage;
		pool* bufferStorage;
		list* gridStorage;
		pool* actionStorage;
		pool* fontStorage;
		
		// reference keeping
		std::vector<node*> nodeRef;
		std::vector<entity*> entityRef;
		std::vector<grid*> gridRef;
		std::vector<scene*> sceneRef;
		std::vector<image*> imageRef;
		std::vector<color*> colorRef;
		std::vector<texture*> textureRef;
		std::vector<source*> sourceRef;
		std::vector<buffer*> bufferRef;
		std::vector<action*> actionRef;
		std::vector<font*> fontRef;
		*/
		
		scene();
		~scene();
		
		void onLoad();
		void unLoad();
		
		void preLoad();
		bool switchTo();
		void setLoadable(bool b);
		void setRetain(bool b);
		
		void update();
		void render();
		
		
		//int readFromFile(std::string file);
		//int dumpToFile(std::string file);
		
		
		void* operator new(size_t s, std::string n = "");
		void operator delete(void* p);
	};
	
	//#define createScene(a) new(a)scene()
	void registerScene(lua_State* L);
}

#endif /* defined(__SinncaEngine__Scene__) */
