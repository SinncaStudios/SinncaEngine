//
//  Scene.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 2/10/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Scene.h"
#include "MemoryManager.h"
#include "Palette.h"

namespace sinnca
{
	scene::scene()
	{
		col = &Palette->defaultColor;
		guiManager = Heap->allocateNew<guiMenu>();
		percLoaded = 0.0f;
		perspective = 0; // 2D by defualt
		//entityStorage = memoryManager->heap->allocateNew<PoolAllocator>();
	}
	
	scene::~scene()
	{
		//memoryManager->heap->deallocateDelete(entityStorage);
	}
	
	void scene::update()
	{
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->update();
		}
	}
	
	void scene::render()
	{
		Graphics->sceneColor(col->toFloat(col->r), col->toFloat(col->g), col->toFloat(col->b));
		
		for (linkList<node*>::iterator i = children.begin(); i != children.end(); ++i)
		{
			(*i)->render();
		}
	}
	
	int scene::pers()
	{
		return perspective;
	}
}