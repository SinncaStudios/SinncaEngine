//
//  Audio.cpp
//  SinncaEngine
//
//  Created by Ryan Oldis on 9/27/14.
//  Copyright (c) 2014 Ryan Oldis. All rights reserved.
//

#include "Audio.h"
#include "Heap.h"
#include "Listener.h"

namespace sinnca
{
	
	namespace Audio
	{
		
		ALCdevice* device;
		ALCcontext* context;
		
		ALboolean enumEnabled;
		ALenum error = alGetError();
		
		
		void setup()
		{
			alGetError(); // reset error message;
			
			device = alcOpenDevice(NULL);
			if (!device)
			{
				printf("Could not create OpenAL device");
			}
			
			if ((Audio::error = alGetError() != AL_NO_ERROR))
			{
				printf("Audio error: %s\n", alGetString(Audio::error));
			}
			
			enumEnabled = alcIsExtensionPresent(device, "ALC_ENUMERATION_EXT");
			if (enumEnabled == AL_TRUE)
			{
				
				const ALCchar* devices = alcGetString(NULL, ALC_DEVICE_SPECIFIER);
				
				fprintf(stdout, "Devices: %s\n", devices);
			}
			
			
			context = alcCreateContext(device, NULL);
			if ((Audio::error = alGetError() != AL_NO_ERROR))
			{
				printf("Audio error: %s\n", alGetString(Audio::error));
			}
			
			
			alcMakeContextCurrent(context);
			if ((Audio::error = alGetError() != AL_NO_ERROR))
			{
				printf("Audio error: %s\n", alGetString(Audio::error));
			}
			
			Listener->update();
			
		}
		
		void shutDown()
		{
			alcDestroyContext(context);
			alcCloseDevice(device);
		}
		
	}
	
	
}