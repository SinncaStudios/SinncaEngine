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
		/*
		 // variables are in Audio.cpp
		 
		static ALCdevice* device;
		static ALCcontext* context;
		
		static ALboolean enumEnabled;
		*/
		static ALenum error = alGetError();
		
		void setup();
		void shutDown();
		
	}
}

#endif /* defined(__SinncaEngine__Audio__) */
