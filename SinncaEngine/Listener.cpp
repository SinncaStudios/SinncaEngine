//
//  Listener.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Listener.h"
#include "Heap.h"
#include "Camera.h"
#include "Tree.h"

namespace sinnca
{
	listener* listener::_instance = NULL;
	listener* listener::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<listener>();
		}
		
		return _instance;
	}
	
	listener::listener()
	{
		// the OpenAL listener should be the same position as the OpenGL camera
		setParent(&Tree::currentScene->mainCamera);
	}
	
	void listener::update()
	{
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
		alListener3f(AL_ORIENTATION, rot.x, rot.y, -1.0f);
		alListener3f(AL_VELOCITY, 0.0f, 0.0f, 0.0f);
	}
	
	void listener::render()
	{
		
	}
}