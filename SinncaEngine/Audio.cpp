//
//  Audio.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Audio.h"
#include "Heap.h"

namespace sinnca
{
	audio* audio::_instance = NULL;
	audio* audio::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<audio>();
		}
		
		return _instance;
	}
	
	
	audio::~audio()
	{
		
	}
	
	void audio::setup()
	{
		device = alcOpenDevice(NULL);
		if (!device)
		{
			printf("Could not create OpenAL device");
		}
		
		
	}
	
	
}