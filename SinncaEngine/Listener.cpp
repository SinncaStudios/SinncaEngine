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
		setParent(Camera);
	}
	
	void listener::update()
	{
		alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
	}
	
	void listener::render()
	{
		
	}
}