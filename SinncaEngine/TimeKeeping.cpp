//
//  TimeKeeping.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 8/12/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "TimeKeeping.h"
#include "Heap.h"

namespace sinnca
{
	// This is useful...
	// http://stackoverflow.com/questions/2150291/how-do-i-measure-a-time-interval-in-c
	
	
	timeKeeping* timeKeeping::_instance = NULL;
	timeKeeping* timeKeeping::Instance()
	{
		if (_instance == NULL)
		{
			_instance = Heap->allocateNew<timeKeeping>();
		}
		
		return _instance;
	}
	
	timeKeeping::timeKeeping()
	{
		fps = 0.0f;
		deltaTicks = 0;
		
		start();
	}
	
	void timeKeeping::update()
	{
		deltaTicks = getTicks();
		start();
		
	}
	
	
	float timeKeeping::withDeltaTime()
	{
		return (float)deltaTicks / 1000.0f;
	}
	
}