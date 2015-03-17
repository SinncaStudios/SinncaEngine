//
//  Audio.h
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#ifndef __SinncaEngine__Audio__
#define __SinncaEngine__Audio__

#include <iostream>
#include <OpenAL/al.h>
#include <OpenAL/alc.h>


namespace sinnca
{
	
	namespace Audio
	{
		
		extern ALCdevice* device;
		extern ALCcontext* context;
		
		extern ALboolean enumEnabled;
		
		extern ALenum error;
		
		void setup();
		void shutDown();
		
	}
}

#endif /* defined(__SinncaEngine__Audio__) */
