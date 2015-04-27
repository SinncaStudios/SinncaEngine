//
//  Color.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 7/30/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Color.h"
#include "Tree.h"

namespace sinnca
{
	void* color::operator new(size_t s)
	{
		color* cl = Script::createObject<color>(Tree::currentScene->assets.colorStorage);
		
		cl->ref = Script::makeReference();
		return (void*)cl;
	}
	
	void color::operator delete(void *p)
	{
		if (Tree::currentScene->assets.colorStorage != NULL)
		{
			Tree::currentScene->assets.colorStorage->deallocate(p);
			
		} else {
			
			Heap->deallocate(p);
		}
	}
	
}