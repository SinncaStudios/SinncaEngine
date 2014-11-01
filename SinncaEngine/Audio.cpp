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
	
	namespace Audio
	{
		
		ALCdevice* device;
		ALCcontext* context;
		
		ALboolean enumEnabled;
		
		void setup()
		{
			device = alcOpenDevice(NULL);
			if (!device)
			{
				printf("Could not create OpenAL device");
			}
			
			enumEnabled = alcIsExtensionPresent(device, "ALC_ENUMERATION_EXT");
			if (enumEnabled == AL_TRUE)
			{
				
				const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
				/*
				size_t len = 0;
				
				printf("AL Devices List:\n");
				while (devices && *devices != '/0' && next && *next != '/0')
				{
					fprintf(stdout, "%s\n", devices);
					len = strlen(devices);
					devices += (len + 1);
					next += (len + 2);
				}
				 */
				fprintf(stdout, "Devices: %s\n", devices);
			}
			
			
			context = alcCreateContext(device, NULL);
			if (!alcMakeContextCurrent(context))
			{
				printf("Could not make OpenAL context");
			}
			
		}
		
		void shutDown()
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
		}
		
	}
	
	
}